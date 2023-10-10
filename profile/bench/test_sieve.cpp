#include "benchmark/benchmark.h"

#include <array>
#include <cmath>
#include <memory>
#include <unordered_map>
#include <vector>


std::vector<long> sieve(long n) {
    std::vector<bool> arr((unsigned long)n, true);

    for (long i = 2; i <= (long)std::sqrt(n); ++i) {
        if (arr[i]) {
            for (long j = i*i; j < n; j += i) {
                arr[j] = false;
            }
        }
    }

    std::vector<long> result;
    for (long k = 2; k < n; ++k) {
        if (arr[k]) {
            result.emplace_back(k);
        }
    }
    return result;
}


std::vector<long> sieve_array(long n) {
    std::unique_ptr<bool[]> arr = std::make_unique<bool[]>(n+1);

    for (long i = 2; i <= n; ++i) {
        arr[i] = true;
    }

    for (long j = 2; j <= (long)std::sqrt(n); ++j) {
        if (arr[j]) {
            for (long k = j*j; k < n; k += j) {
                arr[k] = false;
            }
        }
    }

    std::vector<long> result;
    for (long l = 2; l < n; ++l) {
        if (arr[l]) {
            result.emplace_back(l);
        }
    }
    return result;
}


std::vector<long> sieve_map(long n) {
    std::unordered_map<long, bool> arr;

    for (long i = 2; i <= n; ++i) {
        arr[i] = true;
    }

    for (long j = 2; j <= (long)std::sqrt(n); ++j) {
        if (arr[j]) {
            for (long k = j*j; k < n; k += j) {
                arr[k] = false;
            }
        }
    }

    std::vector<long> result;
    for (long l = 2; l < n; ++l) {
        if (arr[l]) {
            result.emplace_back(l);
        }
    }
    return result;
}


static void BM_Sieve_Vector(benchmark::State& state) {
    for (auto _ : state) {
        benchmark::DoNotOptimize(sieve(100000));
    }
}
BENCHMARK(BM_Sieve_Vector);


static void BM_Sieve_Array(benchmark::State& state) {
    for (auto _ : state) {
        benchmark::DoNotOptimize(sieve_array(100000));
    }
}
BENCHMARK(BM_Sieve_Array);


static void BM_Sieve_Map(benchmark::State& state) {
    for (auto _ : state) {
        benchmark::DoNotOptimize(sieve_map(100000));
    }
}
BENCHMARK(BM_Sieve_Map);


BENCHMARK_MAIN();
