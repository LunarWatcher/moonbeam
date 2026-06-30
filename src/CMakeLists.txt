add_library(moonbeam SHARED
    ## Internals and infra
    moonbeam/Moonbeam.cpp
    moonbeam/common/IterUtils.cpp

    ## Modules

    # CLI module
    moonbeam/cli/CLI.cpp

    # JSON module
    moonbeam/json/Json.cpp

    # Lang extensions module
    moonbeam/lang/LangExtensions.cpp

    # Process module
    moonbeam/system/Process.cpp

    # Filesystem module
    moonbeam/fs/Filesystem.cpp
)
set_target_properties(
    moonbeam PROPERTIES PREFIX ""
)

target_link_libraries(moonbeam PUBLIC
    stc::stc
    nlohmann_json::nlohmann_json
    CLI12::CLI12
    ${LUA_LIBRARIES}
)
target_include_directories(moonbeam PUBLIC
    ${LUA_INCLUDE_DIR}
    ./
)

install(
    TARGETS moonbeam
    DESTINATION lib/lua/${LUA_BINARY_NAME}/
)
