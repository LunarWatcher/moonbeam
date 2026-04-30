---@meta

---Finds a filename in a list of paths, or nil if not found
---
---@param searchPath string[]
---@param filename string
---@return string
function findInPath(searchPath, filename) end

return {
    ["findInPath"] = findInPath
}
