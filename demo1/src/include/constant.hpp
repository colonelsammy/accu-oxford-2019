#pragma once
#include <expr.hpp>

namespace demo1
{
  struct Constant : public Expr
  {
    Constant(double v);

    magic_type invoke() const override
    {
      return magic_type(this);
    }

    double value = 0.0;
  };
}