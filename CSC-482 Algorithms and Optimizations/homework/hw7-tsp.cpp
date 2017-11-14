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

// class Path {
//   public:
//   int cost; // cost ultimately includes the steps from the first and last node, as well as between all interanl nodes
//   int* path; // note: the way I'm using this, only the "internal" vertices of a tour are put in the path array here
//   Path(int length) {
//     cost = 0;
//     path = new int[length];
//   }
// };

// void printsol(int n, int root, Path* solution, double elapsedTime);

// implementation of TSPBrute and TSPBruteWorker on another page
// Path* TSPBrute(int n, int root, int** G);
// Path* TSPBruteWorker(int start, int end, int tour_length, int tours[], int** G);

// // implementation of tspGreedy not provided
// Path* TSPGreedy(int n, int root, int** G);

class TSP {
  public:
  Graph graph;
  TSP(Graph* graph) {
    this->graph = *graph;
  };

  void brute() {
    int best_distance = std::numeric_limits<int>::max();
    std::vector<int> best_tour;
    std::vector<int> tour(graph.size());
    graph.print();
    // Create tour
    for (int i = 0; i < graph.size() - 1; i++) {
      if (i < 0) {
        tour[i] = i;
      } else {
        tour[i] = i + 1;
      }
    }

    // Permutate
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

    printf("Tour: ");
    for (int i = 0; i < best_tour.size(); i++) {
      printf("%d ", best_tour[i]);
    }
    printf("\n");
    printf("Weight: %d\n", best_distance);
  }
};

int main() {
  clock_t start, stop;
  srand(time(0));

  int n = 12, low = 1, high = 10, root = 0;

  Graph graph(n);

  graph.randomize(low, high);
  // graph.print();

  TSP tsp(&graph);
  tsp.brute();
  // Path *bruteSolution, *greedySolution;

  // int** G = (int**)callocm(n, n, sizeof(int*), sizeof(int));

  // symrandm(G, n, n, low, high);

  // // printm(G, n, n);

  // start = clock();
  // bruteSolution = TSPBrute(n, root, G);
  // stop = clock();
  // printsol(n, root, bruteSolution, (stop - start) / (double)CLOCKS_PER_SEC);

  // // start = clock();
  // greedySolution = TSPGreedy(n, root, G);
  // // stop = clock();
  // printsol(n, root, greedySolution, (stop - start) / (double)CLOCKS_PER_SEC);
  // freem(G, n);
  return 0;
}

// void printsol(int n, int root, Path* solution, double elapsedTime) {
//   cout << "\n\nRoot: " << root << "\n";
//   cout << "Total Nodes, N = " << n << "\n";

//   cout << "Tour: *" << root << "* --> ";
//   for (int i = 0; i < n - 1; i++) {
//     cout << solution->path[i] << " --> ";
//   }
//   cout << "*" << root << "*\n";
//   cout << "Total Cost: " << solution->cost << "\n";
//   cout << "Elapsed Time: " << elapsedTime << "\n";
// }

// // workhorse recursively finds shortest route between start and end that includes visits all tours
// Path* TSPBruteWorker(int** G, int start, int end, int tour_length, int tours[]) {
//   Path* solution = new Path(tour_length); //solution from the worker will not include the start/end nodes
//   int best_tour_cost;

//   if (tour_length == 1) { // base case: only 1 tour node between the start/end nodes
//     int path = tours[0];
//     solution->path[0] = path; // the only available node is the only step
//     solution->cost = G[start][path] + G[path][end];
//   } else {
//     int* remaining_tours = new int[tour_length - 1]; // allocate array to store remaining tour nodes for recursive call
//     // use tourNode[0] as initial first step, and fill remainingTour with 2nd through last nodes:
//     int current_node, current_best_tour, current_node_cost;

//     int next_node = tours[0];
//     int tour_cost;
//     Path* sub_tour;
//     Path* best_sub_tour = nullptr;
//     for (int i = 0; i < tour_length - 1; i++) { // initially the remaining tour nodes will be 2nd through last of the tour nodes
//       remaining_tours[i] = tours[i + 1];
//     }

//     // cycle through tours as possible first steps
//     for (int i = 0; i < tour_length; i++) {
//       current_node = next_node;
//       current_node_cost = G[start][current_node];

//       sub_tour = TSPBruteWorker(G, current_node, end, tour_length - 1, remaining_tours);
//       tour_cost = current_node_cost + sub_tour->cost;

//       if (tour_cost < best_tour_cost || i == 0) { // if we have better solution, replace current best
//         best_tour_cost = tour_cost;
//         current_best_tour = current_node;
//         free(best_sub_tour);
//         best_sub_tour = sub_tour;
//       } else {
//         free(sub_tour);
//       }
//       // swap the firstStep node with next node from remainingNodes for next goaround
//       if (i < tour_length - 1) {
//         next_node = remaining_tours[i];
//         remaining_tours[i] = current_node;
//       }
//     }
//     // construction solution.path from best first step and best sub_tour path...
//     solution->cost = best_tour_cost;
//     solution->path[0] = current_best_tour;
//     for (int i = 1; i < tour_length; i++) {
//       solution->path[i] = best_sub_tour->path[i - 1];
//     }
//     free(best_sub_tour);
//   }
//   return solution;
// }

// Path* TSPBrute(int n, int root, int** G) {
//   Path* solution;
//   int* tours = new int[n - 1];
//   for (int i = 0; i < n - 1; i++) {
//     if (i < root) {
//       tours[i] = i;
//     } else {
//       tours[i] = i + 1;
//     }
//   }
//   solution = TSPBruteWorker(G, root, root, n - 1, tours);
//   return solution;
// }

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