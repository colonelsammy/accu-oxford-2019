#pragma once
#include <variant>
#include <any>

namespace variant_visit
{
  struct Constant
  {
    Constant(double v) : value(v) {}
    double value = 0.0;
  };

  struct Plus
  {
    template <typename E>
    Plus(E const& l, E const& r)
      : lhs(l), rhs(r)
    {}

    std::any lhs;
    std::any rhs;
  };

  struct Minus
  {
    template <typename E>
    Minus(E const& l, E const& r)
      : lhs(l), rhs(r)
    {}

    std::any lhs;
    std::any rhs;
  };

  using Expr = std::variant<Constant, Plus, Minus>;
}
