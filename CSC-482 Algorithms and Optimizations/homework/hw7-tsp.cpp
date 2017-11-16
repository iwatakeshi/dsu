// #include "commander.h"
// #include <numeric>
// #include <random>
#include "edge.hpp"
#include "graph.hpp"
#include "mst.hpp"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <numeric>
#include <random>
#include <stdio.h>
#include <tuple>
#include <vector>

class TSP {
  public:
  Graph graph;
  TSP(Graph* graph) {
    this->graph = *graph;
  };

  // A non-recursive approach in order to avoid confusion
  std::tuple<int, std::vector<int>> brute() {
    int best_distance = std::numeric_limits<int>::max();
    std::vector<int> best_tour;
    std::vector<int> tour(graph.size());
    // Create tour
    for (int i = 0; i < tour.size(); i++) {
      tour[i] = i;
    }

    // Permutate the tours
    while (std::next_permutation(tour.begin(), tour.end())) {

      // Calculate the distance
      int current_distance = graph.edgeWeight(tour[0], tour[tour.size() - 1]);
      for (int i = 1; i < tour.size(); i++) {
        current_distance += graph.edgeWeight(tour[i - 1], tour[i]);
      }

      // Set the best distance and tour when found
      if (current_distance < best_distance) {
        best_distance = current_distance;
        best_tour = tour;
      }
    }

    // Add the final destination
    best_tour.push_back(0);
    return make_tuple(best_distance, best_tour);
  }

  std::tuple<int, std::vector<int>> greedy() {
    int distance = 0;
    std::vector<int> visited;
    std::vector<int> tour;
    // Current vertex will start from vertex 0
    int current = 0;
    int next;
    tour.push_back(current);

    int size = graph.size();
    visited.push_back(current);

    // Repeat until all vertices are visisted
    while (visited.size() != size) {
      int min = std::numeric_limits<int>::max();
      // Find nearest vertex (loop over vertices)
      for (int j = 0; j < size; j++) {
        // Vertex not visited
        if (std::find(visited.begin(), visited.end(), j) == visited.end()) {
          auto weight = graph.edgeWeight(current, j);
          if (min > weight) {
            min = weight;
            next = j;
          }
        }
      }

      // Get the weight of the current -> next
      distance += graph.edgeWeight(current, next);
      current = next;
      // The vertex has been visited
      visited.push_back(current);
      // Add the vertex to the tour
      tour.push_back(current);
    }
    // Get the final distance from last -> home
    distance += graph.edgeWeight(tour[tour.size() - 1], 0);
    // Add 0 as the final destination
    tour.push_back(0);
    return make_tuple(distance, tour);
  }

  std::tuple<int, std::vector<int>> montecarlo(const int k) {
    int best_distance = std::numeric_limits<int>::max();
    std::vector<int> tour = graph.vertices(), best_tour;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    /* Shuffles the vector */
    auto uniform_shuffle = [](std::vector<int>& tour, unsigned seed) {
      shuffle(tour.begin(), tour.end(), std::default_random_engine(seed));
    };
    /* Calculate the tour's distance (total weight)*/
    auto tour_distance = [](Graph& graph, std::vector<int>& tour) {
      int distance = 0;
      // Calculate the weight from 0 --> next
      distance += graph.edgeWeight(0, tour[0]);
      // Calculate the weight from next --> 0 (final edge)
      distance += graph.edgeWeight(tour[tour.size() - 1], 0);

      // Calculate the weight
      for (int i = 0; i < tour.size() - 1; i++) {
        distance += graph.edgeWeight(tour[i], tour[i + 1]);
      }
      return distance;
    };

    int counter = 0;
    while (counter < k) {
      // Shuffle the tour
      uniform_shuffle(tour, seed);
      // Get the distance
      int distance = tour_distance(graph, tour);
      if (distance < best_distance) {
        best_distance = distance;
        best_tour = tour;
      }
      counter++;
    }
    // Insert the source
    best_tour.insert(best_tour.begin(), 0);
    // Insert the destination
    best_tour.push_back(0);
    return make_tuple(best_distance, best_tour);
  }


  std::tuple<int, std::vector<int>> double_mst() {
    MST mst(graph);
    mst.generate(MSTGenerator::Kruskal);

    std::vector<int> tour;
    printf("Weight: %d\n", mst.distance());
    return std::make_tuple(0, tour);
  }

  static void
  print(std::tuple<int, std::vector<int>> solution) {
    auto distance = std::get<0>(solution);
    auto tour = std::get<1>(solution);
    char letters[26] = {
      'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
      'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
    };
    printf("Tour: ");
    for (int i = 0; i < tour.size(); i++) {
      printf("%c ", letters[tour[i]]);
      if (i != tour.size() - 1) {
        printf("--> ");
      }
    }
    printf("\n");
    printf("Weight: %d\n", distance);
  }
};

int main(int argc, char* argv[]) {
  //   // Expect N
  //   cmd_opt_value();
  //   cmd_opt("-b", "--benchmark", false);
  //   int option;
  //   int N = 0;
  //   while ((option = cmd_parse(argc, argv)) != -1) {
  //     switch (option) {
  //     case 1:
  //       N = atoi(argv[cmd_val_index()]);
  //       break;
  //     default:
  //       break;
  //     }
  //   }
  //   printf("N: %d\n", N);
  clock_t start, stop;
  srand(time(0));

  int n = 4, low = 1, high = 4, root = 0;

  Graph graph(n);

  graph.randomize(low, high);
  graph.print();

  TSP tsp(&graph);

  printf("\nBrute:\n");
  start = clock();
  auto solution1 = tsp.brute();
  stop = clock();
  TSP::print(solution1);
  printf("Time: %f\n", (stop - start) / (double)CLOCKS_PER_SEC);

  printf("\nGreedy:\n");
  start = clock();
  auto solution2 = tsp.greedy();
  stop = clock();
  TSP::print(solution2);
  printf("Time: %f\n", (stop - start) / (double)CLOCKS_PER_SEC);

  printf("\nMonte Carlo:\n");
  start = clock();
  int iterations = 10;
  auto solution3 = tsp.montecarlo(iterations);
  stop = clock();
  TSP::print(solution3);
  printf("Time: %f\n", ((stop - start) / (double)CLOCKS_PER_SEC) / iterations);

  printf("\nChristo (Heuristic):\n");
  start = clock();
  tsp.double_mst();
  stop = clock();
  // TSP::print(solution2);
  printf("Time: %f\n", (stop - start) / (double)CLOCKS_PER_SEC);

  return 0;
}