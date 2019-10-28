#pragma once

namespace excep
{
  struct Expr
  {
    virtual ~Expr() = default;
    virtual Expr* invoke() const = 0;
  };

  struct Constant : public Expr
  {
    Constant(double v) : value(v) {}

    Expr* invoke() const override
    {
      throw this;
      //return nullptr;
    }

    double value = 0.0;
  };

  struct Plus : public Expr
  {
    Plus(Constant const* l, Constant const* r) : lhs(l), rhs(r) {}

    Expr* invoke() const override
    {
      throw this;
      //return nullptr;
    }

    Constant const* lhs = nullptr;
    Constant const* rhs = nullptr;
  };

  struct Minus : public Expr
  {
    Minus(Plus const* l, Constant const* r) : lhs(l), rhs(r) {}

    Expr* invoke() const override
    {
      throw this;
      //return nullptr;
    }

    Plus const* lhs = nullptr;
    Constant const* rhs = nullptr;
  };

  double eval(Constant const& expr);
  double eval(Plus const& expr);
  double eval(Minus const& expr);

  inline double eval(Constant const& expr)
  {
    return expr.value;
  }

  inline double eval_plus_rhs(Constant const* lhs, Expr const* rhs)
  {
    double result = 0.0;
    try
    {
      rhs->invoke();
    }
    catch (Constant const* p)
    {
      result = lhs->value + p->value;
    }
    catch (Plus const* p)
    {
      result = lhs->value + eval(*p);
    }
    catch (Minus const* p)
    {
      result = lhs->value + eval(*p);
    }
    return result;
  }

  inline double eval_minus_rhs(Constant const* lhs, Expr const* rhs)
  {
    double result = 0.0;
    try
    {
      rhs->invoke();
    }
    catch (Constant const* p)
    {
      result = lhs->value - p->value;
    }
    catch (Plus const* p)
    {
      result = lhs->value - eval(*p);
    }
    catch (Minus const* p)
    {
      result = lhs->value - eval(*p);
    }
    return result;
  }

  template <typename T>
  double eval_plus_rhs(T const* lhs, Expr const* rhs)
  {
    double result = 0.0;
    try
    {
      rhs->invoke();
    }
    catch (Constant const* p)
    {
      result = eval(*lhs) + p->value;
    }
    catch (Plus const* p)
    {
      result = eval(*lhs) + eval(*p);
    }
    catch (Minus const* p)
    {
      result = eval(*lhs) + eval(*p);
    }
    return result;
  }

  template <typename T>
  double eval_minus_rhs(T const* lhs, Expr const* rhs)
  {
    double result = 0.0;
    try
    {
      rhs->invoke();
    }
    catch (Constant const* p)
    {
      result = eval(*lhs) - p->value;
    }
    catch (Plus const* p)
    {
      result = eval(*lhs) - eval(*p);
    }
    catch (Minus const* p)
    {
      result = eval(*lhs) - eval(*p);
    }
    return result;
  }

  inline double eval(Plus const& expr)
  {
    double result = 0.0;
    try
    {
      expr.lhs->invoke();
    }
    catch (Constant const* p)
    {
      result = eval_plus_rhs(p, expr.rhs);
    }
    catch (Plus const* p)
    {
      result = eval_plus_rhs(p, expr.rhs);
    }
    catch (Minus const* p)
    {
      result = eval_plus_rhs(p, expr.rhs);
    }
    return result;
  }

  inline double eval(Minus const& expr)
  {
    double result = 0.0;
    try
    {
      expr.lhs->invoke();
    }
    catch (Constant const* p)
    {
      result = eval_minus_rhs(p, expr.rhs);
    }
    catch (Plus const* p)
    {
      result = eval_minus_rhs(p, expr.rhs);
    }
    catch (Minus const* p)
    {
      result = eval_minus_rhs(p, expr.rhs);
    }
    return result;
  }

  void print(std::ostream& os, Constant const& expr);
  void print(std::ostream& os, Plus const& expr);
  void print(std::ostream& os, Minus const& expr);

  inline void print(std::ostream& os, Constant const& expr)
  {
    os << expr.value;
  }

  inline void print_plus_rhs(std::ostream& os, Constant const* lhs, Expr const* rhs)
  {
    try
    {
      rhs->invoke();
    }
    catch (Constant const* p)
    {
      os << lhs->value;
      os << "+";
      os << p->value;
    }
    catch (Plus const* p)
    {
      os << lhs->value;
      os << "+";
      print(os, *p);
    }
    catch (Minus const* p)
    {
      os << lhs->value;
      os << "+";
      print(os, *p);
    }
  }

  inline void print_minus_rhs(std::ostream& os, Constant const* lhs, Expr const* rhs)
  {
    try
    {
      rhs->invoke();
    }
    catch (Constant const* p)
    {
      os << lhs->value;
      os << "-";
      os << p->value;
    }
    catch (Plus const* p)
    {
      os << lhs->value;
      os << "-";
      print(os, *p);
    }
    catch (Minus const* p)
    {
      os << lhs->value;
      os << "-";
      print(os, *p);
    }
  }

  template <typename T>
  void print_plus_rhs(std::ostream& os, T const* lhs, Expr const* rhs)
  {
    try
    {
      rhs->invoke();
    }
    catch (Constant const* p)
    {
      print(os, *lhs);
      os << "+";
      os << p->value;
    }
    catch (Plus const* p)
    {
      print(os, *lhs);
      os << "+";
      print(os, *p);
    }
    catch (Minus const* p)
    {
      print(os, *lhs);
      os << "+";
      print(os, *p);
    }
  }

  template <typename T>
  void print_minus_rhs(std::ostream& os, T const* lhs, Expr const* rhs)
  {
    try
    {
      rhs->invoke();
    }
    catch (Constant const* p)
    {
      print(os, *lhs);
      os << "-";
      os << p->value;
    }
    catch (Plus const* p)
    {
      print(os, *lhs);
      os << "-";
      print(os, *p);
    }
    catch (Minus const* p)
    {
      print(os, *lhs);
      os << "-";
      print(os, *p);
    }
  }

  inline void print(std::ostream& os, Plus const& expr)
  {
    try
    {
      expr.lhs->invoke();
    }
    catch (Constant const* p)
    {
      print_plus_rhs(os, p, expr.rhs);
    }
    catch (Plus const* p)
    {
      print_plus_rhs(os, p, expr.rhs);
    }
    catch (Minus const* p)
    {
      print_plus_rhs(os, p, expr.rhs);
    }
  }

  inline void print(std::ostream& os, Minus const& expr)
  {
    try
    {
      expr.lhs->invoke();
    }
    catch (Constant const* p)
    {
      print_minus_rhs(os, p, expr.rhs);
    }
    catch (Plus const* p)
    {
      print_minus_rhs(os, p, expr.rhs);
    }
    catch (Minus const* p)
    {
      print_minus_rhs(os, p, expr.rhs);
    }
  }
}
