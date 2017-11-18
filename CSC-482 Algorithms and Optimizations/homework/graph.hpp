#ifndef GRAPH_H
#define GRAPH_H
#include "edge.hpp"
#include <algorithm>
#include <array>
#include <cstring>
#include <iterator>
#include <limits>
#include <list>
#include <numeric>
#include <stdexcept>
#include <vector>

class Graph {
  private:
  // The edges of a graph
  std::vector<Edge> edges_;
  // The vertices of a graph
  std::vector<int> vertices_;
  // The adjacency matrix representation of the graph
  std::vector<std::vector<int>> adjacency_matrix_;
  // The adjacency matrix representation of the edges
  std::vector<std::vector<Edge>> edge_matrix_;
  // The adjacency matrix representation of the graph in the form of a list
  std::vector<std::vector<int>> simple_adjacency_matrix_;

  // Size of the graph
  int size_;

  public:
  Graph(){};

  Graph(unsigned size) {
    // Size of the graph
    size_ = size;

    adjacency_matrix_.resize(size);
    edge_matrix_.resize(size);
    simple_adjacency_matrix_.resize(size);
    for (int i = 0; i < size; i++) {
      adjacency_matrix_[i].resize(size);
      edge_matrix_[i].resize(size);
      simple_adjacency_matrix_.resize(size);
    }

    for (int i = 0; i < size; i++) {
      vertices_.push_back(i);
      for (int j = 0; j < size; j++) {
        adjacency_matrix_[i][j] = 0;
      }
    }
  };

  Graph(unsigned size, int low, int high)
      : Graph(size) {
    randomize(low, high);
  }

  Graph(const Graph& other) {
    size_ = other.size_;
    adjacency_matrix_ = other.adjacency_matrix_;
    edge_matrix_ = other.edge_matrix_;
    vertices_ = other.vertices_;
    edges_ = other.edges_;
  }

  Graph(Graph& other) {
    size_ = other.size_;
    adjacency_matrix_ = other.adjacency_matrix_;
    edge_matrix_ = other.edge_matrix_;
    vertices_ = other.vertices_;
    edges_ = other.edges_;
  }

  /**
   * Assignment Operator
   */
  Graph& operator=(Graph& other) {
    size_ = other.size_;
    adjacency_matrix_ = other.adjacency_matrix_;
    edge_matrix_ = other.edge_matrix_;
    vertices_ = other.vertices_;
    edges_ = other.edges_;
    return *this;
  }

  /**
   * Generates random numbers for the adjacency matrices
   */
  void randomize(int low, int high) {
    for (int i = 0; i < size_; i++) {
      for (int j = i + 1; j < size_; j++) {
        auto num = rand() % (1 + high - low) + low;
        auto edge = Edge(i, j, num);
        edges_.push_back(edge);
        edge_matrix_[i][j] = edge;
        edge_matrix_[j][i] = edge;
        adjacency_matrix_[i][j] = num;
        adjacency_matrix_[j][i] = num;
        simple_adjacency_matrix_[i].push_back(j);
        simple_adjacency_matrix_[j].push_back(i);
      }
    }

    for (int i = 0; i < size_; i++) {
      for (int j = 0; j < size_; j++) {
        if (i == j) {
          auto edge = Edge(i, j, 0);
          edges_.push_back(edge);
          edge_matrix_[i][j] = edge;
          simple_adjacency_matrix_[i].push_back(j);
          simple_adjacency_matrix_[j].push_back(i);
        }
      }
    }

    
  }

  /**
   * Returns the edge at the specified row and column
   */
  Edge get_edge(unsigned row, unsigned column) {
    if (row >= 0 && row < size_ && column >= 0 && column < size_) {
      return edge_matrix_[row][column];
    }
    throw std::out_of_range("Index is out of range.");
  }

  /**
   * Set the edge's weight at the specified row and column
   */
  void set_edge_weight(unsigned row, unsigned column, unsigned weight) {
    if (row >= 0 && row < size_ && column >= 0 && column < size_) {
      adjacency_matrix_[row][column] = weight;
    }
    throw std::out_of_range("Index is out of range.");
  }

  /**
   * Print's the adjacency matrix
   */
  void print() {
    for (int i = 0; i < size_; i++) {
      for (int j = 0; j < size_; j++) {
        printf(" %2d", adjacency_matrix_[i][j]);
      }
      printf("\n");
    }
  }
  /**
   * Adds an edge to the matrix
   */
  void add_edge(int v, int w, int weight) {
    if ((v >= 0 && v < size_) && (w >= 0 && w < size_) && weight >= 0 && !contains(v, w)) {
      adjacency_matrix_[v][w] = weight;
      adjacency_matrix_[w][v] = weight;
      simple_adjacency_matrix_[v].push_back(w);
      simple_adjacency_matrix_[w].push_back(v);
      edges_.push_back(Edge(v, w, weight));
    }
  }
  /**
   * Determines whether an edge exists
   */
  bool contains(const int v, const int w) {
    return adjacency_matrix_[v][w] > 0;
  }

  /**
   * Removes an edges from the graph
   */
  void remove(int v, int w) {

    adjacency_matrix_[v][w] = 0;

    for (auto column : edge_matrix_) {
      auto it = std::find_if(column.begin(), column.end(), [&](const Edge& edge) mutable {
        return edge.either() == v && edge.other() == w;
      });

      if (it != column.end()) {
        it->set_weight(0);
      }
    }

    auto it = std::find_if(edges_.begin(), edges_.end(), [&](const Edge& edge) mutable {
      return edge.either() == v && edge.other() == w;
    });

    if (it != edges_.end()) {
      edges_.erase(it);
    }
  }
  /**
   * Returns an adjacent edge
   */
  std::vector<Edge> adjacent_edge(int v) {
    if (v >= 0 && v < size_) {
      return edge_matrix_[v];
    }
    throw std::out_of_range("Index is out of range.");
  }

  std::vector<int> adjacent_vertex(int v) {
    if (v >= 0 && v < size_) {
      return simple_adjacency_matrix_[v];
    }
    throw std::out_of_range("Index is out of range.");
  }

  // std::vector<std::vector<int>> adjacent_vertices() {
  //   std::vector<std::vector<int>> adj;
  // }
  
  /**
   * Returns an adjacency matrix
   */
  std::vector<std::vector<int>> simple_adjacency_matrix() {
    return simple_adjacency_matrix_;
  }

  /**
   * Returns an adjacency matrix
   */
  std::vector<std::vector<int>> adjacency_matrix() {
    return adjacency_matrix_;
  }

  /**
   * Returns the edge matrix
   */
  std::vector<std::vector<Edge>> edge_matrix() {
    return edge_matrix_;
  }

  /**
   * Returns a list of vertices
   */
  std::vector<int> vertices() {
    return vertices_;
  }

  /**
   * Returns a list of edges
   */
  std::vector<Edge> edges() {
    return edges_;
  }

  /**
   * Returns the intial size of the graph (size)
   */
  int size() {
    return size_;
  }

  /**
   * Returns the initial size of the matrix (size * size)
   */
  int matrix_size() {
    return size_ * size_;
  }

  // std::vector<std::vector<int>> find_perfect_matching(std::vector<std::vector<int>> adj_matrix, std::vector<int> odd_degree_vertices) {
  //   int closest, distance;
  //   std::vector<int>::iterator temp, first;
  //   std::vector<std::vector<int>> M = adj_matrix;

  //   while (!odd_degree_vertices.empty()) {
  //     first = odd_degree_vertices.begin();
  //     auto it = odd_degree_vertices.begin() + 1;
  //     auto end = odd_degree_vertices.end();
  //     distance = std::numeric_limits<int>::max();
  //     for (; it != end; ++it) {
  //       // auto d = graph[*first][*it];
  //       if (adjacency_matrix_[*first][*it] < distance) {
  //         distance = adjacency_matrix_[*first][*it];
  //         closest = *it;
  //         temp = it;
  //       }
  //     }
  //     M[*first].push_back(closest);
  //     M[closest].push_back(*first);
  //     odd_degree_vertices.erase(temp);
  //     odd_degree_vertices.erase(first);
  //   }
  //   printf("\n");
  //   int max = 0;

  //   for (int i = 0; i < M.size(); i++) {
  //     if (max < M[i].size()) {
  //       max = M[i].size();
  //     }
  //   }

  //   for (int i = 0; i < max; i++) {
  //     while (M[i].size() - 1 < max - 1) {
  //       M[i].push_back(0);
  //     }
  //   }

  //   return M;
  // }
};

#endif