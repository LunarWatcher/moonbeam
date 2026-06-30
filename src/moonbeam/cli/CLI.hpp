#pragma once

#include <lua.hpp>
#include <CLI/CLI.hpp>

namespace moonbeam::cli {

namespace Parse {

/**
 * Utility wrapper for CLI::App. `add_subcommand` returns a new CLI::App* that's bound to the root app's
 * lifecycle. Therefore, we need to wrap it and indicate if a given CLI::App* is the main app (`delete` in __gc), or a
 * subapp (ignore and erase on GC)
 *
 * Moonbeam does not currently implement `add_subcommand` wrapper functionality, but when it is added, this will be
 * needed.
 */
struct AppWrapper {
    CLI::App* app;
    bool isRootApp;
};

extern int addFlag(lua_State* L);
extern int addOption(lua_State* L);
extern int parse(lua_State* L);
extern int freeApp(lua_State* L);

extern int optionRequired(lua_State* L);
extern int optionDefault(lua_State* L);

inline const static luaL_Reg appMetatable[] = {
    { "addFlag", addFlag },
    { "addOption", addOption },
    { "parse", parse },

    { "__gc", freeApp },
    { nullptr, nullptr },
};

inline const static luaL_Reg optMetatable[] = {
    { "required", optionRequired },
    { "default", optionDefault },
    { nullptr, nullptr }
};

}

extern int createApp(lua_State* L);

inline const static luaL_Reg functions[] = {
    { "createApp", createApp },
    { nullptr, nullptr },
};

}
