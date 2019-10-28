#pragma once
#include <expr.hpp>

namespace demo2
{
  struct Plus : public Expr
  {
    Plus(Expr const* l, Expr const* r);

    magic_type type_id() const noexcept override
    {
      return magic_type::make_magic_type<Types>(this);
    }

    Expr const* lhs = nullptr;
    Expr const* rhs = nullptr;
  };
}
