local moonjson = require("moonbeam.json");
local lu = require("luaunit");

TestJson = {
    testWorks = function()
        local object = moonjson.parse('{"test": "hi", "nested": [6, 9]}')
        lu.assertEquals(
            object,
            {
                ["test"] = "hi",
                ["nested"] = { 6, 9 }
            }
        )
    end,
}

