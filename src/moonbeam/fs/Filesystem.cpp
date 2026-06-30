#include "Filesystem.hpp"
#include "lua.h"
#include "moonbeam/common/IterUtils.hpp"
#include <iostream>
#include <string>
#include <vector>

#include <filesystem>

#include <stc/FileUtil.hpp>

namespace moonbeam {

int filesystem::findInPath(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    luaL_checktype(L, 2, LUA_TSTRING);

    std::vector<std::filesystem::path> directories;
    directories.reserve(
        util::length(L, 1)
    );

    util::iterateTable(
        L,
        1,
        [&]() {
            luaL_checktype(L, -2, LUA_TNUMBER);
            luaL_checktype(L, -1, LUA_TSTRING);
            size_t size;
            auto str = luaL_checklstring(
                L,
                -1,
                &size
            );
            directories.push_back(std::string_view{str, size});
        }
    );
    
    size_t strlen;
    auto* rawStr = luaL_checklstring(L, 2, &strlen);
    std::string filename{rawStr, strlen};

    if (auto file = stc::FileUtil::findFile(
        directories,
        filename
    ); file.has_value()) {
        std::string s = file->string();

        lua_pushlstring(L, s.c_str(), s.size());
    } else {
        lua_pushnil(L);
    }

    return 1;
}

int filesystem::getCwd(lua_State* L) {
    std::string pwd = std::filesystem::current_path().string();
    lua_pushlstring(L, pwd.c_str(), pwd.size());
    return 1;
}

}
