#pragma once
#include <expr.hpp>

namespace demo4
{
  struct Constant : public Expr
  {
    Constant(double v);

    variant_types type_id() const noexcept override
    {
      variant_types ty = *this;
      return ty;
    }

    double value = 0.0;
  };
}