add_library(demo_lib
  # demo code
  include/constant.hpp
  include/expr.hpp
  include/plus.hpp
  demo_eval.cpp
  constant.cpp
  plus.cpp

  # second demo...
  include/minus.hpp
  minus.cpp

  # third demo...
  demo_print.cpp
)

target_include_directories(demo_lib PUBLIC include)
target_compile_features(demo_lib PRIVATE cxx_std_17)
target_link_libraries(demo_lib PUBLIC typelist)
