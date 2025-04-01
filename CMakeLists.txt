cmake_minimum_required(VERSION 3.14)
project(SteamSuggestor VERSION 1.0.0 LANGUAGES CXX)

# Use C++17 and export compile commands.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# flags

# files

# include
include_directories( ./include ./src ./libs ./libs/gtest/googletest/include )

# target
file(GLOB SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable( GameSuggestor ${SRC_FILES})

find_package(curl)

if(CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIR})
    target_link_libraries(GameSuggestor ${CURL_LIBRARY})
else(CURL_FOUND)
    message(FATAL_ERROR "CURL library not found")
endif(CURL_FOUND)

# external libs - 3rd party libs
add_subdirectory( ./libs/gtest/ )
target_link_libraries( GameSuggestor curl gtest )


