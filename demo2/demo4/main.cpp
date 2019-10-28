#include <iostream>
using std::cout;

#include <constant.hpp>
#include <plus.hpp>
#include <minus.hpp>

namespace demo_double_dispatch
{
  double demo_eval(demo4::Expr const& expr);
  void demo_print(std::ostream& os, demo4::Expr const& expr);
}

int
main()
{
  using namespace demo4;

  Constant c1{ 3.0 }, c2{ 5.0 };
  Plus p{ &c1, &c2 };
  cout << "Result: " << demo_double_dispatch::demo_eval(p) << "\n";
  
  Constant c3{ 7.0 };
  Minus m{ &p, &c3 };
  cout << "Result: " << demo_double_dispatch::demo_eval(m) << "\n";
  
  demo_double_dispatch::demo_print(cout, m);
  cout << " = " << demo_double_dispatch::demo_eval(m) << "\n";

  return 0;
}
