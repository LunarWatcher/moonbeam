#include "Process.hpp"

#include "lauxlib.h"
#include "lua.h"
#include "moonbeam/udata/TypeRegistry.hpp"
#include <iostream>
#include <stc/unix/Process.hpp>

// TODO: not a fan of this structure. system::Process should maybe be separated?
namespace moonbeam {

int system::Process::freeProcess(lua_State* L) {
    auto udata = (stc::Unix::Process**) luaL_checkudata(L, 1, UdataStcProcess);
    if (*udata != nullptr) {
        delete (*udata);
        *udata = nullptr;
    }
    return 0;
}

int system::Process::readStdout(lua_State* L) {
    // TODO: validate properly
    auto udata = (stc::Unix::Process**) luaL_checkudata(L, 1, UdataStcProcess);

    auto str = (**udata).getStdoutBuffer(true);
    lua_pushlstring(
        L,
        str.c_str(),
        str.size()
    );
    
    return 1;
}

int system::Process::writeStdin(lua_State* L) {
    auto udata = (stc::Unix::Process**) luaL_checkudata(L, 1, UdataStcProcess);
    size_t size;
    auto str = luaL_checklstring(L, 2, &size);

    (**udata).writeToStdin({str, size});

    return 0;
}

int system::Process::closeStdin(lua_State* L) {
    auto udata = (stc::Unix::Process**) luaL_checkudata(L, 1, UdataStcProcess);
    (**udata).closeStdin();
    return 0;
}

int system::Process::block(lua_State* L) {
    auto udata = (stc::Unix::Process**) luaL_checkudata(L, 1, UdataStcProcess);
    int code = (**udata).block();

    lua_pushnumber(L, code);
    return 1;
}

int system::process(lua_State* L) {
    if (lua_gettop(L) == 0) {
        return luaL_error(
            L,
            "This function requires at least one argument"
        );
    }

    // TODO: stc should support string_view. Lua owns these strings, so copying them is redundant
    std::vector<std::string> command;
    command.reserve(
        lua_gettop(L)
    );

    for (size_t i = 0; i < (size_t) lua_gettop(L); ++i) {
        luaL_checktype(L, i + 1, LUA_TSTRING);
        size_t size;
        auto str = luaL_checklstring(
            L,
            i + 1,
            &size
        );
        command.push_back({str, size});
    }

    auto** proc = (stc::Unix::Process**) lua_newuserdata(
        L,
        sizeof(stc::Unix::Process**)
    );
    luaL_setmetatable(L, UdataStcProcess);

    *proc = new stc::Unix::Process(
        command,
        stc::Unix::Pipes::separate(true)
    );

    return 1;
}

}
