#ifndef MST_H
#define MST_H
#include "disjointset.hpp"
#include "edge.hpp"
#include <algorithm>
#include <functional>
#include <iostream>
#include <tuple>
#include <vector>

// enum MSTGenerator {
//   Kruskal,
// };

// Note to self: Use "Graph&" and not "Graph" or else compiler throws a fit! 
using MSTGenerator = std::function<std::tuple<int, std::vector<Edge>>(Graph&)>;

class MST {
  private:
  int _distance = 0;
  std::vector<Edge> _tree;
  std::vector<std::vector<int>> _adjmatrix;
  Graph _graph;
  public:
  MST(Graph graph) {
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

  std::vector<std::vector<int>> to_adjacency_matrix() {
    _adjmatrix.resize(_tree.size() * 2);
    for (int i = 0; i < _tree.size(); i++) {
      auto edge = _tree[i];
      int v = edge.either();
      int w = edge.other(v);
      // printf("%d, %d\n", v, w);
      _adjmatrix[v].push_back(w);
      _adjmatrix[w].push_back(v);
    }

    return _adjmatrix;
  }

  std::vector<int> to_odd_degree_vertices() {
    if (_adjmatrix.size() == 0) {
      to_adjacency_matrix();
    }
    std::vector<int> odd_v;
    for (int i = 0; i < _adjmatrix.size(); i++) {
      if ((_adjmatrix[i].size() % 2) != 0) {
        odd_v.push_back(i);
      }
    }
    return odd_v;
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
      printf("<%d, %d>\n", v, w);
      if (!dset.connected(v, w)) {
        dset.merge(v, w);
        T.push_back(edge);
        distance += edge.weight();
      }
    }
    return std::make_tuple(distance, T);
  }

  static auto prim(Graph graph) {

    std::vector<bool> marked(graph.size(), false);
    std::vector<Edge> edges = graph.edges();

  }

};

#endif