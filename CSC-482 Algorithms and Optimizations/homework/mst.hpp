#ifndef MST_H
#define MST_H
#include "disjointset.hpp"
#include "edge.hpp"
#include "queue.hpp"
#include <algorithm>
#include <deque>
#include <functional>
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

// Note to self: Use "Graph&" and not "Graph" or else compiler throws a fit!
using MSTGenerator = std::function<std::tuple<int, std::vector<Edge>>(Graph&)>;

class MST {
  private:
  int distance_ = 0;
  std::vector<Edge> tree_;
  Graph graph_;

  public:
  MST(){};
  MST(Graph& graph) {
    graph_ = graph;
  }
  /**
   * Assignment Operator
   */
  MST& operator=(MST& other) {
    distance_ = other.distance_;
    tree_ = other.tree_;
    graph_ = other.graph_;
    return *this;
  }

  MST operator=(const MST& other) {
    distance_ = other.distance_;
    tree_ = other.tree_;
    graph_ = other.graph_;
    return *this;
  }

  ~MST() {
  }

  int distance() {
    return distance_;
  }

  std::vector<Edge> tree() {
    return tree_;
  }

  std::tuple<int, std::vector<Edge>> generate(MSTGenerator generator) {
    auto solution = generator(graph_);
    std::tie(distance_, tree_) = solution;
    return solution;
  }

  // std::vector<int> to_odd_degree_vertices() {
  //   if (_adjmatrix.size() == 0) {
  //     to_adjacency_matrix();
  //   }
  //   std::vector<int> odd_v;
  //   for (int i = 0; i < _adjmatrix.size(); i++) {
  //     if ((_adjmatrix[i].size() % 2) != 0) {
  //       odd_v.push_back(i);
  //     }
  //   }
  //   return odd_v;
  // }

  Graph to_graph() {
    Graph mst(graph_.size());
    for (auto edge : tree_) {
      mst.add_edge(edge.either(), edge.other(), edge.weight());
    }
    return mst;
  }

  void print() {
    printf("Minimum Spanning Tree:\n");
    for (auto e : tree_) {
      auto v = e.either();
      auto w = e.other(v);
      printf("<%d, %d>\n", v, w);
    }
    printf("Distance: %d\n", distance_);
  }
};

class MSTAlgorithms {

  public:
  static auto kruskal(Graph& graph) {
    // Get the edges of the graph
    std::vector<Edge> edges = graph.edges();
    // Sort the edges
    std::sort(edges.begin(), edges.end());
    // Define an elementary cluster (disjoint set)
    DisjointSet dset(graph.size());
    // Stores a minimum spanning tree, T
    std::vector<Edge> T;
    // Let Q be a priority queue storing the edges in G, using edge weights as keys
    auto Q = Edge::to_priority_queue(edges);

    int distance = 0;
    // Generate a minimum spanning tree
    while (T.size() < graph.size() - 1 && !Q.empty()) {
      auto edge = Q.top();
      Q.pop();
      auto v = edge.either();
      auto w = edge.other(v);
      if (!dset.connected(v, w)) {
        dset.merge(v, w);
        T.push_back(edge);
        distance += edge.weight();
      }
    }
    return std::make_tuple(distance, T);
  }

  static auto lazy_prim(Graph& graph) {
    auto edges = graph.edges();
    std::vector<Edge> T;
    bool* marked = new bool[graph.size()]();

    iterable_priority_queue<Edge> Q;
    auto visit = [&](int v) mutable {
      marked[v] = true;
      for (auto edge : graph.adjacent_edge(v)) {
        if (!marked[edge.other(v)]) {
          Q.push(edge);
        }
      }
    };

    visit(0);

    while (!Q.empty() && T.size() < graph.size() - 1) {
      auto e = Q.delMin();
      int v = e.either(), w = e.other(v);
      if (marked[v] && marked[w]) continue;
      T.push_back(e);
      if (!marked[v]) visit(v);
      if (!marked[w]) visit(w);
    }
    int distance = 0;
    for (auto e : T) {
      auto v = e.either();
      auto w = e.other(v);
      distance += e.weight();
    }
    
    delete marked[];
    return std::make_tuple(distance, T);
  }

  // //http://www.geeksforgeeks.org/greedy-algorithms-set-5-prims-minimum-spanning-tree-mst-2/
  // static auto prim(Graph& graph) {
  //   auto size = graph.size();
  //   auto cost_matrix = graph.cost_matrix();
  //   int parent[size];
  //   int key[size];
  //   bool marked[size];

  //   auto min_key = [&](int key[], bool marked[]) {
  //     int min = std::numeric_limits<int>::max(), min_index = 0;
  //     for (int v = 0; v < size; v++) {
  //       if (marked[v] == false && key[v] < min) {
  //         min = key[v], min_index = v;
  //       }
  //     }
  //     return min_index;
  //   };

  //   for (int i = 0; i < size; i++) {
  //     key[i] = std::numeric_limits<int>::max(), marked[i] = false;
  //   }

  //   key[0] = 0;
  //   parent[0] = -1;

  //   for (int count = 0; count < size - 1; count++) {
  //     int u = min_key(key, marked);
  //     marked[u] = true;

  //     for (int v = 0; v < size; v++) {
  //       if (cost_matrix[u][v] && marked[v] == false && cost_matrix[u][v] < key[v]) {
  //         parent[v] = u, key[v] = cost_matrix[u][v];
  //       }
  //     }
  //   }

  //   int distance = 0;
  //   std::vector<Edge> T;
  //   for (int v = 1; v < size; v++) {
  //     auto edge = Edge(parent[v], v, cost_matrix[v][parent[v]]);
  //     distance += edge.weight();
  //     T.push_back(edge);
  //   }

  //   return make_tuple(distance, T);
  // }
};

#endif