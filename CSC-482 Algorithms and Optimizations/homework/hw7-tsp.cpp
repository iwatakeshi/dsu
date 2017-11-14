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
    for (int i = 0; i <= size; i++) {
      rank[i] = 0;
      //every element is parent of itself
      parent[i] = i;
    }
  };

  int find(int p) {
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

   /**
   * Based on Kruskal's algorithm. It only gives a suboptimal solution in general.
   * Works for complete graphs. May not work for a graph that is not complete.
   * As in Kruskal's algorithm, first sort the edges in the increasing order of weights.
   * Starting with the least cost edge, look at the edges one by one and select an edge only if the edge, together with already selected edges,
   *  1. does not cause a vertex to have degree three or more
   *  2. does not form a cycle, unless the number of selected edges equals the number of vertices in the graph.
   */
  // A greedy approach using Kruskal's Algorithm
  void greedy() {
    int best_distance = 0;
    vector<int> mst;
    auto edges = Edge::toQueue(graph.getEdges());
    // Comparator
    auto comparator = [](Edge s, Edge t) { return s.weight() < t.weight(); };
    // Sort the edges
    std::sort(edges.begin(), edges.end(), comparator);

    // for (auto edge : edges) {
    //   printf("edge [%d, %d], weight %d\n", edge.either(), edge.other(), edge.weight());
    // }

    // Create a disjoint set
    DisjointSet ds(graph.size());
    // mst.push_back(0);
    // Iterate through all sorted edges
    while (!edges.empty() && mst.size() < graph.size() - 1) {
      Edge e = edges.front();
      int v = e.either();
      int w = e.other(v);
      edges.pop_front();
      if (!ds.connected(v, w)) {
        // printf("connected\n");
        ds.join(v, w);
        mst.push_back(v);
        mst.push_back(w);
        best_distance += e.weight();
      }
    }

    printf("Tour:\n");
    for (int i = 0; i < mst.size(); i++) {
      printf("%c ", alpha[mst[i]]);
      if (i != mst.size() - 1) {
        printf("--> ");
      }
    }
    printf("\n");
    printf("Weight: %d\n", best_distance);
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
  // graph.print();

  TSP tsp(&graph);
  tsp.brute();
  printf("\nGreedy (Kruskal's Algorithm):\n");
  tsp.greedy();

  // // start = clock();
  // greedySolution = TSPGreedy(n, root, G);
  // // stop = clock();
  // printsol(n, root, greedySolution, (stop - start) / (double)CLOCKS_PER_SEC);
  // freem(G, n);
  return 0;
}