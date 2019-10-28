#pragma once
#include <functional>
#include <typelist.hpp>
using namespace typelist;

namespace demo4
{
  struct Constant;
  struct Plus;
  struct Minus;

  using variant_types = std::variant<
    std::reference_wrapper<const Constant>,
    std::reference_wrapper<const Plus>,
    std::reference_wrapper<const Minus>
  >;

  struct Expr
  {
    virtual ~Expr() = default;
    virtual variant_types type_id() const noexcept = 0;
  };
}
