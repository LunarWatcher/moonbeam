local mooncli = require("moonbeam.cli")
local moonlang = require("moonbeam.lang")
local lu = require("luaunit")

local function createTestApp()
    local app = mooncli.createApp("test", "description")
    return app
end

TestCLI = {
    testCommandLineParsing = function()
        local app = createTestApp()

        local boolBox = moonlang:newBoolBox()

        local opt = app:addFlag(
            "-v,--verbose",
            boolBox,
            "Description"
        )
        print(type(opt))
        print(getmetatable(opt).__name)
    end,
}
