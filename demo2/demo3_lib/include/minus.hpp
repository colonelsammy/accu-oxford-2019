#pragma once
#include <expr.hpp>

namespace demo3
{
  struct Minus
  {
    Minus(Expr const* l, Expr const* r);

    Expr const* lhs = nullptr;
    Expr const* rhs = nullptr;
  };
}
