#include <lua.hpp>

extern "C" {

int luaopen_moonbeam(lua_State* L) {
    const static luaL_Reg functions[] = {
        { nullptr, nullptr },
    };
    luaL_newlib(L, functions);
    lua_pushstring(L, "good girl :3");
    lua_setfield(L, -2, "test_global");
    return 1;
}

int luaopen_moonbeam_system(lua_State* L) {
    const static luaL_Reg functions[] = {
        { nullptr, nullptr },
    };
    luaL_newlib(L, functions);
    
    return 1;
}
    
}
