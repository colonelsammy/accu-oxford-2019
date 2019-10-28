add_executable(benchmark_demo2
  main.cpp
)

target_include_directories(benchmark_demo2 PUBLIC .)
target_compile_features(benchmark_demo2 PRIVATE cxx_std_17)
target_link_libraries(benchmark_demo2 PRIVATE demo_lib benchmark_lib)
