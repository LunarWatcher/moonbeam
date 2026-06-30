---@meta

local fs = {}

---Finds a filename in a list of paths, or nil if not found
---
---@param searchPath string[]
---@param filename string
---@return string
function fs.findInPath(searchPath, filename) end


--- Returns the current working directory
--- @return string
function fs.cwd() end

return fs
