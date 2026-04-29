--- @meta

--- Represents an stc::Unix::Process object; this is userdata
--- @class Process
Process = {}

--- Reads the contents of the buffer, and resets the internal buffer to avoid repeating the same text multiple times.
--- @return string
function Process:read() end

--- Writes a string to stdin
--- @param content string
--- @return nil
function Process:write(content) end

--- Closes the stdin file descriptor. This is required for certain programs that accept stdin to tell that the stdin
--- stream has ended, and that it should start ending itself too.
--- @return nil
function Process:closeStdin() end

--- Blocks the process and waits for it to exit. Returns the exit code
--- @return number
function Process:block() end

--- Starts a process.
--- 
--- @param command string[]
--- @param env? table<string, string>?
--- @return Process
function process(command, env) end

return {
    ["process"] = process
}
