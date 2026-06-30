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

        app:addFlag(
            "-v,--verbose",
            boolBox,
            "Description"
        )

        lu.assertFalse(boolBox:unwrap())
        app:parse({ "/usr/bin/lua", "-v" })
        lu.assertTrue(boolBox:unwrap())
    end,
    testRequiredFlags = function()
        local app = createTestApp()

        local boolBox = moonlang:newBoolBox()

        local verboseOpt = app:addFlag(
            "-v,--verbose",
            boolBox, -- TODO: why does this not trigger an error with newStringBox instead of newBoolBox?
            "Description"
        )
        verboseOpt:required()

        lu.assertErrorMsgContains(
            "--verbose is required",
            app.parse, app, {"/usr/bin/lua"}
        )
    end,
    testStringOpts = function()
        local app = createTestApp()

        local stringBox = moonlang:newStringBox()

        app:addOption(
            "--flag",
            stringBox,
            "Description"
        )

        app:parse({"/usr/bin/lua", "--flag", "owo x3"});
        lu.assertEquals(
            stringBox:unwrap(),
            "owo x3"
        )
    end,
    testDefaultOptions = function()
        local app = createTestApp()

        local stringBox = moonlang:newStringBox()

        local flagOpt = app:addOption(
            "--flag",
            stringBox,
            "Description"
        )
        flagOpt:default("owo x3")

        app:parse({"/usr/bin/lua"});
        lu.assertEquals(
            stringBox:unwrap(),
            "owo x3"
        )
    end,
}
