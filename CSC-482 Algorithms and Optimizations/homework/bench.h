#ifndef BENCH_H
#define BENCH_H

#include <chrono>
#include <iostream>
using Clock = std::chrono::steady_clock;
using std::chrono::time_point;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

namespace bench {
  time_point<Clock> start() {
    return Clock::now();
  }

  time_point<Clock> end() {
    return Clock::now();
  }

  auto measure(time_point<Clock> start, time_point<Clock> end) {
    return duration_cast<milliseconds>(end - start).count();
  }
}

#endif