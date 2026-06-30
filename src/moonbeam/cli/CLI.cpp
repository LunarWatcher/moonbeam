#include "CLI.hpp"
#include "CLI/CLI.hpp"
#include "moonbeam/common/CppExtensions.hpp"
#include "moonbeam/common/IterUtils.hpp"
#include "moonbeam/lang/LangExtensions.hpp"
#include "moonbeam/udata/TypeRegistry.hpp"
#include "lua.hpp"

#include <iostream>
#include <lauxlib.h>
#include <lua.h>

namespace moonbeam {

namespace cli {

int Parse::addFlag(lua_State* L) {
    auto app = (AppWrapper**) luaL_checkudata(L, 1, UdataCLI12App);
    // TODO: make utility wrapper for the three arg form of checkstring with std::string conversion
    auto flagStr = luaL_checkstring(L, 2);
    auto box = (moonbeam::lang::Box::Box**) luaL_checkudata(L, 3, UdataBoxedPrimitive);
    if (!(**box).isBool()) {
        return luaL_error(
            L,
            "app:addFlag requires a bool box"
        );
    }
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

    if (!lua_istable(L, 2)) {
        return luaL_typeerror(
            L,
            2,
            luaL_typename(L, LUA_TTABLE)
        );
    }

    std::vector<std::string> args;
    util::iterateTable(L, 2, [&]() {
        int pos = luaL_checkinteger(L, -2);
        // -1 is the lua interpreter, the other 0 and under is other flags that we can discard (lua interpreter flags)
        if (pos <= 0 && pos != -1) {
            return;
        } else if (pos == -1) {
            // -1 is the program name, as far as I can tell, in all cases. This is the first argument in our vec
            args.insert(args.begin(), ext::toCppString(L, -1));
        } else {
            args.push_back(ext::toCppString(L, -1));
        }
    });

    std::vector<const char*> nativeVec;
    if (!args.empty()) {
        nativeVec.reserve(args.size());
        for (auto& arg : args) {
            nativeVec.push_back(arg.c_str());
        }
    }

    try {
        (**udata).app->parse(nativeVec.size(), nativeVec.data());
    } catch (const CLI::ParseError& e) {
        (**udata).app->exit(e);
        // I don't understand why this requires separate handling, but whatever
        // Decay to std::exception results in a shit message instead
        // TODO: this can still return "This should be caught in your main function, see examples", but not sure how
        // best to handle it. I want to avoid a just dumb e.what() == "..."
        return luaL_error(
            L,
            "CLI12 returned potentially internal error message: %s",
            e.what()
        );
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

int Parse::optionRequired(lua_State *L) {
    auto udata = (CLI::Option**) luaL_checkudata(L, 1, UdataCLI12Option);
    (**udata).required(true);
    return 1;
}

int Parse::optionDefault(lua_State *L) {
    auto udata = (CLI::Option**) luaL_checkudata(L, 1, UdataCLI12Option);

    switch (lua_type(L, 2)) {
    case LUA_TNUMBER:
        if (lua_isinteger(L, 2)) {
            (*udata)->default_val(luaL_checkinteger(L, 2));
        } else {
            (*udata)->default_val(luaL_checknumber(L, 2));
        }
        break;
    case LUA_TSTRING:
        (*udata)->default_val(ext::toCppString(L, 2));
        break;
    case LUA_TBOOLEAN:
        (*udata)->default_val(lua_toboolean(L, 2));
        break;
    default:
        return luaL_error(
            L,
            "%s is not a supported type for option:default",
            lua_typename(L, 2)
        );
    }
    return 1;
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
