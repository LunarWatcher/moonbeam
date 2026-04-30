#pragma once

#include <lua.hpp>

namespace moonbeam::filesystem {

extern int findInPath(lua_State* L);

inline const static luaL_Reg functions[] = {
    { "findInPath", findInPath },
    { nullptr, nullptr },
};

}
