os = require("os")

-- I don't like this, but this seems to be the only way to set the path.
-- setting the variable from CMake doesn't work because, as far as I can tell, cmake simply does not support this
-- particular use-case. 
package.path = "../build/_deps/luaunit-src/?.lua;./src/?.lua;" .. package.path;
package.cpath = "../build/lib/?.so;" .. package.cpath;

print(io.popen("pwd"):read())

lu = require("luaunit");

require "system.test_process"

os.exit(lu.LuaUnit.run())
