#include <iostream>
using std::cout;

#include <constant.hpp>
#include <plus.hpp>
//#include <minus.hpp>

namespace demo1
{
  double demo_eval(Expr const& expr);

  void demo_print(std::ostream& os, Expr const& expr);
}

int
main()
{
  using namespace demo1;

  Constant c1{ 3.0 }, c2{ 5.0 };
  Plus p{ &c1, &c2 };
  cout << "Result: " << demo1::demo_eval(p) << "\n";
  
  //Constant c3{ 7.0 };
  //Minus m{ &p, &c3 };
  //cout << "Result: " << demo1::demo_eval(m) << "\n";
  //
  //demo1::demo_print(cout, m);
  //cout << " = " << demo1::demo_eval(m) << "\n";

  return 0;
}
