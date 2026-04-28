local moonbeam = require("moonbeam");

-- TODO: seeing as moonbeam.system is nil, how do I want to go about this?
-- I probably want to separate the imports since I want to be able to not have to import the entirety of moonbeam for
-- like a single file or whatever, so splitting it up likely makes sense. The DLL is still going to be loaded in its
-- entirety, but that's because I can't be bothered dealing with multiple versions of it and shit
print(moonbeam)
print(moonbeam.system)
print(require("moonbeam.system"))

print(moonbeam.test_global)

function TestProcess()
   lu.assertEquals(
      1, 1
   )
end
