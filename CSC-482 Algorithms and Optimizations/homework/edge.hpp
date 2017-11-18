#ifndef EDGE_H
#define EDGE_H
#include <deque>
#include <functional>
#include <queue>
#include <vector>
#include <set>
#include <stdexcept>

  class Edge {
  private:
  int _weight;
  int _v;
  int _w;

  public:
  Edge() {
    _weight = _v = _w = 0;
  };
  Edge(const int v, const int w, const int weight) {
    _v = v;
    _w = w;
    _weight = weight;
  };
  Edge(const Edge& edge) {
    _weight = edge._weight;
    _v = edge._v;
    _w = edge._w;
  };

  bool operator<(const Edge& edge) {
    return _weight < edge.weight();
  }

  bool operator<=(const Edge& edge) {
    return _weight <= edge.weight();
  }

  bool operator>(const Edge& edge) {
    return _weight > edge.weight();
  }

  bool operator>=(const Edge& edge) {
    return _weight >= edge.weight();
  }

  friend bool operator<(const Edge& a, const Edge& b) {
    return a.weight() < b.weight();
  }

  friend bool operator<=(const Edge& a, const Edge& b) {
    return a.weight() <= b.weight();
  }

  friend bool operator>(const Edge& a, const Edge& b) {
    return a.weight() > b.weight();
  }

  friend bool operator>=(const Edge& a, const Edge& b) {
    return a.weight() >= b.weight();
  }

  static std::priority_queue<Edge> to_priority_queue(std::vector<Edge> edges) {
    std::priority_queue<Edge> q;
    for (const auto& edge : edges)
      q.push(edge);
    return q;
  }

  static std::deque<Edge> to_deque(std::vector<Edge> edges) {
    std::deque<Edge> q;
    for (const auto& edge : edges)
      q.push_back(edge);
    return q;
  }

  static std::set<Edge> to_set(std::vector<Edge> edges) {
    std::set<Edge> s;
    for(const auto& edge : edges) {
      s.insert(edge);
    }
    return s;
  }

  int either() const {
    return _v;
  }
  int other() const {
    return _w;
  }
  int other(int v) const {
    if (v == _v) return _w;
    if (v == _w) return _v;
    throw std::out_of_range("Index is out of range.");
  }
  void set_weight(unsigned weight) {
    _weight = weight;
  }
  int weight() const {
    return _weight;
  }
};


#endif