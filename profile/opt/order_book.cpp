#include "benchmark/benchmark.h"

#include <algorithm>
#include <iterator>
#include <string>
#include <string_view>
#include <utility>
#include <vector>


class OrderBook {
public:
    OrderBook(std::vector<std::pair<std::string, long>> levels)
        : mVolumes(levels.begin(), levels.end()) {}

    long get_volume(const std::string_view price_level) {
        auto it = mVolumes.find({price_level.data(), price_level.size()});
        if (it != mVolumes.end()) {
            return it->second;
        }
        return 0;
    }

private:
    std::map<std::string, long> mVolumes;
};


std::vector<std::pair<std::string, long>> make_levels() {
    std::vector<std::pair<std::string, long>> levels;
    for (long p = 712339; p < (712339 + 100000); p += 2) {
        levels.emplace_back(std::to_string(p), 100);
    }
    return levels;
}


static void BM_Get_Volume(benchmark::State& state) {
    std::vector<std::pair<std::string, long>> levels = make_levels();
    OrderBook book = {levels};

    std::vector<std::string_view> views;
    std::transform(levels.begin(), levels.end(), std::back_inserter(views),
                   [&] (const auto& p) { return p.first; });

    auto it = views.begin();
    for (auto _ : state) {
        benchmark::DoNotOptimize(book.get_volume(*it));
        if (++it == views.end()) {
            it = views.begin();
        }
    }
}
BENCHMARK(BM_Get_Volume);


BENCHMARK_MAIN();
