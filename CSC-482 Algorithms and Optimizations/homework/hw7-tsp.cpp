// #include "commander.h"
// #include <numeric>
// #include <random>
#include "edge.hpp"
#include "graph.hpp"
#include "matrix.hpp"
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

using namespace std;

class TSP {
  public:
  Graph graph;
  TSP(Graph* graph) {
    this->graph = *graph;
  };

  // A non-recursive approach in order to avoid confusion
  tuple<int, vector<int>> brute() {
    graph.print();
    int best_distance = numeric_limits<int>::max();
    vector<int> best_tour;
    vector<int> tour(graph.size());
    // Create tour
    for (int i = 0; i < tour.size(); i++) {
      tour[i] = i;
    }

    // Permutate the tours
    while (std::next_permutation(tour.begin() + 1, tour.end())) {

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

  tuple<int, vector<int>> greedy() {
    graph.print();

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
        // printf("current: %c, j: %c\n", alpha[current], alpha[j]);
        // Vertex not visited
        if (std::find(visited.begin(), visited.end(), j) == visited.end()) {
          auto weight = graph.edgeWeight(current, j);
          if (min > weight) {
            // printf("(Not Visited) current: %c, j: %c, weight: %d\n", alpha[current], alpha[j], weight);
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

  tuple<int, vector<int>> montecarlo() {
    int distance = 0;
    vector<int> tour(graph.size());
    iota(tour.begin(), tour.end(), 1);
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    auto uniform_shuffle = [](vector<int> &tour, unsigned seed) {
      shuffle(tour.begin(), tour.end(), std::default_random_engine(seed));
    };

    printf("Before:\n");

    for (auto i : tour) {
      printf("%d ", i);
    }
    printf("\n");
    uniform_shuffle(tour, seed);
    tour.insert(tour.begin(), 0);
    tour.push_back(0);
    printf("After:\n");
    for (auto i : tour) {
      printf("%d ", i);
    }
    printf("\n");

    

    for(int i = 0; i < tour.size() - 1; i++) {
      distance += graph.edgeWeight(tour[i], tour[i + 1]);
    }

    return make_tuple(distance, tour);
  }

  static void print(tuple<int, vector<int>> solution) {
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

  int n = 4, low = 1, high = 10, root = 0;

  Graph graph(n);

  graph.randomize(low, high);
  graph.print();

  TSP tsp(&graph);
  printf("\nBrute:\n");
  start = clock();
  TSP::print(tsp.brute());
  stop = clock();
  printf("Time: %f\n", (stop - start) / (double)CLOCKS_PER_SEC);
  printf("\nGreedy:\n");
  start = clock();
  TSP::print(tsp.greedy());
  stop = clock();
  printf("Time: %f\n", (stop - start) / (double)CLOCKS_PER_SEC);

  start = clock();
  TSP::print(tsp.montecarlo());
  stop = clock();
  printf("Time: %f\n", (stop - start) / (double)CLOCKS_PER_SEC);
  return 0;
}