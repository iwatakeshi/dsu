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
  int _distance = 0;
  std::vector<Edge> _tree;
  Graph _graph;

  public:
  MST(Graph &graph) {
    _graph = graph;
  }
  ~MST() {
  }

  int distance() {
    return _distance;
  }

  std::vector<Edge> tree() {
    return _tree;
  }

  std::tuple<int, std::vector<Edge>> generate(MSTGenerator generator) {
    auto solution = generator(_graph);
    std::tie(_distance, _tree) = solution;

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
    Graph mst(_graph.size());
    for (auto edge : _tree) {
      mst.add_edge(edge.either(), edge.other(), edge.weight());
    }
    return mst;
  }

  void print() {
    printf("Minimum Spanning Tree:\n");
    for (auto e : _tree) {
      auto v = e.either();
      auto w = e.other(v);
      printf("<%d, %d>\n", v, w);
    }
    printf("Distance: %d\n", _distance);
  }
};

class MSTAlgorithms {

  public:
  static auto kruskal(Graph graph) {
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

  static auto lazy_prim(Graph graph) {
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
    return std::make_tuple(distance, T);
  }
};

#endif