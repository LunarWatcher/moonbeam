include(FetchContent)
FetchContent_declare(luaunit
    GIT_REPOSITORY https://github.com/bluebird75/luaunit.git
    # v3.5
    GIT_TAG 9678c933e71cb26adcdfa6cf1baceb926398eb48
)
FetchContent_MakeAvailable(
    luaunit
)

add_custom_target(test
    COMMAND lua5.4 "${CMAKE_CURRENT_SOURCE_DIR}/src/suite.lua" -v
    DEPENDS moonbeam
    COMMENT "Test moonbeam"
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    VERBATIM
)
