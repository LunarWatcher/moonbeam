# moonbeam

Silly little lua module for scripting purposes. Largely exists to back some upcoming scripts I need in my dotfiles

This module is primarily aimed at Linux, with Windows support being incidental.

## Modules

### `moonbeam`

Fuck knows

### `moonbeam.system`

Contains system operations, notably a massive extension to the process execution capabilities of lua's stdlib, and filesystem operations, which are lacking entirely from the stdlib.

May also include special implementations for certain operations (like copying and pasting), but I have no idea if this is doable easily enough that it's worth it over just running `xclip` with stdin hijacked.

### `moonbeam.json`

Maintained alternative to `cjson` and other misc mostly abandoned JSON libraries. This does not actually do any parsing by itself, but rather delegates to a proper C library. At this time, it just forwards to nlohmann/json, but in the longer run, it will likely switch to yyjson for unlimited speed.

### `moonbeam.cli`

Provides command line argument parsing through [CLI12](https://codeberg.org/LunarWatcher/CLI12). Uses `moonbeam.lang`'s `Box` type.

### `moonbeam.lang`

Utility-module for the other modules. Largely used for its `Box` type, used for passing references to lua functions.

## Requirements

* `liblua5.4-dev` or `liblua5.5-dev` - this will primarily be pinned to whatever my main distros use, though future support for more dynamic versions may be considered
* A C++23 runtime/compiler

## Installing

### Standalone

```bash
# It's assumed you've already cloned the repo
mkdir build
cd build
# root install is required with Lua's default linker paths. If you amend your lua path
# to include a ~/.local folder, you can append `-DCMAKE_INSTALL_PREFIX="$HOME/.local"`.
# Moonbeam installs into ${INSTALL_PREFIX}/lib/lua/${LUA_VERSION}/, where LUA_VERSION
# is derived when `liblua` is located
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j $(nproc)

# Optional: moonbeam comes with a lua-based test suite you can run before installing
make -j $(nproc) test

sudo make install
```

### Embedded

Moonbeam has not been tested in an embedded environment, but if you still wish to include it, the recommended way is to use FetchContent:
```cmake
include(FetchContent)
FetchContent_Declare(moonbeam
    GIT_REPOSITORY https://codeberg.org/LunarWatcher/moonbeam
    GIT_TAG v1.0.0
)
FetchContent_MakeAvailable(moonbeam)
```

### Meta definitions and documentation

`tests/meta` contains meta definitions for LSPs for all the modules in lua. These also act as documentation for the various available functions. I strongly recommend making sure they're discoverable by your LSP setup. If you don't have one available, the files themselves still serve as condensed documentation.

