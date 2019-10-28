#pragma once
#include <constant.hpp>
#include <plus.hpp>
#include <minus.hpp>
#include <ostream>

namespace demo1
{
  void print(std::ostream& os, Constant const& expr);
  void print(std::ostream& os, Plus const& expr);
  void print(std::ostream& os, Minus const& expr);
}
