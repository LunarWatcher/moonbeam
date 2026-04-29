#pragma once

#include "nlohmann/json.hpp"

#include <lua.hpp>

namespace moonbeam::json {


extern void parseInternal(lua_State* state, const nlohmann::json& json);
extern int parse(lua_State* state);

inline const static luaL_Reg functions[] {
    {"parse", parse},
    {nullptr, nullptr}
};

}
