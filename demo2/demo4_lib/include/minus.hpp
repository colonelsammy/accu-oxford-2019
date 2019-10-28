#pragma once
#include <expr.hpp>

namespace demo4
{
  struct Minus : public Expr
  {
    Minus(Expr const* l, Expr const* r);

    variant_types type_id() const noexcept override
    {
      variant_types ty = *this;
      return ty;
    }

    Expr const* lhs = nullptr;
    Expr const* rhs = nullptr;
  };
}
