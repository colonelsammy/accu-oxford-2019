#include <iostream>
using std::cout;

#include <expr_impl.hpp>

namespace demo_variant
{
  double eval(demo3::Expr const& expr);
  double demo_eval(demo3::Expr const& expr);
  void demo_print(std::ostream& os, demo3::Expr const& expr);
}
//namespace demo_double_dispatch
//{
//  double demo_eval(demo3::Expr const& expr);
//  void demo_print(std::ostream& os, demo3::Expr const& expr);
//}

int
main()
{
  using namespace demo3;

  Expr c1{ Constant{3.0} };
  Expr c2{ Constant{5.0} };
  Expr p = Plus{ &c1, &c2 };
  cout << "Result: " << demo_variant::demo_eval(p) << "\n";
  
  Expr c3 = Constant{7.0};
  Expr m = Minus{ &p, &c3 };
  cout << "Result: " << demo_variant::demo_eval(m) << "\n";
  
  demo_variant::demo_print(cout, m);
  cout << " = " << demo_variant::demo_eval(m) << "\n";

  return 0;
}
