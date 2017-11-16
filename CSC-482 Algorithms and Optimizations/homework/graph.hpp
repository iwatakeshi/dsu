#ifndef GRAPH_H
#define GRAPH_H
#include "edge.hpp"
#include <array>
#include <cstring>
#include <iterator>
#include <limits>
#include <numeric>
#include <stdexcept>
#include <vector>

class Graph {
  private:
  std::vector<std::vector<int>> graph;
  int _size;

  public:
  Graph(){};

  Graph(unsigned size) {
    _size = size;
    graph.resize(size);
    for (int i = 0; i < size; i++) {
      graph[i].resize(size);
    }
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        graph[i][j] = 0;
      }
    }
  };

  Graph(Graph& other) {
    _size = other.size();
    graph = other.graph;
  }

  int at(int row, int column) {
    if (row < _size && column < _size) {
      return graph[row][column];
    }

    throw std::out_of_range("Index is out of range.");
  }

  void print() {
    for (int i = 0; i < _size; i++) {
      for (int j = 0; j < _size; j++) {
        printf(" %2d", graph[i][j]);
      }
      printf("\n");
    }
  }

  void randomize(int low, int high) {
    for (int i = 0; i < _size; i++) {
      for (int j = i + 1; j < _size; j++) {
        graph[i][j] = rand() % (1 + high - low) + low;
        graph[j][i] = graph[i][j];
      }
    }
  }

  void addEdge(int v, int w, int weight) {
    if ((v >= 0 && v < _size) && (w >= 0 && w < _size) && weight >= 0 && !hasEdge(v, w)) {
      graph[v][w] = weight;
      graph[w][v] = weight;
    }
  }
  int edgeWeight(const int v, const int w) {
    return graph[v][w];
  }
  bool hasEdge(const int v, const int w) {
    return graph[v][w] > 0;
  }
  void removeEdge(int v, int w) {
    graph[v][w] = 0;
  }
  std::vector<Edge> edges() {
    std::vector<Edge> _edges;
    for (int i = 0; i < _size; i++) {
      for (int j = 0; j < _size; j++) {
        if (hasEdge(i, j)) {
          Edge edge(i, j, graph[i][j]);
          _edges.push_back(edge);
        }
      }
    }
    return _edges;
  }

  std::vector<int> vertices() {
    std::vector<int> _vertices(_size - 1);
    std::iota(_vertices.begin(), _vertices.end(), 1);
    return _vertices;
  }

  std::vector<std::vector<int>> adjacency_matrix() {
    return graph;
  }

  Graph& operator=(Graph& other) {
    _size = other.size();
    graph = other.graph;
    return *this;
  }

  int size() {
    return _size;
  }

  std::vector<std::vector<int>> find_perfect_matching(std::vector<std::vector<int>> adj_matrix, std::vector<int> odd_degree_vertices) {
    int closest, distance;
    std::vector<int>::iterator temp, first;
    std::vector<std::vector<int>> M = adj_matrix;

    while (!odd_degree_vertices.empty()) {
      first = odd_degree_vertices.begin();
      auto it = odd_degree_vertices.begin() + 1;
      auto end = odd_degree_vertices.end();
      distance = std::numeric_limits<int>::max();
      for (; it != end; ++it) {
        // auto d = graph[*first][*it];
        if (graph[*first][*it] < distance) {
          distance = graph[*first][*it];
          closest = *it;
          temp = it;
        }
      }
      M[*first].push_back(closest);
      M[closest].push_back(*first);
      odd_degree_vertices.erase(temp);
      odd_degree_vertices.erase(first);
    }
    printf("\n");
    int max = 0;

    for (int i = 0; i < M.size(); i++) {
      if (max < M[i].size()) {
        max = M[i].size();
      }
    }

    for (int i = 0; i < max; i++) {
      while (M[i].size() - 1 < max - 1) {
        M[i].push_back(0);
      }
    }

    return M;
  }
};

#endif