#include "bench.h"
#include "tsp.hpp"
#include <ctime>
#include <map>
#include <numeric>
#include <stdio.h>
#include <string>
#include <tuple>
#include <vector>

void printbar(int length) {
  for (int i = 0; i < length; i++)
    printf("-");
  printf("\n");
}

int main() {
  srand(time(0));
  std::map<std::string, std::vector<double>> test_quality;
  std::map<std::string, std::vector<double>> test_distance;
  std::map<std::string, std::vector<double>> test_time;
  std::map<std::string, std::vector<std::string>> test_tour;

  const std::string brute = "Brute (Non-recursive)";
  const std::string dynamic = "Dynamic Programming (Non-recursive)";

  printf("%-5s%-50s%-20s%-20s%-20s\n", "N", "Algorithm", "Time", "Distance", "Tour");
  printbar(150);
  const int N = 25;

  for (int n = 4; n < N; n++) {
    TSP tsp(n, 1, 10);
    if (n < 13) {
      std::tuple<double, tsp_t> result = Bench::time(([&]() { return tsp.brute(); }));
      double time = std::get<0>(result);
      tsp_t solution = std::get<1>(result);
      printf("%-5d%-50s%-20f%-20f%-20s\n",
          n,
          brute.c_str(),
          time,
          (double)std::get<0>(solution),
          TSP::tour_to_string(std::get<1>(solution)).c_str());
    }

    std::tuple<double, tsp_t> result = Bench::time(([&]() { return tsp.dynamic(); }));
    double time = std::get<0>(result);
    tsp_t solution = std::get<1>(result);
    printf("%-5d%-50s%-20f%-20f%-20s\n",
        n,
        dynamic.c_str(),
        time,
        (double)std::get<0>(solution),
        TSP::tour_to_string(std::get<1>(solution)).c_str());
    printbar(150);
  }
  return 0;
}