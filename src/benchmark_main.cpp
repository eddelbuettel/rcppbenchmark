#include <RcppBenchmark.h>

void BENCHMARK_MAIN() {
    char* argv[] = { (char*) "RcppBenchmark" };
    int argc = sizeof(argv)/sizeof(argv[0]);

    ::benchmark::Initialize(&argc, argv);
    ::benchmark::RunSpecifiedBenchmarks(); 
}
