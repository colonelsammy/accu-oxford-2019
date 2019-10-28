#include <constant.hpp>
#include <plus.hpp>
#include <minus.hpp>

namespace demo_double_dispatch
{
  double eval(demo4::Constant const& expr);
  double eval(demo4::Plus const& expr);
  double eval(demo4::Minus const& expr);

  double eval(demo4::Constant const& expr)
  {
    return expr.value;
  }

  template <typename LHS, typename RHS>
  double eval_plus(LHS const&, RHS const&)
  {
    throw std::runtime_error("invalid eval");
  }

  double eval_plus(demo4::Constant const& lhs, demo4::Constant const& rhs)
  {
    return lhs.value + rhs.value;
  }

  double eval(demo4::Plus const& expr)
  {
    return dispatch<demo4::variant_types>([](auto lhs, auto rhs)
      { return eval_plus(lhs, rhs); },
      std::array{ expr.lhs->type_id(), expr.rhs->type_id()});
  }

  template <typename LHS, typename RHS>
  double eval_minus(LHS const&, RHS const&)
  {
    throw std::runtime_error("invalid eval");
  }

  double eval_minus(demo4::Constant const& lhs, demo4::Constant const& rhs)
  {
    return lhs.value - rhs.value;
  }

  double eval_minus(demo4::Plus const& lhs, demo4::Constant const& rhs)
  {
    return dispatch<demo4::variant_types>([](auto expr)
      { return eval(expr); },
      std::array{ lhs.type_id() }) - rhs.value;
  }

  double eval(demo4::Minus const& expr)
  {
    return dispatch<demo4::variant_types>([](auto lhs, auto rhs)
      { return eval_minus(lhs, rhs);  },
      std::array{ expr.lhs->type_id(), expr.rhs->type_id() });
  }

  double demo_eval(demo4::Expr const& expr)
  {
    return dispatch<demo4::variant_types>([](auto local_expr)
      { return eval(local_expr); },
      std::array{ expr.type_id() });
  }
}

namespace demo_single_dispatch
{
  double eval(demo4::Constant const& expr);
  double eval(demo4::Plus const& expr);
  double eval(demo4::Minus const& expr);

  double eval(demo4::Constant const& expr)
  {
    return expr.value;
  }

  double eval(demo4::Plus const& expr)
  {
    auto value_lhs = dispatch<demo4::variant_types>([](auto local_expr)
      { return eval(local_expr); },
      std::array{ expr.lhs->type_id() });
    auto value_rhs = dispatch<demo4::variant_types>([](auto local_expr)
      { return eval(local_expr); },
      std::array{ expr.rhs->type_id() });
    return value_lhs + value_rhs;
  }

  double eval(demo4::Minus const& expr)
  {
    auto value_lhs = dispatch<demo4::variant_types>([](auto local_expr)
      { return eval(local_expr); },
      std::array{ expr.lhs->type_id() });
    auto value_rhs = dispatch<demo4::variant_types>([](auto local_expr)
      { return eval(local_expr); },
      std::array{ expr.rhs->type_id() });
    return value_lhs - value_rhs;
  }

  double demo_eval(demo4::Expr const& expr)
  {
    return dispatch<demo4::variant_types>([](auto local_expr)
      { return eval(local_expr); },
      std::array{ expr.type_id() });
  }
}
