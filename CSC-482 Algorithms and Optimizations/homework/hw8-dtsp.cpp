#include "bench.h"
#include "tsp.hpp"
#include <ctime>
#include <map>
#include <numeric>
#include <stdio.h>
#include <string>
#include <tuple>
#include <vector>

int main() {
  srand(time(0));
  std::map<std::string, std::vector<double>> test_quality;
  std::map<std::string, std::vector<double>> test_distance;
  std::map<std::string, std::vector<double>> test_time;
  std::map<std::string, std::vector<std::string>> test_tour;

  const std::string brute = "Brute (Non-recursive)";
  const std::string dynamic = "Dynamic Programming";

  for (int n = 4; n < 10; n++) {
    printf("N = %d\n", n);
    for (int i = 0; i < 150; i++)
      printf("-");
      printf("\n");
    for (int trial = 0; trial < 10; trial++) {
      TSP tsp(n, 1, n);
      std::vector<std::function<tsp_t()>> tests = {
        ([&]() { return tsp.brute(); }),
        ([&]() { return tsp.dynamic(); }),
      };
      double last_brute_distance;
      printf("Trial = %d\n", trial);
      printf("%-25s%-20s%-20s%-20s%-20s\n", "Algorithm", "Quality", "Distance", "Time", "Tour");
      for (auto test : tests) {
        auto result = Bench::time(test);
        auto solution = std::get<1>(result);
        std::string name = std::get<2>(solution), tour = TSP::tour_to_string(std::get<1>(solution));
        double distance = std::get<0>(solution), time = std::get<0>(result);

        test_distance[name].push_back(distance);
        test_time[name].push_back(time);
        test_tour[name].push_back(tour);
        if (name == dynamic) {
          auto brute_distance = test_distance[brute];

          test_quality[name].push_back(distance / brute_distance.back());
          // printf("here: %f, %f\n", distance, brute_distance.back());
        } else
          test_quality[name].push_back(1.0);
      }

      printf("%-25s%-20f%-20f%-20f%-20s\n", brute.c_str(),
          test_quality[brute].back(),
          test_distance[brute].back(),
          test_time[brute].back(),
          test_tour[brute].back().c_str());
      printf("%-25s%-20f%-20f%-20f%-20s\n", dynamic.c_str(),
          test_quality[dynamic].back(),
          test_distance[dynamic].back(),
          test_time[dynamic].back(),
          test_tour[dynamic].back().c_str());
      printf("\n");
    }
    printf("%-25s%-20s%-20s%-20s\n", "Algorithm", "Average Quality", "Average Distance", "Average Time");

    printf("%-25s%-20f%-20f%-20f\n", brute.c_str(),
        double(std::accumulate(test_quality[brute].begin(), test_quality[brute].end(), 0.0) / test_quality[brute].size()),
        double(std::accumulate(test_distance[brute].begin(), test_distance[brute].end(), 0.0) / test_distance[brute].size()),
        double(std::accumulate(test_time[brute].begin(), test_time[brute].end(), 0.0) / test_time[brute].size()));

    printf("%-25s%-20f%-20f%-20f\n", dynamic.c_str(),
        double(std::accumulate(test_quality[dynamic].begin(), test_quality[dynamic].end(), 0.0) / test_quality[dynamic].size()),
        double(std::accumulate(test_distance[dynamic].begin(), test_distance[dynamic].end(), 0.0) / test_distance[dynamic].size()),
        double(std::accumulate(test_time[dynamic].begin(), test_time[dynamic].end(), 0.0) / test_time[dynamic].size()));
    for (int i = 0; i < 150; i++)
      printf("-");
    printf("\n");

    std::vector<std::string> names = { brute, dynamic };
    for(auto name: names) {
      test_quality[name].clear();
      test_distance[name].clear();
      test_time[name].clear();
      test_tour[name].clear();
    }
  }
  return 0;
}