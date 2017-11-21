// #include "commander.h"
#include "tsp.hpp"
#include <cstdlib>
#include <ctime>
#include <functional>
#include <map>
#include <stdio.h>
#include <string>
#include <tuple>

typedef std::tuple<int, std::vector<int>, std::string> tsp_type;
typedef std::map<std::string, std::tuple<tsp_type, double>> test_type;
typedef test_type (*func)(Graph&);
typedef std::tuple<int, int> range_type;

test_type run_worst_case_greedy();

int main(int argc, char* argv[]) {
  clock_t start, stop;
  srand(time(0));

  // int n = 8, low = 1, high = 4, root = 0;
  // Graph random_g(n, low, high);
  std::vector<std::vector<std::vector<double>>> tests(2);
  std::vector<double> average_costs;
  std::vector<double> average_qualities;
  std::vector<double> average_times;
  std::vector<std::string> algorithm_names = {
    "Brute (Non-recursive)", "Greedy (Nearest Neighbor)",
    "Monte Carlo (k = 1...100)", "Kruskal's MST + Two-Approximate",
    "Prim's MST + Two-Approximate", "Kruskal's MST + A*", "Prim's MST + A*"
  };
  // Worst Case for Greedy Algorithm:
  printf("Worst Case Greedy Algorithm:\n");
  test_type worst_case = run_worst_case_greedy();
  printf("%-53s%-53s%-20s%-20s\n", "Algorithm", "Tour", "Distance", "Time");
  for (int i = 0; i < 145; i++)
    printf("-");
  printf("\n");

  for (auto t : worst_case) {
    double time;
    auto result = t.second;
    tsp_type r;
    std::tie(r, time) = result;

    printf("%-53s%-53s%-20d%-f\n", t.first.c_str(), TSP::tour_to_string(std::get<1>(r)).c_str(), std::get<0>(r), (time / (double)CLOCKS_PER_SEC));
  }

  printf("\n");
  // Testing Framework

  printf("Small N Test:\n\n");

  int total_brute_cost = 0, total_greedy_cost = 0, total_monte_cost = 0,
      total_kruskal_approx_cost = 0, total_prim_approx_cost = 0,
      total_kruskal_a_star_cost = 0, total_prim_a_star_cost = 0;

  double total_brute_time = 0, total_greedy_time = 0, total_monte_time = 0,
         total_kruskal_approx_time = 0, total_prim_approx_time = 0,
         total_kruskal_a_star_time = 0, total_prim_a_star_time = 0;

  double total_brute_quality = 0, total_greedy_quality = 0, total_monte_quality = 0,
         total_kruskal_approx_quality = 0, total_prim_approx_quality = 0,
         total_kruskal_a_star_quality = 0, total_prim_a_star_quality = 0;

  auto reset_totals = [&]() mutable {
    total_brute_cost = 0, total_greedy_cost = 0, total_monte_cost = 0,
    total_kruskal_approx_cost = 0, total_prim_approx_cost = 0,
    total_kruskal_a_star_cost = 0, total_prim_a_star_cost = 0;

    total_brute_time = 0, total_greedy_time = 0, total_monte_time = 0,
    total_kruskal_approx_time = 0, total_prim_approx_time = 0,
    total_kruskal_a_star_time = 0, total_prim_a_star_time = 0;

    total_brute_quality = 0, total_greedy_quality = 0, total_monte_quality = 0,
    total_kruskal_approx_quality = 0, total_prim_approx_quality = 0,
    total_kruskal_a_star_quality = 0, total_prim_a_star_quality = 0;
  };

  auto print_averages = [&](int n_trials, int i, bool show_brute) mutable {
    printf("%-50s%-20s%-50s%-20s\n", "Algorithm", "Average Cost", "Average Quality", "Average Time");
    for (int j = 0; j < 145; j++)
      printf("-");
    printf("\n");
    if (show_brute) {
      // Brute
      printf("%-50s%-20f%-50f%-20f\n", "Brute (Non-recursive)",
          (double)(total_brute_cost / n_trials),
          (double)(1),
          (double)(total_brute_time / n_trials));
    }

    // Greedy
    printf("%-50s%-20f%-50f%-20f\n", "Greedy (Nearest Neighbor)",
        (double)(total_greedy_cost / n_trials),
        (double)(total_greedy_quality / n_trials),
        (double)(total_greedy_time / n_trials));

    // Monte Carlo
    printf("%-50s%-20f%-50f%-20f\n", "Monte Carlo (k = 1...100)",
        (double)(total_monte_cost / n_trials),
        (double)(total_monte_quality / n_trials),
        (double)(total_monte_time / n_trials));

    // Kruskal + Two Approximate
    printf("%-50s%-20f%-50f%-20f\n", "Kruskal's MST + Two Approximate",
        (double)(total_kruskal_approx_cost / n_trials),
        (double)(total_kruskal_approx_quality / n_trials),
        (double)(total_kruskal_approx_time / n_trials));

    // Prim's + Two Approximate
    printf("%-50s%-20f%-50f%-20f\n", "Prim's MST + Two Approximate",
        (double)(total_prim_approx_cost / n_trials),
        (double)(total_prim_approx_quality / n_trials),
        (double)(total_prim_approx_time / n_trials));

    // Kruskal + A*
    printf("%-50s%-20f%-50f%-20f\n", "Kruskal's MST + A*",
        (double)(total_kruskal_a_star_cost / n_trials),
        (double)(total_kruskal_a_star_quality / n_trials),
        (double)(total_kruskal_a_star_time / n_trials));

    // Prim's + A*
    printf("%-50s%-20f%-50f%-20f\n", "Prim's MST + A*",
        (double)(total_prim_a_star_cost / n_trials),
        (double)(total_prim_a_star_quality / n_trials),
        (double)(total_prim_a_star_time / n_trials));
    printf("\n\n");
    if (i < n_trials - 1) {
      printf("%-10s%-10s%-50s%-20s\n", "N", "Trial", "Algorithm", "Time");
      for (int j = 0; j < 145; j++)
        printf("-");
      printf("\n");
    }
  };

  int k_max = 100;
  int n_max = 11;
  int n_trials = 10;
  int current_trial = 0;
  // printf("%-10s%-10s%-50s%-20s\n", "N", "Trial", "Algorithm", "Time");
  for (int i = 0; i < 145; i++)
    printf("-");
  printf("\n");
  for (int n = 4; n < n_max; n++) {
    reset_totals();
    for (int trial = 0; trial < n_trials; trial++) {
      current_trial = trial;
      // printf("%-10d%-10d", n, trial + 1);
      TSP tsp(10, 1, n);
      tsp_type solution;
      int optimal = 0, cost = 0;
      double quality;

      // printf("%-50s", "Brute (Non-recursive)");
      // Brute
      start = clock();
      solution = tsp.brute();
      stop = clock();
      optimal = std::get<0>(solution);
      total_brute_cost += optimal;
      total_brute_quality = total_brute_cost;
      total_brute_time += (stop - start) / (double)CLOCKS_PER_SEC;
      // printf("%-20f\n", (stop - start) / (double)CLOCKS_PER_SEC);

      // printf("%*c", 20, ' ');

      // Greedy
      // printf("%*c%s", 20, ' ', "Greedy (Nearest Neighbor)");
      start = clock();
      solution = tsp.greedy();
      stop = clock();
      cost = std::get<0>(solution);

      total_greedy_cost += cost;
      total_greedy_quality += cost / optimal;
      total_greedy_time += (stop - start) / (double)CLOCKS_PER_SEC;
      // printf("%*c%f\n", 25, ' ', (stop - start) / (double)CLOCKS_PER_SEC);

      //Monte Carlo
      // printf("%*c%s", 20, ' ', "Monte Carlo (k = 1...100)");

      for (int k = 1; k < k_max; k++) {
        start = clock();
        solution = tsp.montecarlo(k);
        stop = clock();
        cost = std::get<0>(solution);

        total_monte_cost += cost;
        total_monte_quality += cost / optimal;
        total_monte_time += (stop - start) / (double)CLOCKS_PER_SEC;
      }
      // printf("%-20d%-20f\n", optimal, (stop - start) / (double)CLOCKS_PER_SEC);
      // printf("\n");

      // Kruskal's MST + Two Approximate
      // printf("%*c%s", 20, ' ', "Kruskal's MST + Two-Approximate");
      start = clock();
      solution = tsp.two_approximate(MSTAlgorithms::kruskal);
      stop = clock();
      cost = std::get<0>(solution);
      // printf("%*c%f\n", 19, ' ', (stop - start) / (double)CLOCKS_PER_SEC);

      total_kruskal_approx_cost += cost;
      total_kruskal_approx_quality += cost / optimal;
      total_kruskal_approx_time += (stop - start) / (double)CLOCKS_PER_SEC;

      // Prim's MST + Two Approximate
      // printf("%*c%s", 20, ' ', "Prim's MST + Two-Approximate");
      start = clock();
      solution = tsp.two_approximate(MSTAlgorithms::lazy_prim);
      stop = clock();
      cost = std::get<0>(solution);
      // printf("%*c%f\n", 22, ' ', (stop - start) / (double)CLOCKS_PER_SEC);

      total_prim_approx_cost += cost;
      total_prim_approx_quality += cost / optimal;
      total_prim_approx_time += (stop - start) / (double)CLOCKS_PER_SEC;

      // Kruskal's MST + A*
      // printf("%*c%s", 20, ' ', "Kruskal's MST + A*");
      start = clock();
      solution = tsp.a_star(MSTAlgorithms::kruskal);
      stop = clock();
      cost = std::get<0>(solution);
      // printf("%*c%f\n", 32, ' ', (stop - start) / (double)CLOCKS_PER_SEC);

      total_kruskal_a_star_cost += cost;
      total_kruskal_a_star_quality += cost / optimal;
      total_kruskal_a_star_time += (stop - start) / (double)CLOCKS_PER_SEC;

      // Prim's MST + A*
      // printf("%*c%s", 20, ' ', "Prim's MST + A*");
      start = clock();
      solution = tsp.a_star(MSTAlgorithms::lazy_prim);
      stop = clock();
      cost = std::get<0>(solution);
      // printf("%*c%f\n", 35, ' ', (stop - start) / (double)CLOCKS_PER_SEC);

      total_prim_a_star_cost += cost;
      total_prim_a_star_quality += cost / optimal;
      total_prim_a_star_time += (stop - start) / (double)CLOCKS_PER_SEC;
      // printf("\n");
    }
    printf("N = %d\n", n);
    print_averages(n_trials, current_trial, true);
  }

  printf("\n");
  // Testing Framework

  printf("Large N Test:\n\n");

  n_trials = 50;
  n_max = 1000 + 10;
  // printf("%-10s%-10s%-50s%-20s\n", "N", "Trial", "Algorithm", "Time");
  for (int i = 0; i < 145; i++)
    printf("-");
  printf("\n");

  for (int n = 10; n < n_max; n += 10) {
    reset_totals();
    for (int trial = 0; trial < n_trials; trial++) {
      current_trial = trial;
      // printf("%-10d%-10d", n, trial + 1);
      TSP tsp(10, 1, n);
      tsp_type solution;
      int cost = 0;
      double quality;

      // printf("%*c", 20, ' ');

      // Greedy
      // printf("%*c%s", 10, ' ', "Greedy (Nearest Neighbor)");
      start = clock();
      solution = tsp.greedy();
      stop = clock();
      cost = std::get<0>(solution);

      total_greedy_cost += cost;
      total_greedy_time += (stop - start) / (double)CLOCKS_PER_SEC;
      // printf("%*c%f\n", 25, ' ', (stop - start) / (double)CLOCKS_PER_SEC);

      //Monte Carlo
      // printf("%*c%s", 20, ' ', "Monte Carlo (k = 1...100)");

      for (int k = 1; k < k_max; k++) {
        start = clock();
        solution = tsp.montecarlo(k);
        stop = clock();
        cost = std::get<0>(solution);
        total_monte_cost += cost;
        total_monte_time += (stop - start) / (double)CLOCKS_PER_SEC;
      }
      // printf("%-20d%-20f\n", optimal, (stop - start) / (double)CLOCKS_PER_SEC);
      // printf("\n");

      // Kruskal's MST + Two Approximate
      // printf("%*c%s", 20, ' ', "Kruskal's MST + Two-Approximate");
      start = clock();
      solution = tsp.two_approximate(MSTAlgorithms::kruskal);
      stop = clock();
      cost = std::get<0>(solution);
      // printf("%*c%f\n", 19, ' ', (stop - start) / (double)CLOCKS_PER_SEC);

      total_kruskal_approx_cost += cost;
      total_kruskal_approx_time += (stop - start) / (double)CLOCKS_PER_SEC;

      // Prim's MST + Two Approximate
      // printf("%*c%s", 20, ' ', "Prim's MST + Two-Approximate");
      start = clock();
      solution = tsp.two_approximate(MSTAlgorithms::lazy_prim);
      stop = clock();
      cost = std::get<0>(solution);
      // printf("%*c%f\n", 22, ' ', (stop - start) / (double)CLOCKS_PER_SEC);

      total_prim_approx_cost += cost;
      total_prim_approx_time += (stop - start) / (double)CLOCKS_PER_SEC;

      // Kruskal's MST + A*
      // printf("%*c%s", 20, ' ', "Kruskal's MST + A*");
      start = clock();
      solution = tsp.a_star(MSTAlgorithms::kruskal);
      stop = clock();
      cost = std::get<0>(solution);
      // printf("%*c%f\n", 32, ' ', (stop - start) / (double)CLOCKS_PER_SEC);

      total_kruskal_a_star_cost += cost;
      total_kruskal_a_star_time += (stop - start) / (double)CLOCKS_PER_SEC;

      // Prim's MST + A*
      // printf("%*c%s", 20, ' ', "Prim's MST + A*");
      start = clock();
      solution = tsp.a_star(MSTAlgorithms::lazy_prim);
      stop = clock();
      cost = std::get<0>(solution);
      // printf("%*c%f\n", 35, ' ', (stop - start) / (double)CLOCKS_PER_SEC);

      total_prim_a_star_cost += cost;
      total_prim_a_star_time += (stop - start) / (double)CLOCKS_PER_SEC;
      // printf("\n");
    }
    printf("N = %d\n", n);
    print_averages(n_trials, current_trial, false);
  }

  return 0;
}

test_type run_worst_case_greedy() {
  auto b = std::numeric_limits<int>::max() - 10000;

  std::vector<std::vector<int>> optimal_graph = {
    { 0, 2, 3, 3, 1, 4, 3, 2 },
    { 2, 0, 3, 2, 1, 4, 2, 4 },
    { 3, 3, 0, 1, 2, 2, 1, 2 },
    { 3, 2, 1, 0, 2, 3, 1, 3 },
    { 1, 1, 2, 2, 0, 1, 1, 2 },
    { 4, 4, 2, 3, 1, 0, 4, 1 },
    { 3, 2, 1, 1, 1, 4, 0, 2 },
    { 2, 4, 2, 3, 2, 1, 2, 0 }
  };

  std::vector<std::vector<int>> non_optimal_graph = {
    { 0, 2, 3, 3, 1, b, 3, 2 },
    { 2, 0, 3, 2, 1, 4, 2, 4 },
    { 3, 3, 0, 1, 2, 2, 1, 2 },
    { 3, 2, 1, 0, 2, 3, 1, 3 },
    { 1, 1, 2, 2, 0, 1, 1, 2 },
    { b, 4, 2, 3, 1, 0, 4, 1 },
    { 3, 2, 1, 1, 1, 4, 0, 2 },
    { 2, 4, 2, 3, 2, 1, 2, 0 }
  };
  std::vector<std::vector<std::vector<int>>> graphs = { optimal_graph, non_optimal_graph };
  std::vector<std::string> graph_types = { "Optimal Graph", "Non-optimal Graph" };
  std::vector<std::string> generator_types = { "Kruskal's MST", "Prim's MST" };
  std::vector<MSTGenerator> generators = { MSTAlgorithms::kruskal, MSTAlgorithms::lazy_prim };
  test_type times;
  clock_t start, stop;
  auto run_tsp = [&](TSP& tsp, std::string graph) {
    // Test brute
    start = clock();
    auto s1 = tsp.brute();
    stop = clock();
    times[(std::string)std::get<2>(s1) + " (" + graph + ")"] = make_tuple(s1, (stop - start));

    // Test greedy
    start = clock();
    auto s2 = tsp.greedy();
    stop = clock();
    times[(std::string)std::get<2>(s2) + " (" + graph + ")"] = make_tuple(s2, (stop - start));

  };
  auto run_tsp_gen = [&](TSP& tsp, MSTGenerator generator, std::string generator_name, std::string graph) mutable {
    // Test two-approx
    start = clock();
    auto s4 = tsp.two_approximate(generator);
    stop = clock();
    times[generator_name + " + " + std::get<2>(s4) + " (" + graph + ")"] = make_tuple(s4, (stop - start));
    // Test a-star
    start = clock();
    auto s5 = tsp.a_star(generator);
    stop = clock();
    times[generator_name + " + " + std::get<2>(s5) + " (" + graph + ")"] = make_tuple(s5, (stop - start));
  };

  for (int i = 0; i < graphs.size(); i++) {
    auto tsp = TSP(graphs[i]);
    run_tsp(tsp, graph_types[i]);
    for (int j = 0; j < generators.size(); j++) {
      run_tsp_gen(tsp, generators[j], generator_types[j], graph_types[i]);
    }
  }
  return times;
}
