// #include "commander.h"
// #include <numeric>
// #include <random>
#include <stdio.h>
// #include <stdlib.h>
// #include <vector>

#include "edge.hpp"
#include "graph.hpp"
#include "matrix.hpp"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class DisjointSet {
  private:
  int* parent;
  int* rank;
  int _size;

  public:
  DisjointSet(int size) {
    _size = size;
    parent = new int[size];
    rank = new int[size];
    // Initially, all vertices are in
    // different sets and have rank 0.
    for (int i = 0; i < size; i++) {
      rank[i] = 0;
      //every element is parent of itself
      parent[i] = i;
    }
  };

  int find(int p) {
    // for(int i = 0; i < _size; i++) {
    //   printf("%d ", parent[i]);
    // }
    // printf("\n");
    while (p != parent[p]) {
      parent[p] = parent[parent[p]]; // path compression by halving
      p = parent[p];
    }
    return p;
  }

  bool connected(int p, int q) {
    return find(p) == find(q);
  }

  void join(int p, int q) {
    int x = find(p);
    int y = find(q);
    if (x == y) return;
    // make root of smaller rank point to root of larger rank
    if (rank[x] < rank[y])
      parent[x] = y;
    else if (rank[x] > rank[y])
      parent[y] = x;
    else {
      parent[y] = x;
      rank[x]++;
    }
    _size--;
  }

  int size() {
    return _size;
  }
};

class TSP {
  private:
  char alpha[26];

  public:
  Graph graph;
  TSP(Graph* graph) {
    this->graph = *graph;
    char letters[26] = {
      'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
      'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
    };
    std::copy(std::begin(letters), std::end(letters), std::begin(alpha));
  };

  // A non-recursive approach in order to avoid confusion
  void brute() {
    graph.print();
    int best_distance = std::numeric_limits<int>::max();
    std::vector<int> best_tour;
    std::vector<int> tour(graph.size());
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

    printf("Tour: ");
    for (int i = 0; i < best_tour.size(); i++) {
      printf("%c ", alpha[best_tour[i]]);
      if (i < best_tour.size() - 1) {
        printf("--> ");
      }
    }
    printf("\n");
    printf("Weight: %d\n", best_distance);
  }

  void greedy() {
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

    printf("\nTour: ");
    for (int i = 0; i < tour.size(); i++) {
      printf("%c ", alpha[tour[i]]);
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
  tsp.brute();
  stop = clock();
  printf("Time: %f\n", (stop - start) / (double)CLOCKS_PER_SEC);
  printf("\nGreedy:\n");
  start = clock();
  tsp.greedy();
  stop = clock();
  printf("Time: %f\n", (stop - start) / (double)CLOCKS_PER_SEC);
  return 0;
}