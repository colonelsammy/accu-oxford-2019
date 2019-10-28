add_executable(demo1
  main.cpp
)

target_include_directories(demo1 PUBLIC include)
target_compile_features(demo1 PRIVATE cxx_std_17)
target_link_libraries(demo1 PRIVATE demo_lib)
