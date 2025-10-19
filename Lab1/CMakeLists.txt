cmake_minimum_required(VERSION 3.10)
project(OOP_LAB_1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=uninitialized")

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.0
  TLS_VERIFY false
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(include)
add_library(euclid_lib src/euclid.cpp)

add_executable(euclid main.cpp)
target_link_libraries(euclid PRIVATE euclid_lib)

enable_testing()
add_executable(euclid_tests test/tests.cpp)
target_link_libraries(euclid_tests euclid_lib gtest_main)
add_test(NAME euclid_tests COMMAND euclid_tests)