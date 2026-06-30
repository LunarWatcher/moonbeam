--- @meta

--- Represents a CLI app. This object is used to keep track of config state, and is eventually used to parse the command
--- line flags into usable data objects.
--- @class CLIApp
CLIApp = {}

--- Represents a CLI option. This object can optionally be used to provide extra config to a flag or option.
--- @class CLIOption
CLIOption = {}

--- Add a flag, i.e. a `--flag` that doesn't take an explicit value. Usually used for bool toggles.
---
--- @param flag string A string representing the flag, i.e. `-v,--verbose`.
--- @param dataBox moonbeam.lang.Box A Box that's used for storing the actual value the flag gets.
--- @param flagDescription string A description of the flag.
--- @return CLIOption
function CLIApp:addFlag(flag, dataBox, flagDescription) end

--- Add an option, i.e. a `--flag "user-provided value"`.
---
--- @param option string A string representing the option, i.e. `-n,--nuclear-launch-code-location`.
--- @param dataBox moonbeam.lang.Box A Box that's used for storing the actual value the flag gets.
--- @param optionDescription string A description of the flag.
--- @return CLIOption
function CLIApp:addOption(option, dataBox, optionDescription) end

--- Parses the provided <args> via CLI12. This is only defined for the root app. This will throw an error if you use it
--- on an app returned by add_subcommand.
--- @param args table<string>
function CLIApp:parse(args) end

--- Create a CLI12 app (lua-representation: CLIApp).
---
--- @param name string A name to show in the `--help`
--- @param description string A description to show in the `--help`
--- @return CLIApp
function createApp(name, description) end

return {
    ["createApp"] = createApp
}
