add_executable(demo2
  main.cpp
)

target_include_directories(demo2 PUBLIC include)
target_compile_features(demo2 PRIVATE cxx_std_17)
target_link_libraries(demo2 PRIVATE demo_lib)
