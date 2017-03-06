// -*- mode: C++; c-indent-level: 4; c-basic-offset: 4; indent-tabs-mode: nil; -*-

#include <RcppBenchmark.h>

#define BASIC_BENCHMARK_TEST(x) BENCHMARK(x)->Arg(8)->Arg(512)->Arg(8192)


void BM_empty(benchmark::State& state) {
    while (state.KeepRunning()) {
        benchmark::DoNotOptimize(state.iterations());
    }
}
BENCHMARK(BM_empty);
BENCHMARK(BM_empty)->ThreadPerCpu();


void BM_spin_empty(benchmark::State& state) {
  while (state.KeepRunning()) {
    for (int x = 0; x < state.range(0); ++x) {
      benchmark::DoNotOptimize(x);
    }
  }
}
BASIC_BENCHMARK_TEST(BM_spin_empty);
BASIC_BENCHMARK_TEST(BM_spin_empty)->ThreadPerCpu();


void BM_spin_pause_before(benchmark::State& state) {
  for (int i = 0; i < state.range(0); ++i) {
    benchmark::DoNotOptimize(i);
  }
  while (state.KeepRunning()) {
    for (int i = 0; i < state.range(0); ++i) {
      benchmark::DoNotOptimize(i);
    }
  }
}
BASIC_BENCHMARK_TEST(BM_spin_pause_before);
BASIC_BENCHMARK_TEST(BM_spin_pause_before)->ThreadPerCpu();


void BM_spin_pause_during(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    for (int i = 0; i < state.range(0); ++i) {
      benchmark::DoNotOptimize(i);
    }
    state.ResumeTiming();
    for (int i = 0; i < state.range(0); ++i) {
      benchmark::DoNotOptimize(i);
    }
  }
}
BASIC_BENCHMARK_TEST(BM_spin_pause_during);
BASIC_BENCHMARK_TEST(BM_spin_pause_during)->ThreadPerCpu();


void BM_pause_during(benchmark::State& state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    state.ResumeTiming();
  }
}
BENCHMARK(BM_pause_during);
BENCHMARK(BM_pause_during)->ThreadPerCpu();
BENCHMARK(BM_pause_during)->UseRealTime();
BENCHMARK(BM_pause_during)->UseRealTime()->ThreadPerCpu();


//' Simple microbenchmarking examples
//'
//' @title Simple Google Benchmark micro-benchmarking examples
//' @return None
// [[Rcpp::export]]
void example0() {
    
    BENCHMARK_MAIN();           // a re-defined function in our case
}

