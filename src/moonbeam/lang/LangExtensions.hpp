#pragma once

#include <lua.hpp>
#include <string>
#include <variant>

namespace moonbeam::lang {

namespace Box {

struct Box {
    std::variant<
        int,
        double,
        std::string,
        bool
    > value;

    bool isBool() const {
        return std::holds_alternative<bool>(value);
    }
};

extern int unwrap(lua_State* L);
extern int freeBox(lua_State* L);

inline const static luaL_Reg boxMetatable[] = {
    { "unwrap", unwrap },

    { "__gc", freeBox },
    { nullptr, nullptr },
};

}

extern int newBoolBox(lua_State* L);
extern int newStringBox(lua_State* L);
extern int newIntBox(lua_State* L);
extern int newDoubleBox(lua_State* L);

inline const static luaL_Reg functions[] = {
    { "newBoolBox", newBoolBox },
    { "newStringBox", newStringBox },
    { "newIntBox", newIntBox },
    { "newDoubleBox", newDoubleBox },
    { nullptr, nullptr },
};

}
