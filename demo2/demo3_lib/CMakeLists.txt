add_library(demo3_lib
  # demo code
  include/constant.hpp
  include/expr.hpp
  include/expr_impl.hpp
  include/plus.hpp
  demo_eval.cpp
  constant.cpp
  plus.cpp

  # second demo...
  include/minus.hpp
  minus.cpp

  # third demo...
  #demo_print.cpp
)

target_include_directories(demo3_lib PUBLIC include)
target_compile_features(demo3_lib PRIVATE cxx_std_17)
target_link_libraries(demo3_lib PUBLIC typelist)
