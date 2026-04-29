#pragma once

#include "Process.hpp"

namespace moonbeam::system {

inline const static luaL_Reg functions[] = {
    { "process", system::process },
    { nullptr, nullptr },
};

}
