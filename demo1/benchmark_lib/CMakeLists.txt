include(CTest)
include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.8.1
)

FetchContent_Declare(
  benchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG v1.5.0
)

FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
  FetchContent_Populate(googletest)
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  set(gtest_disable_pthreads ON CACHE BOOL "" FORCE)
  add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
  message(STATUS "Gtest dirs: ${googletest_SOURCE_DIR} ${googletest_BINARY_DIR}")
  if(MSVC)
    foreach(_tgt gtest gtest_main gmock gmock_main)
      target_compile_definitions(${_tgt}
        PRIVATE "_SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING")
    endforeach()
  endif()
endif()

FetchContent_GetProperties(benchmark)
if(NOT benchmark_POPULATED)
  FetchContent_Populate(benchmark)
  set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
  set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "" FORCE)
  add_subdirectory(${benchmark_SOURCE_DIR} ${benchmark_BINARY_DIR})
  message(STATUS "Benchmark dirs: ${benchmark_SOURCE_DIR} ${benchmark_BINARY_DIR}")
endif()

add_library(benchmark_lib
  baseline.hpp
  exception.hpp
  baseline.cpp
  exception.cpp
)

target_include_directories(benchmark_lib PUBLIC .)
target_compile_features(benchmark_lib PUBLIC cxx_std_17)
target_link_libraries(benchmark_lib PUBLIC benchmark)
