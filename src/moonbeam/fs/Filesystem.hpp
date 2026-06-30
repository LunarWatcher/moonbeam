#pragma once

#include <lua.hpp>

namespace moonbeam::filesystem {

extern int findInPath(lua_State* L);
extern int getCwd(lua_State* L);

inline const static luaL_Reg functions[] = {
    { "findInPath", findInPath },
    { "cwd", getCwd },
    { nullptr, nullptr },
};

}
