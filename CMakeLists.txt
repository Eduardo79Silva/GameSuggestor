cmake_minimum_required(VERSION 3.14)
project(SteamSuggestor VERSION 1.0.0 LANGUAGES CXX)

# Use C++17 and export compile commands.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Force output directories for executables and libraries.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

if(MSVC)
  add_compile_options(/W4)
else()
  add_compile_options(-Wall -Wextra -Werror -pedantic -O2)
endif()

# Add include directories.
include_directories(
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
  "${CMAKE_CURRENT_SOURCE_DIR}/lib"
  "${CMAKE_CURRENT_SOURCE_DIR}/lib/curl/include"
  "${CMAKE_CURRENT_SOURCE_DIR}/lib/gtest/googletest/include"
)

# Collect all source files from src/.
file(GLOB SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_library(GameSuggestorLib ${SRC_FILES})

# Create the main executable target.
add_executable(SteamSuggestor ${SRC_FILES})
set_target_properties(SteamSuggestor PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(MSVC)
  target_link_libraries(SteamSuggestor PRIVATE 
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/curl/bin/libcurl.lib"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/gtest/build/lib/gtest.lib"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/gtest/build/lib/gtest_main.lib"
  )
else()
  # For MinGW, add link directories (which can handle spaces correctly) before linking.
  link_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/curl/lib"
  )
  target_link_libraries(GameSuggestorLib PUBLIC -lcurl)
  target_link_libraries(SteamSuggestor PRIVATE GameSuggestorLib -pthread)
endif()

# Optionally, add a test executable if test sources exist.
file(GLOB TEST_SRC "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp")
if(TEST_SRC)
  add_executable(run_tests ${TEST_SRC})
  target_include_directories(run_tests PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/curl/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/gtest/googletest/include"
  )
  if(MSVC)
    target_link_libraries(run_tests PRIVATE
      "${CMAKE_CURRENT_SOURCE_DIR}/lib/curl/bin/libcurl.lib"
      "${CMAKE_CURRENT_SOURCE_DIR}/lib/gtest/build/lib/gtest.lib"
      "${CMAKE_CURRENT_SOURCE_DIR}/lib/gtest/build/lib/gtest_main.lib"
    )
  else()
    # Specify the full paths to the Google Test libraries
    set(GTEST_LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/gtest/lib")
    target_link_libraries(run_tests PRIVATE 
      -lcurl
      "${GTEST_LIB_DIR}/libgtest.dll.a"
      "${GTEST_LIB_DIR}/libgtest_main.dll.a"
      GameSuggestorLib
      -pthread
    )
  endif()
  set_target_properties(run_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
  enable_testing()
  add_test(NAME UnitTests COMMAND run_tests)
endif()

# Installation rule for the main executable.
install(TARGETS SteamSuggestor DESTINATION bin)

