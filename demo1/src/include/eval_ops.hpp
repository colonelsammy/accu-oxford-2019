#pragma once
#include <constant.hpp>
#include <plus.hpp>
//#include <minus.hpp>

namespace demo1
{
  double eval(Constant const& expr);
  double eval(Plus const& expr);
  //double eval(Minus const& expr);
}
