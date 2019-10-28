#pragma once

#include <ostream>

namespace virtualfn
{
  struct Expr
  {
    virtual ~Expr() = default;
    virtual double eval() const = 0;
    virtual void print(std::ostream& os) const = 0;
  };

  struct Constant : public Expr
  {
    Constant(double v) : value(v) {}

    double eval() const
    {
      return value;
    }
    void print(std::ostream& os) const
    {
      os << value;
    }
    double value = 0.0;
  };

  struct Plus : public Expr
  {
    Plus(Constant const* l, Constant const* r) : lhs(l), rhs(r) {}

    double eval() const
    {
      return lhs->eval() + rhs->eval();
    }
    void print(std::ostream& os) const
    {
      lhs->print(os);
      os << "+";
      rhs->print(os);
    }

    Constant const* lhs = nullptr;
    Constant const* rhs = nullptr;
  };

  struct Minus : public Expr
  {
    Minus(Plus const* l, Constant const* r) : lhs(l), rhs(r) {}

    double eval() const
    {
      return lhs->eval() - rhs->eval();
    }
    void print(std::ostream& os) const
    {
      lhs->print(os);
      os << "-";
      rhs->print(os);
    }

    Plus const* lhs = nullptr;
    Constant const* rhs = nullptr;
  };

}
