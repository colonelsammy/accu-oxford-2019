add_executable(benchmark_demo4
  main.cpp
)

target_include_directories(benchmark_demo4 PUBLIC .)
target_compile_features(benchmark_demo4 PRIVATE cxx_std_17)
target_link_libraries(benchmark_demo4 PRIVATE demo4_lib benchmark_lib)
