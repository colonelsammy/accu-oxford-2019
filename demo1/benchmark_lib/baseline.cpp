#include <benchmark/benchmark.h>
#include <baseline.hpp>
#include <ostream>

namespace baseline
{
  double eval(Constant const& expr)
  {
    return expr.value;
  }

  double eval(Plus const& expr)
  {
    return eval(*expr.lhs) + eval(*expr.rhs);
  }

  double eval(Minus const& expr)
  {
    return eval(*expr.lhs) - eval(*expr.rhs);
  }

  void print(std::ostream& os, Constant const& expr)
  {
    os << expr.value;
  }

  void print(std::ostream& os, Plus const& expr)
  {
    print(os, *expr.lhs);
    os << "+";
    print(os, *expr.rhs);
  }

  void print(std::ostream& os, Minus const& expr)
  {
    print(os, *expr.lhs);
    os << "-";
    print(os, *expr.rhs);
  }
}

double baseline_eval(baseline::Plus const& expr)
{
  return eval(expr);
}

void baseline_print(std::ostream& os, baseline::Plus const& expr)
{
  print(os, expr);
}

double baseline_eval(baseline::Minus const& expr)
{
  return eval(expr);
}

void baseline_print(std::ostream& os, baseline::Minus const& expr)
{
  print(os, expr);
}
