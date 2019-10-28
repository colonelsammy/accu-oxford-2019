#pragma once
#include <expr.hpp>

namespace demo2
{
  struct Constant : public Expr
  {
    Constant(double v);

    magic_type type_id() const noexcept override
    {
      return magic_type::make_magic_type<Types>(this);
    }

    double value = 0.0;
  };
}