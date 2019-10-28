add_executable(benchmark_demo1
  variant_visit.hpp
  virtualfn.hpp
  main.cpp
  variant_visit.cpp
  virtualfn.cpp
)

target_include_directories(benchmark_demo1 PUBLIC .)
target_compile_features(benchmark_demo1 PRIVATE cxx_std_17)
target_link_libraries(benchmark_demo1 PRIVATE demo_lib benchmark_lib)
