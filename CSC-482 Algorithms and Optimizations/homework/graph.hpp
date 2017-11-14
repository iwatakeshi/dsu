#ifndef GRAPH_H
#define GRAPH_H
#include "edge.hpp"
#include "matrix.hpp"
#include <cstring>
#include <vector>

class Graph {
  private:
  int** graph;
  int _size;

  public:
  Graph(){};

  Graph(int n) {
    _size = n;
    graph = (int**)callocm(n, n, sizeof(int*), sizeof(int));
  };
  
  void print() {
    printm(graph, _size, _size);
  }

  void randomize(int low, int high) {
    symrandm(graph, _size, _size, low, high);
  }

  void addEdge(int v, int w, int weight) {
    if ((v >= 0 && v < _size) && (w >= 0 && w < _size) && weight >= 0 && !hasEdge(v, w)) {
      graph[v][w] = weight;
      graph[w][v] = weight;
    }
  }
  int getEdgeWeight(int v, int w) {
    return graph[v][w];
  }
  bool hasEdge(int v, int w) {
    return graph[v][w] > 0;
  }
  void removeEdge(int v, int w) {
    graph[v][w] = 0;
  }
  std::vector<Edge> getEdges() {
    std::vector<Edge> edges;
    for (int i = 0; i < _size; i++) {
      for (int j = 0; _size; j++) {
        if (hasEdge(i, j)) {
          Edge edge(i, j, graph[i][j]);
          edges.push_back(edge);
        }
      }
    }
    return edges;
  }

  // Graph& operator=(Graph& other) {
  //   _size = other.size();
  //   Graph temp(_size);
  //   for (int i = 0; i < _size; i++) {
  //     for (int j = 0; j < _size; j++) {
  //       temp.graph[i][j] = other.graph[i][j];
  //     }
  //   }
  //   return temp;
  // }

  int size() {
    return _size;
  }
};

#endif