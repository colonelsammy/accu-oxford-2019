#include <benchmark/benchmark.h>
#include <virtualfn.hpp>
#include <ostream>

double virtualfn_eval(virtualfn::Expr const& expr)
{
  return expr.eval();
}

void virtualfn_print(std::ostream& os, virtualfn::Expr const& expr)
{
  expr.print(os);
}
