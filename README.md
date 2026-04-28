# moonbeam

Silly little lua module for scripting purposes. Largely exists to back some upcoming scripts I need in my dotfiles

This module is primarily aimed at Linux, with Windows support being incidental.

## Modules

### `moonbeam`

Fuck knows

### `moonbeam.system`

Contains system operations, notably a massive extension to the process execution capabilities of lua's stdlib, and filesystem operations, which are lacking entirely from the stdlib.

May also include special implementations for certain operations (like copying and pasting), but I have no idea if this is doable easily enough that it's worth it over just running `xclip` with stdin hijacked.

