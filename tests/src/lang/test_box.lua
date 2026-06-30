local lang = require("moonbeam.lang");
local lu = require("luaunit");

-- These tests test the default initializations
TestBox = {
    testInt = function()
        local int = lang.newIntBox()
        lu.assertEquals(int:unwrap(), 0)
    end,
    testDouble = function()
        -- TODO: this technically doesn't differentiate ints from doubles. Use math.type or something instead (same for
        -- the int test actually)
        local double = lang.newDoubleBox()
        lu.assertEquals(double:unwrap(), 0.0)
    end,
    testBool = function()
        local bool = lang.newBoolBox()
        lu.assertEquals(bool:unwrap(), false)
    end,
    testString = function()
        local string = lang.newStringBox()
        lu.assertEquals(string:unwrap(), "")
    end,
}
