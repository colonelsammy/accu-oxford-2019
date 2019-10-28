#include <benchmark/benchmark.h>
#include <sstream>

#include <constant.hpp>
#include <plus.hpp>
#include <minus.hpp>
#include <baseline.hpp>
#include <virtualfn.hpp>
#include <exception.hpp>
#include <variant_visit.hpp>

double baseline_eval(baseline::Plus const& expr);
void baseline_print(std::ostream& os, baseline::Plus const& expr);
double baseline_eval(baseline::Minus const& expr);
void baseline_print(std::ostream& os, baseline::Minus const& expr);

double virtualfn_eval(virtualfn::Expr const& expr);
void virtualfn_print(std::ostream& os, virtualfn::Expr const& expr);

double exception_eval(excep::Expr const& expr);
void exception_print(std::ostream& os, excep::Expr const& expr);

double visit_eval(variant_visit::Expr const& expr);
void visit_print(std::ostream& os, variant_visit::Expr const& expr);

namespace demo1
{
  double demo_eval(Expr const& expr);
  void demo_print(std::ostream& os, Expr const& expr);
}

static void BM_baseline_eval_plus(benchmark::State& state)
{
  for (auto _ : state)
  {
    baseline::Constant c1{ 3.0 }, c2{ 5.0 };
    baseline::Plus p{ &c1, &c2 };
    double result;
    benchmark::DoNotOptimize(result = baseline_eval(p));
    assert(result == 8.0);
  }
}

BENCHMARK(BM_baseline_eval_plus);

static void BM_exception_eval_plus(benchmark::State& state)
{
  for (auto _ : state)
  {
    excep::Constant c1{ 3.0 }, c2{ 5.0 };
    excep::Plus p{ &c1, &c2 };
    double result;
    benchmark::DoNotOptimize(result = exception_eval(p));
    assert(result == 8.0);
  }
}

BENCHMARK(BM_exception_eval_plus);

static void BM_virtualfn_eval_plus(benchmark::State& state)
{
  for (auto _ : state)
  {
    virtualfn::Constant c1{ 3.0 }, c2{ 5.0 };
    virtualfn::Plus p{ &c1, &c2 };
    double result;
    benchmark::DoNotOptimize(result = virtualfn_eval(p));
    assert(result == 8.0);
  }
}

BENCHMARK(BM_virtualfn_eval_plus);

static void BM_visit_eval_plus(benchmark::State& state)
{
  for (auto _ : state)
  {
    variant_visit::Constant c1{ 3.0 }, c2{ 5.0 };
    variant_visit::Plus p{ variant_visit::Expr{c1}, variant_visit::Expr{c2} };
    double result;
    benchmark::DoNotOptimize(result = visit_eval(p));
    assert(result == 8.0);
  }
}

BENCHMARK(BM_visit_eval_plus);

static void BM_eval_plus(benchmark::State& state)
{
  for (auto _ : state)
  {
      demo1::Constant c1{ 3.0 }, c2{ 5.0 };
      demo1::Plus p{ &c1, &c2 };
      double result;
      benchmark::DoNotOptimize(result = demo1::demo_eval(p));
      assert(result == 8.0);
  }
}

BENCHMARK(BM_eval_plus);

static void BM_baseline_eval_minus(benchmark::State& state)
{
  for (auto _ : state)
  {
    baseline::Constant c1{ 3.0 }, c2{ 5.0 };
    baseline::Plus p{ &c1, &c2 };
    baseline::Constant c3{ 7.0 };
    baseline::Minus m{ &p, &c3 };
    double result;
    benchmark::DoNotOptimize(result = baseline_eval(m));
    assert(result == 1.0);
  }
}

BENCHMARK(BM_baseline_eval_minus);

static void BM_exception_eval_minus(benchmark::State& state)
{
  for (auto _ : state)
  {
    excep::Constant c1{ 3.0 }, c2{ 5.0 };
    excep::Plus p{ &c1, &c2 };
    excep::Constant c3{ 7.0 };
    excep::Minus m{ &p, &c3 };
    double result;
    benchmark::DoNotOptimize(result = exception_eval(m));
    assert(result == 1.0);
  }
}

BENCHMARK(BM_exception_eval_minus);

static void BM_virtualfn_eval_minus(benchmark::State& state)
{
  for (auto _ : state)
  {
    virtualfn::Constant c1{ 3.0 }, c2{ 5.0 };
    virtualfn::Plus p{ &c1, &c2 };
    virtualfn::Constant c3{ 7.0 };
    virtualfn::Minus m{ &p, &c3 };
    double result;
    benchmark::DoNotOptimize(result = virtualfn_eval(m));
    assert(result == 1.0);
  }
}

BENCHMARK(BM_virtualfn_eval_minus);

static void BM_visit_eval_minus(benchmark::State& state)
{
  for (auto _ : state)
  {
    variant_visit::Constant c1{ 3.0 }, c2{ 5.0 };
    variant_visit::Plus p{ variant_visit::Expr{c1}, variant_visit::Expr{c2} };
    variant_visit::Constant c3{ 7.0 };
    variant_visit::Minus m{ variant_visit::Expr{p}, variant_visit::Expr{c3} };
    double result;
    benchmark::DoNotOptimize(result = visit_eval(m));
    assert(result == 1.0);
  }
}

BENCHMARK(BM_visit_eval_minus);

static void BM_eval_minus(benchmark::State& state)
{
  for (auto _ : state)
  {
    demo1::Constant c1{ 3.0 }, c2{ 5.0 };
    demo1::Plus p{ &c1, &c2 };
    demo1::Constant c3{ 7.0 };
    demo1::Minus m{ &p, &c3 };
    double result;
    benchmark::DoNotOptimize(result = demo1::demo_eval(m));
    assert(result == 1.0);
  }
}

BENCHMARK(BM_eval_minus);

int bm_baseline_print(baseline::Minus const& m)
{
  std::ostringstream os;
  baseline_print(os, m);
#ifndef NDEBUG
  std::string s = os.str();
  assert(s == "3+5-7");
#endif
  return 0;
}

static void BM_baseline_print(benchmark::State& state)
{
  for (auto _ : state)
  {
    baseline::Constant c1{ 3.0 }, c2{ 5.0 };
    baseline::Plus p{ &c1, &c2 };
    baseline::Constant c3{ 7.0 };
    baseline::Minus m{ &p, &c3 };
    benchmark::DoNotOptimize(bm_baseline_print(m));
  }
}

BENCHMARK(BM_baseline_print);

int bm_exception_print(excep::Expr const& m)
{
  std::ostringstream os;
  exception_print(os, m);
#ifndef NDEBUG
  std::string s = os.str();
  assert(s == "3+5-7");
#endif
  return 0;
}

static void BM_exception_print(benchmark::State& state)
{
  for (auto _ : state)
  {
    excep::Constant c1{ 3.0 }, c2{ 5.0 };
    excep::Plus p{ &c1, &c2 };
    excep::Constant c3{ 7.0 };
    excep::Minus m{ &p, &c3 };
    benchmark::DoNotOptimize(bm_exception_print(m));
  }
}

BENCHMARK(BM_exception_print);

int bm_virtualfn_print(virtualfn::Expr const& m)
{
  std::ostringstream os;
  virtualfn_print(os, m);
#ifndef NDEBUG
  std::string s = os.str();
  assert(s == "3+5-7");
#endif
  return 0;
}

static void BM_virtualfn_print(benchmark::State& state)
{
  for (auto _ : state)
  {
    virtualfn::Constant c1{ 3.0 }, c2{ 5.0 };
    virtualfn::Plus p{ &c1, &c2 };
    virtualfn::Constant c3{ 7.0 };
    virtualfn::Minus m{ &p, &c3 };
    benchmark::DoNotOptimize(bm_virtualfn_print(m));
  }
}

BENCHMARK(BM_virtualfn_print);

int bm_visit_print(variant_visit::Expr const& m)
{
  std::ostringstream os;
  visit_print(os, m);
#ifndef NDEBUG
  std::string s = os.str();
  assert(s == "3+5-7");
#endif
  return 0;
}

static void BM_visit_print(benchmark::State& state)
{
  for (auto _ : state)
  {
    variant_visit::Constant c1{ 3.0 }, c2{ 5.0 };
    variant_visit::Plus p{ variant_visit::Expr{c1}, variant_visit::Expr{c2} };
    variant_visit::Constant c3{ 7.0 };
    variant_visit::Minus m{ variant_visit::Expr{p}, variant_visit::Expr{c3} };
    benchmark::DoNotOptimize(bm_visit_print(m));
  }
}

BENCHMARK(BM_visit_print);

int bm_demo_print(demo1::Expr const& m)
{
  std::ostringstream os;
  demo1::demo_print(os, m);
#ifndef NDEBUG
  std::string s = os.str();
  assert(s == "3+5-7");
#endif
  return 0;
}

static void BM_print(benchmark::State& state)
{
  for (auto _ : state)
  {
    demo1::Constant c1{ 3.0 }, c2{ 5.0 };
    demo1::Plus p{ &c1, &c2 };
    demo1::Constant c3{ 7.0 };
    demo1::Minus m{ &p, &c3 };
    benchmark::DoNotOptimize(bm_demo_print(m));
  }
}

BENCHMARK(BM_print);

BENCHMARK_MAIN();
