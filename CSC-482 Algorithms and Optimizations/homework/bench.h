#ifndef BENCH_H
#define BENCH_H
#include <ctime>
#include <string>
#include <functional>

class Bench {
  public:
  static void bench(std::string title, std::function<void(void)> f, bool enabled) {
    clock_t start, stop;
    start = clock();
    f();
    printf("Time: %3.2f", (stop - stop) / (double) CLOCKS_PER_SEC);
  }
}

#endif