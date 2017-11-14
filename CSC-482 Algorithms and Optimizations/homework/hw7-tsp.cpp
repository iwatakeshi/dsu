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
#include <vector>

using namespace std;

class TSP {
  private:
  char alpha[26];

  public:
  Graph graph;
  TSP(Graph* graph) {
    this->graph = *graph;
    char letters[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    std::copy(std::begin(letters), std::end(letters), std::begin(alpha));
  };
  // A non-recursive approach in order to avoid confusion
  void brute() {
    int best_distance = std::numeric_limits<int>::max();
    std::vector<int> best_tour;
    std::vector<int> tour(graph.size());
    graph.print();
    // Create tour
    for (int i = 0; i < tour.size(); i++) {
      tour[i] = i;
    }

    // Permutate the tours
    while (std::next_permutation(tour.begin() + 1, tour.end())) {

      // Calculate the distance
      int current_distance = graph.getEdgeWeight(tour[0], tour[tour.size() - 1]);
      for (int i = 1; i < tour.size(); i++) {
        current_distance += graph.getEdgeWeight(tour[i - 1], tour[i]);
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

  // A greedy approach using Kruskal's Algorithm
  void greedy() {
    int best_distance = 0;
    auto edges = graph.getEdges();
    // Comparator
    auto comparator = [](Edge s, Edge t) { return s.weight < t.weight; };
    // Sort the edges
    std::sort(edges.begin(), edges.end(), comparator);

    // for (auto edge : edges) {
    //   printf("edge [%d, %d], weight %d\n", edge.start, edge.end, edge.weight);
    // }
  }
};

int main() {
  clock_t start, stop;
  srand(time(0));

  int n = 4, low = 1, high = 10, root = 0;

  Graph graph(n);

  graph.randomize(low, high);
  // graph.print();

  TSP tsp(&graph);
  tsp.brute();

  tsp.greedy();

  // // start = clock();
  // greedySolution = TSPGreedy(n, root, G);
  // // stop = clock();
  // printsol(n, root, greedySolution, (stop - start) / (double)CLOCKS_PER_SEC);
  // freem(G, n);
  return 0;
}


// void sortedges(Edge* edges[], int n) {
//   for (int i = 0; i < n - 1; i++) {
//     for (int j = 0; j < n - i - 1; j++) {
//       if (edges[j]->weight > edges[j + 1]->weight) {
//         swap(edges[j], edges[j + 1]);
//       }
//     }
//   }
// }

// // Returns the subset in which vertex i belongs
// int find(int tours[], int v) {
//   return tours[v];
// }

// void union_set(int tours[], int s1, int s2, int n) {
//   for (int i = 0; i < n; i++) {
//     if (tours[i] == s2) tours[i] = s1;
//   }
// }

// Path* TSPGreedy(int n, int root, int** G) {
//   Path* solution = new Path(n * n);
//   Edge* edges[n * n];
//   int* tours = new int[n];
//   int k = 0;
//   // Create a list of edges
//   for (int i = 0; i < n; i++) {
//     for (int j = 0; j < i; j++) {
//       if (G[i][j] != 0) {
//         edges[k++] = new Edge(i, j, G[i][j]);
//       }
//     }
//   }
//   // for(int i = 0; i < k; i++) {
//   //   printf("edge: [%d, %d], weight: %d\n", edges[i]->start, edges[i]->end, edges[i]->weight);
//   // }
//   // printf("done\n");
//   // printf("after sort:\n");

//   sortedges(edges, k);

//   for (int i = 0; i < k; i++) {
//     printf("edge: [%d, %d], weight: %d\n", edges[i]->start, edges[i]->end, edges[i]->weight);
//   }

//   for (int i = 0; i < n; i++) {
//     if (i < root) {
//       tours[i] = i;
//     } else {
//       tours[i] = i + 1;
//     }
//   }

//   int l = 0, m = 0;
//   for (int i = 0; i < k; i++) {
//     int s1 = find(tours, edges[i]->start);
//     int s2 = find(tours, edges[i]->end);

//     if (s1 != s2) {
//       solution->path[l++] = edges[i]->start;
//       solution->path[l++] = edges[i]->end;
//       solution->cost += edges[i]->weight;
//       union_set(tours, s1, s2, m++);
//     }
//   }

//   return solution;
// }

// int main(int argc, char* argv[]) {
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
//   std::vector<std::vector<long long>> M(N, std::vector<long long>(N, 0));

//   std::random_device rd;
//   std::mt19937 mt(rd());
//   std::uniform_int_distribution<> dist(0, 1);

//   for (int i = 0; i < N; i++) {
//     for (int j = 0; j < N; j++) {
//       M[i][j] = dist(mt);
//     }
//   }

//   for (int i = 0; i < N; i++) {
//     for (int j = 0; j < N; j++) {
//       printf("%lld ", M[i][j]);
//     }
//     printf("\n");
//   }

//   return cmd_free();
// }