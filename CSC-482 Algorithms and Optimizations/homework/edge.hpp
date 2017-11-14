#ifndef EDGE_H
#define EDGE_H
#include <deque>
#include <vector>

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
    _weight = edge.weight();
    _v = edge.either();
    _w = edge.other();
  };
  
  static std::deque<Edge> toQueue(std::vector<Edge> edges) {
    std::deque<Edge> q;
    for (const auto& edge : edges)
      q.push_back(edge);
    return q;
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
    return -1;
  }
  int weight() const {
    return _weight;
  }
};
#endif