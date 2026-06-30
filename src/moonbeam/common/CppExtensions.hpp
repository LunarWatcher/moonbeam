#pragma once

#include <lua.hpp>
#include <string>

namespace moonbeam::ext {

inline std::string toCppString(
    lua_State* L,
    int pos
) {
    size_t len;
    auto rawStr = luaL_checklstring(L, pos, &len);

    return std::string(
        rawStr,
        len
    );
}

}
