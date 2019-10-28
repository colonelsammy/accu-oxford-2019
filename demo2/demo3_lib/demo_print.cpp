#include <constant.hpp>
#include <plus.hpp>
#include <minus.hpp>

namespace demo_double_dispatch
{
  void print(std::ostream& os, demo2::Constant const& expr);
  void print(std::ostream& os, demo2::Plus const& expr);
  void print(std::ostream& os, demo2::Minus const& expr);

  struct Exec
  {
    template<typename... Args, typename LHS>
    static void dispatch(std::tuple<Args...> const& args, LHS const& expr)
    {
      print(std::get<0>(args), expr);
    }
  };

  void print(std::ostream& os, demo2::Constant const& expr)
  {
    os << expr.value;
  }

  template <typename LHS, typename RHS>
  void print_plus(std::ostream&, LHS const&, RHS const&)
  {
    throw std::runtime_error("invalid print");
  }

  void print_plus(std::ostream& os, demo2::Constant const& lhs, demo2::Constant const& rhs)
  {
    os << lhs.value;
    os << "+";
    os << rhs.value;
  }

  struct ExecPlus
  {
    template<typename...Args, typename LHS, typename RHS>
    static void dispatch(std::tuple<Args...> const& args, LHS const& lhs, RHS const& rhs)
    {
      print_plus(std::get<0>(args), lhs, rhs);
    }
  };

  void print(std::ostream& os, demo2::Plus const& expr)
  {
    return dispatch<demo2::Types, ExecPlus>(std::tuple<std::ostream&> {os}, std::array{ expr.lhs->type_id(), expr.rhs->type_id() });
  }

  template <typename LHS, typename RHS>
  void print_minus(std::ostream&, LHS const&, RHS const&)
  {
    throw std::runtime_error("invalid eval");
  }

  void print_minus(std::ostream& os, demo2::Constant const& lhs, demo2::Constant const& rhs)
  {
    os << lhs.value;
    os << "-";
    os << rhs.value;
  }

  void print_minus(std::ostream& os, demo2::Plus const& lhs, demo2::Constant const& rhs)
  {
    dispatch<demo2::Types, Exec>(std::tuple<std::ostream&> {os}, std::array{ lhs.type_id() });
    os << "-";
    os << rhs.value;
  }

  struct ExecMinus
  {
    template<typename... Args, typename LHS, typename RHS>
    static void dispatch(std::tuple<Args...> const& args, LHS const& lhs, RHS const& rhs)
    {
      print_minus(std::get<0>(args), lhs, rhs);
    }
  };

  void print(std::ostream& os, demo2::Minus const& expr)
  {
    dispatch<demo2::Types, ExecMinus>(std::tuple<std::ostream&> {os}, std::array{ expr.lhs->type_id(), expr.rhs->type_id() });
  }

  void demo_print(std::ostream& os, demo2::Expr const& expr)
  {
    dispatch<demo2::Types, Exec>(std::tuple<std::ostream&> {os}, std::array{ expr.type_id() });
  }
}

namespace demo_single_dispatch
{
  void print(std::ostream& os, demo2::Constant const& expr);
  void print(std::ostream& os, demo2::Plus const& expr);
  void print(std::ostream& os, demo2::Minus const& expr);

  struct Exec
  {
    template<typename... Args, typename LHS>
    static void dispatch(std::tuple<Args...> const& args, LHS const& expr)
    {
      print(std::get<0>(args), expr);
    }
  };

  void print(std::ostream& os, demo2::Constant const& expr)
  {
    os << expr.value;
  }

  void print(std::ostream& os, demo2::Plus const& expr)
  {
    dispatch<demo2::Types, Exec>(std::tuple<std::ostream&> {os}, std::array{ expr.lhs->type_id() });
    os << "+";
    dispatch<demo2::Types, Exec>(std::tuple<std::ostream&> {os}, std::array{ expr.rhs->type_id() });
  }

  void print(std::ostream& os, demo2::Minus const& expr)
  {
    dispatch<demo2::Types, Exec>(std::tuple<std::ostream&> {os}, std::array{ expr.lhs->type_id() });
    os << "-";
    dispatch<demo2::Types, Exec>(std::tuple<std::ostream&> {os}, std::array{ expr.rhs->type_id() });
  }

  void demo_print(std::ostream& os, demo2::Expr const& expr)
  {
    dispatch<demo2::Types, Exec>(std::tuple<std::ostream&> {os}, std::array{ expr.type_id() });
  }
}