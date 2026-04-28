cmake_minimum_required(VERSION 3.27)
project(moonbeam)

set (CMAKE_CXX_STANDARD 23)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if (NOT ENABLE_CONAN)
    list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
endif()


set(MAGPIE_STANDALONE ON)

if (NOT WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
endif()

option(MOONBEAM_BUILD_TESTS "Whether or not to build tests" ON)

message(STATUS "Moonbeam build configuration:")
message(STATUS "\t- Tests: ${MOONBEAM_BUILD_TESTS}")

include(FetchContent)
FetchContent_Declare(stc
    GIT_REPOSITORY https://github.com/LunarWatcher/stc
)
FetchContent_MakeAvailable(
    stc
)

find_package(Lua 5.4 REQUIRED)

add_subdirectory(src)

if (MOONBEAM_BUILD_TESTS)
    add_subdirectory(tests EXCLUDE_FROM_ALL)
endif()
