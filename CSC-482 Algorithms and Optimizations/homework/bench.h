#ifndef BENCH_H
#define BENCH_H
#include <ctime>
#include <functional>
#include <string>
#include <tuple>

class Bench {
  public:
  template <typename func>
  static auto time(func f) {
    clock_t start, stop;
    start = clock();
    auto solution = f();
    stop = clock();
    return std::make_tuple((stop - start) / (double)CLOCKS_PER_SEC, solution);
  }
};

#endif