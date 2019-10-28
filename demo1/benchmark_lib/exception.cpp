#include <benchmark/benchmark.h>
#include <ostream>
#include <exception.hpp>

double exception_eval(excep::Expr const& expr)
{
  double result = 0.0;
  try
  {
    expr.invoke();
  }
  catch (excep::Constant const* p)
  {
    result = excep::eval(*p);
  }
  catch (excep::Plus const* p)
  {
    result = excep::eval(*p);
  }
  catch (excep::Minus const* p)
  {
    result = excep::eval(*p);
  }
  return result;
}

void exception_print(std::ostream& os, excep::Expr const& expr)
{
  try
  {
    expr.invoke();
  }
  catch (excep::Constant const* p)
  {
    excep::print(os, *p);
  }
  catch (excep::Plus const* p)
  {
    excep::print(os, *p);
  }
  catch (excep::Minus const* p)
  {
    excep::print(os, *p);
  }
}
