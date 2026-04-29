add_library(moonbeam SHARED

    moonbeam/Moonbeam.cpp
    moonbeam/common/IterUtils.cpp

    moonbeam/system/Process.cpp
)
set_target_properties(
    moonbeam PROPERTIES PREFIX ""
)

target_link_libraries(moonbeam PUBLIC stc::stc ${LUA_LIBRARIES})
target_include_directories(moonbeam PUBLIC
    ${LUA_INCLUDE_DIR}
    ./
)
