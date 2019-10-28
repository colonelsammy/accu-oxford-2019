add_library(typelist
  # magic...
  include/typelist.hpp
  typelist.cpp
)

# settings for msvc
string(APPEND compiler_msvc "$<AND:$<COMPILE_LANGUAGE:CXX>,$<CXX_COMPILER_ID:MSVC>>")
string(APPEND build_msvc "$<$<BUILD_INTERFACE:${compiler_msvc}>:/WX;/W4>")
string(APPEND compiler_msvc_release "$<AND:${compiler_msvc},$<CONFIG:release>>")
string(APPEND build_msvc_release "$<$<BUILD_INTERFACE:${compiler_msvc_release}>:/O2>")
#string(APPEND build_msvc_release "$<$<BUILD_INTERFACE:${compiler_msvc_release}>:/Ox>")

# setting for gcc
string(APPEND compiler_gnu "$<AND:$<COMPILE_LANGUAGE:CXX>,$<CXX_COMPILER_ID:GNU>>")
string(APPEND build_gnu "$<$<BUILD_INTERFACE:${compiler_gnu}>:-Wall;-Wextra;-Werror>")
string(APPEND compiler_gnu_release "$<AND:${compiler_gnu},$<CONFIG:release>>")
string(APPEND build_msvc_release "$<$<BUILD_INTERFACE:${compiler_gnu_release}>:-O3>")

target_compile_options(typelist PUBLIC
  ${build_gnu}
  ${build_gnu_release}
  ${build_msvc}
  ${build_msvc_release}
)

target_include_directories(typelist PUBLIC include)
target_compile_features(typelist PRIVATE cxx_std_17)
