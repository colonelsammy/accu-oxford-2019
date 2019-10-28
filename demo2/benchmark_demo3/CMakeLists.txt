add_executable(benchmark_demo3
  main.cpp
)

target_include_directories(benchmark_demo3 PUBLIC .)
target_compile_features(benchmark_demo3 PRIVATE cxx_std_17)
target_link_libraries(benchmark_demo3 PRIVATE demo3_lib benchmark_lib)
