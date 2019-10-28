#include <expr_impl.hpp>

#ifdef XXX
#include <variant>
#include <memory>

struct Expr;
struct Neg {
  std::shared_ptr<Expr> expr;
};
struct Add {
  std::shared_ptr<Expr> lhs, rhs;
};
struct Mul {
  std::shared_ptr<Expr> lhs, rhs;
};
struct Expr : std::variant<int, Neg, Add, Mul> {
  using variant::variant;
};

namespace std {
  template <>
  struct variant_size<Expr> : variant_size<Expr::variant> {};
  template <std::size_t I>
  struct variant_alternative<I, Expr> : variant_alternative<I, Expr::variant> {};
}

int eval(Expr expr) {
  struct visitor {
    int operator()(int i) const {
      return i;
    }
    int operator()(const Neg& n) const {
      return -eval(*n.expr);
    }
    int operator()(const Add& a) const {
      return eval(*a.lhs) + eval(*a.rhs);
    }
    int operator()(const Mul& m) const {
      // Optimize multiplication by 0.
      if (int* i = std::get_if<int>(m.lhs.get()); i && *i == 0) {
        return 0;
      }
      if (int* i = std::get_if<int>(m.rhs.get()); i && *i == 0) {
        return 0;
      }
      return eval(*m.lhs) * eval(*m.rhs);
    }
  };
  return std::visit(visitor{}, std::decay_t<Expr::variant>(expr));
}
#endif

namespace demo_variant
{
  // Regular std::visit with variant
  double eval(demo3::Expr const& expr) {
    struct visitor {
      double operator()(demo3::Constant const& expr) const {
        return expr.value;
      }
      double operator()(demo3::Plus const& expr) const {
        return eval(*expr.lhs) + eval(*expr.rhs);
      }
      double operator()(demo3::Minus const& expr) const {
        return eval(*expr.lhs) - eval(*expr.rhs);
      }
    };
    return std::visit(visitor{}, std::decay_t<demo3::Expr::variant>(expr));
  }
  void print(std::ostream* os, demo3::Expr const& expr) {
    struct visitor {
      void operator()(std::ostream* os, demo3::Constant const& expr) const {
        (*os) << expr.value;
      }
      void operator()(std::ostream* os, demo3::Plus const& expr) const {
        print(os, *expr.lhs);
        (*os) << "+";
        print(os, *expr.rhs);
      }
      void operator()(std::ostream* os, demo3::Minus const& expr) const {
        print(os, *expr.lhs);
        (*os) << "-";
        print(os, *expr.rhs);
      }
    };
    std::variant<std::ostream*> v = os;
    return std::visit(visitor{}, v, std::decay_t<demo3::Expr::variant>(expr));
  }

  /////////////////////////////////////////////
  // Calling overloads with variant types

  double eval2(demo3::Constant const& expr);
  double eval2(demo3::Plus const& expr);
  double eval2(demo3::Minus const& expr);

  double eval2(demo3::Constant const& expr)
  {
    return expr.value;
  }

  double eval2(demo3::Plus const& expr)
  {
    auto value_lhs = dispatch<demo3::Types>([](auto local_expr)
      { return eval2(local_expr); },
      std::array{ *expr.lhs });
    auto value_rhs = dispatch<demo3::Types>([](auto local_expr)
      { return eval2(local_expr); },
      std::array{ *expr.rhs });
    return value_lhs + value_rhs;
  }

  double eval2(demo3::Minus const& expr)
  {
    auto value_lhs = dispatch<demo3::Types>([](auto local_expr)
      { return eval2(local_expr); },
      std::array{ *expr.lhs });
    auto value_rhs = dispatch<demo3::Types>([](auto local_expr)
      { return eval2(local_expr); },
      std::array{ *expr.rhs });
    return value_lhs - value_rhs;
  }

  double demo_eval(demo3::Expr const& expr)
  {
    return dispatch<demo3::Types>([](auto local_expr)
      { return eval2(local_expr); },
      std::array{ expr });
  }

  void print(std::ostream& os, demo3::Constant const& expr);
  void print(std::ostream& os, demo3::Plus const& expr);
  void print(std::ostream& os, demo3::Minus const& expr);

  void print(std::ostream& os, demo3::Constant const& expr)
  {
    os << expr.value;
  }

  void print(std::ostream& os, demo3::Plus const& expr)
  {
    dispatch<demo3::Types>([&os](auto local_expr)
      { print(os, local_expr); },
      std::array{ *expr.lhs });
    os << "+";
    dispatch<demo3::Types>([&os](auto local_expr)
      { print(os, local_expr); },
      std::array{ *expr.rhs });
  }

  void print(std::ostream& os, demo3::Minus const& expr)
  {
    dispatch<demo3::Types>([&os](auto local_expr)
      { print(os, local_expr); },
      std::array{ *expr.lhs });
    os << "-";
    dispatch<demo3::Types>([&os](auto local_expr)
      { print(os, local_expr); },
      std::array{ *expr.rhs });
  }

  void demo_print(std::ostream& os, demo3::Expr const& expr)
  {
    dispatch<demo3::Types>([&os](auto local_expr)
      { print(os, local_expr); }, std::array{ expr });
  }
}
