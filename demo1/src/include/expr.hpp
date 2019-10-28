#pragma once
#include <operation.hpp>

namespace demo1
{
  struct Expr
  {
    virtual ~Expr() = default;
    virtual magic_type invoke() const = 0;
  };
}
