add_executable(demo3
  main.cpp
)

target_include_directories(demo3 PUBLIC include)
target_compile_features(demo3 PRIVATE cxx_std_17)
target_link_libraries(demo3 PRIVATE demo3_lib)
