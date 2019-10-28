add_executable(demo4
  main.cpp
)

target_include_directories(demo4 PUBLIC include)
target_compile_features(demo4 PRIVATE cxx_std_17)
target_link_libraries(demo4 PRIVATE demo4_lib)
