#include <operation.hpp>
#include <invoke_operation.hpp>

namespace demo1
{
  void print(std::ostream& os, Constant const& expr)
  {
    os << expr.value;
  }

  void print(std::ostream& os, Plus const& expr)
  {
    auto c1 = expr.lhs->invoke();
    operations ops{ invoke_print{os} };
    c1.call(ops);
    os << "+";
    auto c2 = expr.rhs->invoke();
    c2.call(ops);
  }

  void print(std::ostream& os, Minus const& expr)
  {
    auto c1 = expr.lhs->invoke();
    operations ops{ invoke_print{os} };
    c1.call(ops);
    os << "-";
    auto c2 = expr.rhs->invoke();
    c2.call(ops);
  }

  void demo_print(std::ostream& os, Expr const& expr)
  {
    auto callable = expr.invoke();
    operations ops{ invoke_print{os} };
    callable.call(ops);
  }
}