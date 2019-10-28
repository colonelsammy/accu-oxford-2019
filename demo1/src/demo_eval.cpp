#include <operation.hpp>
#include <invoke_operation.hpp>

namespace demo1
{
  double eval(Constant const& expr)
  {
    return expr.value;
  }

  double eval(Plus const& expr)
  {
    operations ops{ invoke_eval{} };

    auto c1 = expr.lhs->invoke();
    c1.call(ops);
    auto v1 = std::get<invoke_eval>(ops);

    auto c2 = expr.rhs->invoke();
    c2.call(ops);
    auto v2 = std::get<invoke_eval>(ops);

    return v1.result + v2.result;
  }

  //double eval(Minus const& expr)
  //{
  //  operations ops{ invoke_eval{} };

  //  auto c1 = expr.lhs->invoke();
  //  c1.call(ops);
  //  auto v1 = std::get<invoke_eval>(ops);

  //  auto c2 = expr.rhs->invoke();
  //  c2.call(ops);
  //  auto v2 = std::get<invoke_eval>(ops);

  //  return v1.result - v2.result;
  //}

  double demo_eval(Expr const& expr)
  {
    auto callable = expr.invoke();
    operations ops{ invoke_eval{} };
    callable.call(ops);
    auto value = std::get<invoke_eval>(ops);
    return value.result;
  }
}