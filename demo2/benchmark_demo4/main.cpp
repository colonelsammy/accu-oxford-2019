#include <benchmark/benchmark.h>
#include <sstream>

#include <constant.hpp>
#include <plus.hpp>
#include <minus.hpp>
#include <baseline.hpp>
#include <exception.hpp>

double baseline_eval(baseline::Plus const& expr);
void baseline_print(std::ostream& os, baseline::Plus const& expr);
double baseline_eval(baseline::Minus const& expr);
void baseline_print(std::ostream& os, baseline::Minus const& expr);

double exception_eval(excep::Expr const& expr);
void exception_print(std::ostream& os, excep::Expr const& expr);

namespace demo_double_dispatch
{
  double demo_eval(demo4::Expr const& expr);
  void demo_print(std::ostream& os, demo4::Expr const& expr);
}

namespace demo_single_dispatch
{
  double demo_eval(demo4::Expr const& expr);
  void demo_print(std::ostream& os, demo4::Expr const& expr);
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

static void BM_single_dispatch_eval_plus(benchmark::State& state)
{
  for (auto _ : state)
  {
    demo4::Constant c1{ 3.0 }, c2{ 5.0 };
    demo4::Plus p{ &c1, &c2 };
    double result;
    benchmark::DoNotOptimize(result = demo_single_dispatch::demo_eval(p));
    assert(result == 8.0);
  }
}

BENCHMARK(BM_single_dispatch_eval_plus);

static void BM_double_dispatch_eval_plus(benchmark::State& state)
{
  for (auto _ : state)
  {
    demo4::Constant c1{ 3.0 }, c2{ 5.0 };
    demo4::Plus p{ &c1, &c2 };
    double result;
    benchmark::DoNotOptimize(result = demo_double_dispatch::demo_eval(p));
    assert(result == 8.0);
  }
}

BENCHMARK(BM_double_dispatch_eval_plus);

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

static void BM_single_dispatch_eval_minus(benchmark::State& state)
{
  for (auto _ : state)
  {
    demo4::Constant c1{ 3.0 }, c2{ 5.0 };
    demo4::Plus p{ &c1, &c2 };
    demo4::Constant c3{ 7.0 };
    demo4::Minus m{ &p, &c3 };
    double result;
    benchmark::DoNotOptimize(result = demo_single_dispatch::demo_eval(m));
    assert(result == 1.0);
  }
}

BENCHMARK(BM_single_dispatch_eval_minus);

static void BM_double_dispatch_eval_minus(benchmark::State& state)
{
  for (auto _ : state)
  {
    demo4::Constant c1{ 3.0 }, c2{ 5.0 };
    demo4::Plus p{ &c1, &c2 };
    demo4::Constant c3{ 7.0 };
    demo4::Minus m{ &p, &c3 };
    double result;
    benchmark::DoNotOptimize(result = demo_double_dispatch::demo_eval(m));
    assert(result == 1.0);
  }
}

BENCHMARK(BM_double_dispatch_eval_minus);

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

int bm_demo_sd_print(demo4::Expr const& m)
{
  std::ostringstream os;
  demo_single_dispatch::demo_print(os, m);
#ifndef NDEBUG
  std::string s = os.str();
  assert(s == "3+5-7");
#endif
  return 0;
}

static void BM_single_dispatch_print(benchmark::State& state)
{
  for (auto _ : state)
  {
    demo4::Constant c1{ 3.0 }, c2{ 5.0 };
    demo4::Plus p{ &c1, &c2 };
    demo4::Constant c3{ 7.0 };
    demo4::Minus m{ &p, &c3 };
    benchmark::DoNotOptimize(bm_demo_sd_print(m));
  }
}

BENCHMARK(BM_single_dispatch_print);

int bm_demo_dd_print(demo4::Expr const& m)
{
  std::ostringstream os;
  demo_double_dispatch::demo_print(os, m);
#ifndef NDEBUG
  std::string s = os.str();
  assert(s == "3+5-7");
#endif
  return 0;
}

static void BM_double_dispatch_print(benchmark::State& state)
{
  for (auto _ : state)
  {
    demo4::Constant c1{ 3.0 }, c2{ 5.0 };
    demo4::Plus p{ &c1, &c2 };
    demo4::Constant c3{ 7.0 };
    demo4::Minus m{ &p, &c3 };
    benchmark::DoNotOptimize(bm_demo_dd_print(m));
  }
}

BENCHMARK(BM_double_dispatch_print);

BENCHMARK_MAIN();
