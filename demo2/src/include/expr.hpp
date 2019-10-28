#pragma once
#include <typelist.hpp>
using namespace typelist;

namespace demo2
{
  struct Expr
  {
    virtual ~Expr() = default;
    virtual magic_type type_id() const noexcept = 0;
  };

  struct Constant;
  struct Plus;
  struct Minus;

  using Types = tuple<Constant, Plus, Minus>;
}
