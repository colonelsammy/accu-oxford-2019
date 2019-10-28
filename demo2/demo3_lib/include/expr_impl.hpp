#pragma once
#include <typelist.hpp>
#include <variant>
using namespace typelist;

#include <constant.hpp>
#include <plus.hpp>
#include <minus.hpp>

namespace demo3
{
  struct Expr : std::variant<Constant, Plus, Minus>
  {
    using variant::variant;
  };

  template<class T> struct variant_types_list;

  template<class... Ts>
  struct variant_types_list<std::variant<Ts...>> {
    using type = tuple<Ts...>;
  };
  template<class T> using variant_types_list_t = typename variant_types_list<T>::type;

  using Types = variant_types_list_t<std::decay_t<Expr::variant>>;
}

namespace std {
  template <>
  struct variant_size<demo3::Expr> : variant_size<demo3::Expr::variant> {};
  template <std::size_t I>
  struct variant_alternative<I, demo3::Expr> : variant_alternative<I, demo3::Expr::variant> {};
}
