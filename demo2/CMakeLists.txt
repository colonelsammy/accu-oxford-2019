# minimum required version of cmake
cmake_minimum_required(VERSION 3.11...3.14 FATAL_ERROR)

message(STATUS "You are using CMake ${CMAKE_CACHE_MAJOR_VERSION}.${CMAKE_CACHE_MINOR_VERSION}.${CMAKE_CACHE_PATCH_VERSION}")

if(NOT WIN32)
  MESSAGE(STATUS "You are building a ${CMAKE_BUILD_TYPE} build on Linux.")
endif()

project(demo2 VERSION 1.0.0 LANGUAGES CXX)

#disable in-place builds
if(${CMAKE_BINARY_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
  message(FATAL_ERROR "Error:  In-place builds are not supported. Please create a separate build directory")
endif()

set(default_build_type "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(typelist)
add_subdirectory(src)
add_subdirectory(demo)
add_subdirectory(demo3_lib)
add_subdirectory(demo3)
add_subdirectory(demo4_lib)
add_subdirectory(demo4)
add_subdirectory(benchmark_lib)
add_subdirectory(benchmark_demo)
add_subdirectory(benchmark_demo3)
add_subdirectory(benchmark_demo4)
