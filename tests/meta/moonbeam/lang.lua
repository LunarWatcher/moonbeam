--- @meta

--- Represents a Box. This is a userdata object.
---
--- Boxes are used for interaction with native C/C++ APIs that require references. Since Lua doesn't directly work with
--- references, this internally wraps a native datatype for forwarding to said APIs.
---
--- Note that due to how this class is used, this box may be sensitive to the lifespan of other classes that aren't
--- covered by Lua's GC cycle. If you do not ensure that the lifecycle of the Box is as long as the function or object
--- it's passed to, there will be dragons.
---
--- Example of correct usage with moonbeam.cli:
--- ```lua
--- local isVerbose = lang.newBox("bool")
--- -- ...
--- app:addFlag(
---     "-v,--verbose",
---     isVerbose,
---     "Description"
--- )
--- -- If isVerbose is discarded prior to the parse call, calling app:parse will cause a segfault.
--- app:parse()
--- -- Now, isVerbose can be discarded. Obviously, we want to extract its value first, or the whole exercise of having
--- -- such a variable was a waste of time.
--- if (isVerbose:unwrap() == true)
---     -- Do whatever
--- end
--- ```
---
--- Note that the Box may also be discarded if you do _not_ call `app:parse()` (in the case of moonbeam.cli); the
--- discard requirements are only in effect when you plan to use it, and haven't yet used it.
---
--- Boxes, at this time, do not offer type-based differentiation from lua code, largely because the current-generation
--- LSP servers are far too dumb to allow connecting a variable's content to a return type.
---
--- @class Box<T>
Box = {}

--- Returns the native value contained within the box.
--- @return T
function Box:unwrap() end

--- Creates a new bool Box.
--- @return Box<boolean>
function newBoolBox() end

--- Creates a new string Box
--- @return Box<string>
function newStringBox() end

--- Creates a new int Box
--- @return Box<number>
function newIntBox() end

--- Creates a new double Box
--- @return Box<number>
function newDoubleBox() end

return {
    ["newBoolBox"] = newBoolBox,
    ["newStringBox"] = newStringBox,
    ["newIntBox"] = newIntBox,
    ["newDoubleBox"] = newDoubleBox,
}
