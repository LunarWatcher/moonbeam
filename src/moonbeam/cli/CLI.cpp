#include "CLI.hpp"
#include "CLI/CLI.hpp"
#include "moonbeam/common/IterUtils.hpp"
#include "moonbeam/lang/LangExtensions.hpp"
#include "moonbeam/udata/TypeRegistry.hpp"
#include "lua.hpp"

#include <iostream>

namespace moonbeam {

namespace cli {

int Parse::addFlag(lua_State* L) {
    auto app = (AppWrapper**) luaL_checkudata(L, 1, UdataCLI12App);
    // TODO: make utility wrapper for the three arg form of checkstring with std::string conversion
    auto flagStr = luaL_checkstring(L, 2);
    auto box = (moonbeam::lang::Box::Box**) luaL_checkudata(L, 3, UdataBoxedPrimitive);
    auto flagDescription = luaL_checkstring(L, 4);
    std::visit(
        [&](auto& v) {
            auto opt = (**app).app->add_flag(
                flagStr,
                v,
                flagDescription
            );
            auto** luaOpt = (CLI::Option**) lua_newuserdata(
                L,
                sizeof(CLI::Option**)
            );
            luaL_setmetatable(L, UdataCLI12Option);
            *luaOpt = opt;
        },
        (**box).value
    );

    return 1;
}
int Parse::addOption(lua_State* L) {
    auto app = (AppWrapper**) luaL_checkudata(L, 1, UdataCLI12App);
    // TODO: make utility wrapper for the three arg form of checkstring with std::string conversion
    auto flagStr = luaL_checkstring(L, 2);
    auto box = (moonbeam::lang::Box::Box**) luaL_checkudata(L, 3, UdataBoxedPrimitive);
    auto flagDescription = luaL_checkstring(L, 4);
    std::visit(
        [&](auto& v) {
            auto opt = (**app).app->add_option(
                flagStr,
                v,
                flagDescription
            );
            auto** luaOpt = (CLI::Option**) lua_newuserdata(
                L,
                sizeof(CLI::Option**)
            );
            luaL_setmetatable(L, UdataCLI12Option);
            *luaOpt = opt;
        },
        (**box).value
    );

    return 1;
}

int Parse::parse(lua_State* L) {
    auto udata = (AppWrapper**) luaL_checkudata(L, 1, UdataCLI12App);

    std::vector<std::string> args;
    util::iterateTable(L, 2, [&]() {
        size_t len;
        auto entry = luaL_checklstring(L, -1, &len);
        args.push_back(std::string(entry, len));
    });

    try {
        (**udata).app->parse(args);
    } catch (const CLI::ParseError& e) {
        (**udata).app->exit(e);
        return luaL_error(L, "See --help for correct use of this script");
    } catch (const std::exception& e) {
        return luaL_error(L, e.what());
    }
    return 0;
}

int Parse::freeApp(lua_State* L) {
    auto udata = (AppWrapper**) luaL_checkudata(L, 1, UdataCLI12App);
    // Ugh, this got messy
    if (*udata != nullptr) {
        // If the app is the root app, we free the app instance
        if ((**udata).app != nullptr && (**udata).isRootApp) {
            delete (**udata).app;
            (**udata).app = nullptr;
        }
        // Regardless, we free the udata, which is separate from the app data within the udata, and must always be
        // freed.
        delete (*udata);
        *udata = nullptr;
    }
    return 0;
}

}

int cli::createApp(lua_State* L) {
    auto appName = luaL_checkstring(L, 1);
    auto appDescription = luaL_checkstring(L, 2);
    auto** app = (Parse::AppWrapper**) lua_newuserdata(
        L,
        sizeof(Parse::AppWrapper**)
    );
    luaL_setmetatable(L, UdataCLI12App);

    // This is so fucking cursed
    // I love it :3
    *app = new Parse::AppWrapper {
        .app = new CLI::App(appName, appDescription),
        .isRootApp = true
    };
    return 1;
}

}
