#pragma once

#include <lua.hpp>

#include "Process.hpp"

namespace moonbeam::system {

inline const static luaL_Reg functions[] = {
    { "nonCaptureProcess", system::nonCaptureProcess },
    { "process", system::process },
    { nullptr, nullptr },
};

}
