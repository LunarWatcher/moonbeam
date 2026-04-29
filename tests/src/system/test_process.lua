local moonsys = require("moonbeam.system");
local lu = require("luaunit");

TestErrors = {
    testArgumentValidation = function()
        lu.assertErrorMsgContentEquals(
            "This function requires at least one argument",
            moonsys.process
        );
    end,
    testArgumentTypeValidation = function()
        lu.assertErrorMsgContains(
            "string expected, got number",
            moonsys.process,
            "test",
            69
        )
    end,
}

-- Largely mirrored from the stc tests
TestBaseLineFunctionality = {
    tearDown = function()
        -- Need to make sure we properly close everything
        collectgarbage();
    end,
    testOutput = function()
        local proc = moonsys.process(
            "/usr/bin/bash",
            "-c",
            "echo -n 'good girl :3'"
        )
        lu.assertIsUserdata(proc);
        lu.assertEquals(
            proc:block(),
            0
        );
        lu.assertEquals(
            proc:read(),
            "good girl :3"
        );
    end,
    testInput = function()
        local proc = moonsys.process(
            "/usr/bin/bash",
            "-c",
            "cat"
        );
        lu.assertIsUserdata(proc);
        proc:write("good girl :3");
        -- Closing stdin signals that `cat` has nothing more to read
        proc:closeStdin();
        lu.assertEquals(
            proc:block(),
            0
        );
        lu.assertEquals(
            proc:read(),
            "good girl :3"
        );
    end,
    testInputTestCorrectness = function()
        -- This test verifies that the pipes used in the previous test indeed are separate. if `stdin` is piped to
        -- `stdout`, we expect this test to show both the echo string and the input string
        local proc = moonsys.process(
            "/usr/bin/bash",
            "-c",
            "echo -n 'trans rights are human rights' && sleep 1"
        );
        lu.assertIsUserdata(proc);
        proc:write("good girl :3");
        lu.assertEquals(
            proc:block(),
            0
        );
        lu.assertEquals(
            proc:read(),
            "trans rights are human rights"
        );
    end,
}

