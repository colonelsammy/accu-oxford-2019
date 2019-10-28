#pragma once
#include <operation.hpp>
#include <eval_ops.hpp>
//#include <print_ops.hpp>

namespace demo1
{
  template <typename T>
  void invoke_eval::invoke(const T& expr)
  {
    result = eval(expr);
  }

  //template <typename T>
  //void invoke_print::invoke(const T& expr)
  //{
  //  print(os, expr);
  //}

  template <typename T>
  void
    magic_type::call(T const* obj, operations& ops)
  {
    T const* callable_t = static_cast<T const*>(obj);
    switch (ops.index())
    {
    case 0:
      std::get<0>(ops).invoke(*callable_t);
      break;
    //case 1:
    //  std::get<1>(ops).invoke(*callable_t);
    //  break;
    }
  }
}