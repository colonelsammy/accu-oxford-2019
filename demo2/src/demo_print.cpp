#include <constant.hpp>
#include <plus.hpp>
#include <minus.hpp>

namespace demo_double_dispatch
{
  void print(std::ostream& os, demo2::Constant const& expr);
  void print(std::ostream& os, demo2::Plus const& expr);
  void print(std::ostream& os, demo2::Minus const& expr);

  void print(std::ostream& os, demo2::Constant const& expr)
  {
    os << expr.value;
  }

  template <typename LHS, typename RHS>
  void print_plus(std::ostream&, LHS const&, RHS const&)
  {
    throw std::runtime_error("invalid print");
  }

  void print_plus(std::ostream& os, demo2::Constant const& lhs, demo2::Constant const& rhs)
  {
    os << lhs.value;
    os << "+";
    os << rhs.value;
  }

  void print(std::ostream& os, demo2::Plus const& expr)
  {
    return dispatch<demo2::Types>([&os](auto lhs, auto rhs)
      { print_plus(os, lhs, rhs); },
      std::array{ expr.lhs->type_id(), expr.rhs->type_id() });
  }

  template <typename LHS, typename RHS>
  void print_minus(std::ostream&, LHS const&, RHS const&)
  {
    throw std::runtime_error("invalid eval");
  }

  void print_minus(std::ostream& os, demo2::Constant const& lhs, demo2::Constant const& rhs)
  {
    os << lhs.value;
    os << "-";
    os << rhs.value;
  }

  void print_minus(std::ostream& os, demo2::Plus const& lhs, demo2::Constant const& rhs)
  {
    dispatch<demo2::Types>([&os](auto expr)
      { print(os, expr); },
      std::array{ lhs.type_id() });
    os << "-";
    os << rhs.value;
  }

  void print(std::ostream& os, demo2::Minus const& expr)
  {
    dispatch<demo2::Types>([&os](auto lhs, auto rhs)
      { print_minus(os, lhs, rhs); },
      std::array{ expr.lhs->type_id(), expr.rhs->type_id() });
  }

  void demo_print(std::ostream& os, demo2::Expr const& expr)
  {
    dispatch<demo2::Types>([&os](auto local_expr)
      { print(os, local_expr); },
      std::array{ expr.type_id() });
  }
}

namespace demo_single_dispatch
{
  void print(std::ostream& os, demo2::Constant const& expr);
  void print(std::ostream& os, demo2::Plus const& expr);
  void print(std::ostream& os, demo2::Minus const& expr);

  void print(std::ostream& os, demo2::Constant const& expr)
  {
    os << expr.value;
  }

  void print(std::ostream& os, demo2::Plus const& expr)
  {
    dispatch<demo2::Types>([&os](auto local_expr)
      { print(os, local_expr); },
      std::array{ expr.lhs->type_id() });
    os << "+";
    dispatch<demo2::Types>([&os](auto local_expr)
      { print(os, local_expr); },
      std::array{ expr.rhs->type_id() });
  }

  void print(std::ostream& os, demo2::Minus const& expr)
  {
    dispatch<demo2::Types>([&os](auto local_expr)
      { print(os, local_expr); },
      std::array{ expr.lhs->type_id() });
    os << "-";
    dispatch<demo2::Types>([&os](auto local_expr)
      { print(os, local_expr); },
      std::array{ expr.rhs->type_id() });
  }

  void demo_print(std::ostream& os, demo2::Expr const& expr)
  {
    dispatch<demo2::Types>([&os](auto local_expr)
      { print(os, local_expr); },
      std::array{ expr.type_id() });
  }
}