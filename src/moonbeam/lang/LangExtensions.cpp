#include "LangExtensions.hpp"
#include "moonbeam/udata/TypeRegistry.hpp"
#include <variant>

namespace moonbeam {

namespace lang {

int Box::unwrap(lua_State* L) {
    auto udata = (Box**) luaL_checkudata(L, 1, UdataBoxedPrimitive);
    if (udata == nullptr) {
        return luaL_error(
            L,
            "Attempted to use GC'd box"
        );
    }

    auto& var = (**udata).value;

    if (std::holds_alternative<std::string>(var)) {
        // lua makes a copy, so this is fine
        lua_pushstring(L, std::get<std::string>(var).c_str());
    } else if (std::holds_alternative<int>(var)) {
        lua_pushinteger(L, std::get<int>(var));
    } else if (std::holds_alternative<double>(var)) {
        lua_pushnumber(L, std::get<double>(var));
    } else if (std::holds_alternative<bool>(var)) {
        lua_pushboolean(L, std::get<bool>(var));
    } else {
        return luaL_error(
            L,
            "Critical developer error: value holds type not supported by unwrap"
        );
    }

    return 1;
}

int Box::freeBox(lua_State* L) {
    auto udata = (Box**) luaL_checkudata(L, 1, UdataBoxedPrimitive);
    if (*udata != nullptr) {
        delete (*udata);
        *udata = nullptr;
    }
    return 0;
}

}

// Public non-udata API

// Internal utility funcs
namespace {

template <typename T>
lang::Box::Box** createUdataInstance(lua_State* L) {
    auto** box = (lang::Box::Box**) lua_newuserdata(
        L,
        sizeof(lang::Box::Box**)
    );
    luaL_setmetatable(L, UdataBoxedPrimitive);

    // we default-init to get the right type in the variant
    *box = new lang::Box::Box(T());
    return box;
}

}

int lang::newBoolBox(lua_State* L) {
    createUdataInstance<bool>(L);
    return 1;
}
int lang::newStringBox(lua_State* L) {
    createUdataInstance<std::string>(L);
    return 1;
}
int lang::newIntBox(lua_State* L) {
    // TODO: LUA_INTEGER or whatever the typedef was?
    createUdataInstance<int>(L);
    return 1;
}
int lang::newDoubleBox(lua_State* L) {
    createUdataInstance<double>(L);
    return 1;
}

}
