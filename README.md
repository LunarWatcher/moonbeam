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

* `liblua5.4-dev` - this will primarily be pinned to whatever my main distros use, though future support for more dynamic versions may be considered

## Installing

```

```

