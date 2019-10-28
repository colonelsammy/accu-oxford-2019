add_library(demo_lib
  # magic...
  include/operation.hpp
  include/invoke_operation.hpp

  # demo code
  include/constant.hpp
  include/expr.hpp
  include/plus.hpp
  include/operation_definitions.hpp
  include/eval_ops.hpp
  demo_eval.cpp
  constant.cpp
  plus.cpp

  # second demo...
  #include/minus.hpp
  #minus.cpp

  # third demo...
  #include/print_ops.hpp
  #demo_print.cpp
)

# settings for msvc
string(APPEND compiler_msvc "$<AND:$<COMPILE_LANGUAGE:CXX>,$<CXX_COMPILER_ID:MSVC>>")
string(APPEND build_msvc "$<$<BUILD_INTERFACE:${compiler_msvc}>:/WX;/W4>")
string(APPEND compiler_msvc_release "$<AND:${compiler_msvc},$<CONFIG:release>>")
string(APPEND build_msvc_release "$<$<BUILD_INTERFACE:${compiler_msvc_release}>:/O2>")

# setting for gcc
string(APPEND compiler_gnu "$<AND:$<COMPILE_LANGUAGE:CXX>,$<CXX_COMPILER_ID:GNU>>")
string(APPEND build_gnu "$<$<BUILD_INTERFACE:${compiler_gnu}>:-Wall;-Wextra;-Werror>")
string(APPEND compiler_gnu_release "$<AND:${compiler_gnu},$<CONFIG:release>>")
string(APPEND build_msvc_release "$<$<BUILD_INTERFACE:${compiler_gnu_release}>:-O3>")

target_compile_options(demo_lib PUBLIC
  ${build_gnu}
  ${build_gnu_release}
  ${build_msvc}
  ${build_msvc_release}
)

target_include_directories(demo_lib PUBLIC include)
target_compile_features(demo_lib PRIVATE cxx_std_17)
