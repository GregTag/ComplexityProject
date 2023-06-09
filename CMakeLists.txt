cmake_minimum_required(VERSION 3.20)
project(ComplexityProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(FLAGS -O0 -g -fno-omit-frame-pointer -fsanitize=address,undefined)
else()
    set(FLAGS -O2)
endif()

add_compile_options(${FLAGS})
add_link_options(${FLAGS})

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG main
)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
    benchmark
    GIT_REPOSITORY https://github.com/google/benchmark.git
    GIT_TAG main
)
FetchContent_MakeAvailable(benchmark)

FetchContent_Declare(
   ortools
   URL https://github.com/google/or-tools/releases/download/v9.6/or-tools_amd64_ubuntu-22.04_cpp_v9.6.2534.tar.gz
   DOWNLOAD_EXTRACT_TIMESTAMP true
)
FetchContent_MakeAvailable(ortools)
set(CMAKE_PREFIX_PATH ${ortools_SOURCE_DIR})
find_package(ortools CONFIG REQUIRED)

include_directories(.)

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE TESTS tests/*.cpp)
file(GLOB_RECURSE BENCHMARK benchmark/*.cpp)

add_executable(spanning_tree main.cpp ${SOURCES})

add_executable(workloads workloads.cpp ${SOURCES})

add_executable(test ${TESTS} ${SOURCES})
target_link_libraries(test gtest_main gtest ortools::ortools)
target_compile_definitions(test PRIVATE DATA_PREFIX="${CMAKE_CURRENT_SOURCE_DIR}/data")

add_executable(perfomance ${BENCHMARK} ${SOURCES})
target_link_libraries(perfomance benchmark_main benchmark)
