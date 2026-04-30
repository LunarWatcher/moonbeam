add_library(moonbeam SHARED

    moonbeam/Moonbeam.cpp
    moonbeam/common/IterUtils.cpp

    moonbeam/json/Json.cpp

    moonbeam/system/Process.cpp

    moonbeam/fs/Filesystem.cpp
)
set_target_properties(
    moonbeam PROPERTIES PREFIX ""
)

target_link_libraries(moonbeam PUBLIC
    stc::stc
    nlohmann_json::nlohmann_json
    ${LUA_LIBRARIES}
)
target_include_directories(moonbeam PUBLIC
    ${LUA_INCLUDE_DIR}
    ./
)

install(
    TARGETS moonbeam
    DESTINATION lib/lua/5.4/
)
