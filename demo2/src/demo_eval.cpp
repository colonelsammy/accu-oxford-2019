#include <constant.hpp>
#include <plus.hpp>
#include <minus.hpp>

namespace demo_double_dispatch
{
  double eval(demo2::Constant const& expr);
  double eval(demo2::Plus const& expr);
  double eval(demo2::Minus const& expr);

  double eval(demo2::Constant const& expr)
  {
    return expr.value;
  }

  template <typename LHS, typename RHS>
  double eval_plus(LHS const&, RHS const&)
  {
    throw std::runtime_error("invalid eval");
  }

  double eval_plus(demo2::Constant const& lhs, demo2::Constant const& rhs)
  {
    return lhs.value + rhs.value;
  }

  double eval(demo2::Plus const& expr)
  {
    return dispatch<demo2::Types>([](auto lhs, auto rhs)
      { return eval_plus(lhs, rhs); },
      std::array{ expr.lhs->type_id(), expr.rhs->type_id()});
  }

  template <typename LHS, typename RHS>
  double eval_minus(LHS const&, RHS const&)
  {
    throw std::runtime_error("invalid eval");
  }

  double eval_minus(demo2::Constant const& lhs, demo2::Constant const& rhs)
  {
    return lhs.value - rhs.value;
  }

  double eval_minus(demo2::Plus const& lhs, demo2::Constant const& rhs)
  {
    return dispatch<demo2::Types>([](auto expr)
      { return eval(expr); },
      std::array{ lhs.type_id() }) - rhs.value;
  }

  double eval(demo2::Minus const& expr)
  {
    return dispatch<demo2::Types>([](auto lhs, auto rhs)
      { return eval_minus(lhs, rhs);  },
      std::array{ expr.lhs->type_id(), expr.rhs->type_id() });
  }

  double demo_eval(demo2::Expr const& expr)
  {
    return dispatch<demo2::Types>([](auto local_expr)
      { return eval(local_expr); },
      std::array{ expr.type_id() });
  }
}

namespace demo_single_dispatch
{
  double eval(demo2::Constant const& expr);
  double eval(demo2::Plus const& expr);
  double eval(demo2::Minus const& expr);

  double eval(demo2::Constant const& expr)
  {
    return expr.value;
  }

  double eval(demo2::Plus const& expr)
  {
    auto value_lhs = dispatch<demo2::Types>([](auto local_expr)
      { return eval(local_expr); },
      std::array{ expr.lhs->type_id() });
    auto value_rhs = dispatch<demo2::Types>([](auto local_expr)
      { return eval(local_expr); },
      std::array{ expr.rhs->type_id() });
    return value_lhs + value_rhs;
  }

  double eval(demo2::Minus const& expr)
  {
    auto value_lhs = dispatch<demo2::Types>([](auto local_expr)
      { return eval(local_expr); },
      std::array{ expr.lhs->type_id() });
    auto value_rhs = dispatch<demo2::Types>([](auto local_expr)
      { return eval(local_expr); },
      std::array{ expr.rhs->type_id() });
    return value_lhs - value_rhs;
  }

  double demo_eval(demo2::Expr const& expr)
  {
    return dispatch<demo2::Types>([](auto local_expr)
      { return eval(local_expr); },
      std::array{ expr.type_id() });
  }
}
