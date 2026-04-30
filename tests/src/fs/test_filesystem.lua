local moonfs = require("moonbeam.fs");
local lu = require("luaunit");

TestFilesystem = {
    testPathSearch = function()
        local searchPath = {}
        for i in string.gmatch(os.getenv("PATH"), "[^:]+") do
            searchPath[#searchPath + 1] = i
        end
        lu.assertTrue(
            #searchPath > 0,
            "Failed to parse PATH"
        )
        local path = moonfs.findInPath(
            searchPath,
            "lua5.4"
        )
        lu.assertEquals(
            path,
            "/usr/bin/lua5.4"
        )
    end,
}
