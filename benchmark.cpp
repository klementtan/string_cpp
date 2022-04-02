#include <benchmark/benchmark.h>
#include "kstring.hpp"

constexpr const char * s = "01234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789";

static void BM_StdStringCopy(benchmark::State& state) {
  for (auto _ : state) {
    std::string a{s};
    for (auto i = 0; i < state.range(0); i++) {
      std::string b{a};
    }
  }
  state.SetBytesProcessed(int64_t(state.iterations()) *
                        int64_t(state.range(0)));
}
// Register the function as a benchmark
BENCHMARK(BM_StdStringCopy)->Arg(1<<10)->Arg(1<<11)->Arg(1<<12);

static void BM_KStringCopy(benchmark::State& state) {
  for (auto _ : state) {
    k::kastring a{s};
    for (auto i = 0; i < state.range(0); i++) {
      k::kastring b{a};
    }
  }
  state.SetBytesProcessed(int64_t(state.iterations()) *
                        int64_t(state.range(0)));
}
// Register the function as a benchmark
BENCHMARK(BM_KStringCopy)->Arg(1<<10)->Arg(1<<11)->Arg(1<<12);
BENCHMARK_MAIN();
