#include <lua.hpp>

#include "moonbeam/common/UdataUtils.hpp"
#include "moonbeam/json/Json.hpp"
#include "moonbeam/system/Process.hpp"
#include "moonbeam/udata/TypeRegistry.hpp"
#include "system/System.hpp"

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
    luaL_newlib(L, moonbeam::system::functions);
    moonbeam::util::registerMetatable(
        L,
        moonbeam::system::Process::procMetatable,
        UdataStcProcess
    );

    return 1;
}

int luaopen_moonbeam_json(lua_State* L) {
    luaL_newlib(L, moonbeam::json::functions);
    return 1;
}


}
