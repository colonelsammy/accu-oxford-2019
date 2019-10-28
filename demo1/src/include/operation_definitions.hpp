#pragma once
#include <variant>
#include <ostream>

namespace demo1
{
  struct invoke_eval
  {
    template <typename T>
    void invoke(const T& expr);
    double result = 0.0;
  };

  using operations = std::variant<invoke_eval>;

  //struct invoke_print
  //{
  //  invoke_print(std::ostream& o) : os(o) {}
  //  template <typename T>
  //  void invoke(const T& expr);
  //  std::ostream& os;
  //};

  //using operations = std::variant<invoke_eval, invoke_print>;
}