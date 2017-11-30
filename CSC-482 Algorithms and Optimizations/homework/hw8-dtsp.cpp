#include "bench.h"
#include "tsp.hpp"
#include <ctime>
#include <stdio.h>
#include <tuple>
#include <vector>

// typedef typename func;

int main() {
  srand(time(0));
  for (int i = 4; i < 14; i++) {
    printf("Graph size: %d x %d\n", i, i);
    TSP tsp(i, 1, 10);
    // tsp.graph.print();
    printf("\n");
    std::vector<std::function<tsp_t()>> tests = {
      ([&]() { return tsp.brute(); }),
      // ([&]() { return tsp.greedy(); }),
      ([&]() { return tsp.dynamic(); }),
    };

    for (auto test : tests) {
      auto result = Bench::time(test);
      TSP::print(std::get<1>(result));
      printf("Time: %f\n\n", std::get<0>(result));
    }
  }
  return 0;
}