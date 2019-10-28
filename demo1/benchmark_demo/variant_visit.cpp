#include <benchmark/benchmark.h>
#include <variant_visit.hpp>
#include <ostream>

namespace variant_visit
{

  struct EvalVisit
  {
    double result = 0.0;
    void operator()(Constant const& v)
    {
      result = v.value;
    }
    void operator()(Plus const& v)
    {
      EvalVisit eval_lhs;
      auto lhs = std::any_cast<Expr const&>(v.lhs);
      std::visit(eval_lhs, lhs);
      EvalVisit eval_rhs;
      auto rhs = std::any_cast<Expr const&>(v.rhs);
      std::visit(eval_rhs, rhs);

      result = eval_lhs.result + eval_rhs.result;
    }
    void operator()(Minus const& v)
    {
      EvalVisit eval_lhs;
      auto lhs = std::any_cast<Expr const&>(v.lhs);
      std::visit(eval_lhs, lhs);
      EvalVisit eval_rhs;
      auto rhs = std::any_cast<Expr const&>(v.rhs);
      std::visit(eval_rhs, rhs);

      result = eval_lhs.result - eval_rhs.result;
    }
  };

  struct PrintVisit
  {
    std::ostream& os;
    PrintVisit(std::ostream& o)
      : os(o) {}
    
    void operator()(Constant const& v)
    {
      os << v.value;
    }
    void operator()(Plus const& v)
    {
      PrintVisit eval_lhs{ os };
      auto lhs = std::any_cast<Expr const&>(v.lhs);
      std::visit(eval_lhs, lhs);
      os << "+";
      PrintVisit eval_rhs{ os };
      auto rhs = std::any_cast<Expr const&>(v.rhs);
      std::visit(eval_rhs, rhs);
    }
    void operator()(Minus const& v)
    {
      PrintVisit eval_lhs{ os };
      auto lhs = std::any_cast<Expr const&>(v.lhs);
      std::visit(eval_lhs, lhs);
      os << "-";
      PrintVisit eval_rhs{ os };
      auto rhs = std::any_cast<Expr const&>(v.rhs);
      std::visit(eval_rhs, rhs);
    }
  };
}

double visit_eval(variant_visit::Expr const& expr)
{
  variant_visit::EvalVisit eval;
  std::visit(eval, expr);
  return eval.result;
}

void visit_print(std::ostream& os, variant_visit::Expr const& expr)
{
  variant_visit::PrintVisit eval{ os };
  std::visit(eval, expr);
}
