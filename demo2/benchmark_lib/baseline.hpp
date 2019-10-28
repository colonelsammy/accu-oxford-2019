#pragma once

namespace baseline
{
  struct Constant
  {
    Constant(double v) : value(v) {}
    double value = 0.0;
  };

  struct Plus
  {
    Plus(Constant const* l, Constant const* r) : lhs(l), rhs(r) {}
    Constant const* lhs = nullptr;
    Constant const* rhs = nullptr;
  };

  struct Minus
  {
    Minus(Plus const* l, Constant const* r) : lhs(l), rhs(r) {}
    Plus const* lhs = nullptr;
    Constant const* rhs = nullptr;
  };

}
