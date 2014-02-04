#include <nonius/nonius.h++>

#include <iterator>
#include <string>

int main() {
    nonius::configuration cfg;
    nonius::benchmark benchmarks[] = {
        nonius::benchmark("to_string(42)", []{ return std::to_string(42); }),
        nonius::benchmark("to_string(4.2)", []{ return std::to_string(4.2); }),
    };

    nonius::go(cfg, std::begin(benchmarks), std::end(benchmarks));
}

