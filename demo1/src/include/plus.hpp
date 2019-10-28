#pragma once
#include <expr.hpp>

namespace demo1
{
  struct Plus : public Expr
  {
    Plus(Expr const* l, Expr const* r);

    magic_type invoke() const override
    {
      return magic_type(this);
    }

    Expr const* lhs = nullptr;
    Expr const* rhs = nullptr;
  };
}
