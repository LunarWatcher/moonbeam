#pragma once

#include <lua.hpp>

namespace moonbeam::system {

namespace Process {

extern int freeProcess(lua_State* L);
extern int readStdout(lua_State* L);
extern int readStderr(lua_State* L);
extern int writeStdin(lua_State* L);
extern int closeStdin(lua_State* L);
extern int block(lua_State* L);


const static luaL_Reg procMetatable[] = {
    { "readStdout", readStdout },
    { "readStderr", readStderr },
    { "write", writeStdin },
    { "closeStdin", closeStdin },
    { "block", block },

    { "__gc", freeProcess },
    { nullptr, nullptr },
};

}

extern int process(lua_State* L);

}
