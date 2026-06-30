local lang = require("moonbeam.lang");
local lu = require("luaunit");

-- These tests test the default initializations
TestBox = {
    testInt = function()
        local int = lang.newIntBox()
        lu.assertEquals(0, int:unwrap())
    end,
    testDouble = function()
        -- TODO: this technically doesn't differentiate ints from doubles. Use math.type or something instead (same for
        -- the int test actually)
        local double = lang.newDoubleBox()
        lu.assertEquals(0.0, double:unwrap())
    end,
    testBool = function()
        local bool = lang.newBoolBox()
        lu.assertFalse(bool:unwrap())
    end,
    testString = function()
        local string = lang.newStringBox()
        lu.assertEquals("", string:unwrap())
    end,
    testStringVec = function()
        local strVec = lang.newStringVecBox()
        lu.assertEquals({}, strVec:unwrap())
    end,
}
