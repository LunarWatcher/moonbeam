#include <lua.hpp>

#include "moonbeam/common/UdataUtils.hpp"
#include "moonbeam/fs/Filesystem.hpp"
#include "moonbeam/json/Json.hpp"
#include "moonbeam/system/Process.hpp"
#include "moonbeam/udata/TypeRegistry.hpp"
#include "system/System.hpp"

extern "C" {

// TODO: remove?
int luaopen_moonbeam(lua_State* L) {
    const static luaL_Reg functions[] = {
        { nullptr, nullptr },
    };
    luaL_newlib(L, functions);

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

int luaopen_moonbeam_fs(lua_State* L) {
    luaL_newlib(L, moonbeam::filesystem::functions);
    return 1;
}

}
