#pragma once

#include <functional>
#include "lua.hpp"

namespace moonbeam::util {

extern void iterateTable(
    lua_State* L,
    LUA_INTEGER tableIndex,
    const std::function<void()>& next
);

extern LUA_INTEGER length(lua_State* L, LUA_INTEGER stackIdx);

}
