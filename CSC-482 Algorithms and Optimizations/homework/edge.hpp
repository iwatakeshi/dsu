#ifndef EDGE_H
#define EDGE_H
class Edge {
  public:
  int weight;
  int start;
  int end;
  Edge() {
    this->weight = this->start = this->end = 0;
  }
  Edge(const int start, const int end, const int weight) {
    this->start = start;
    this->end = end;
    this->weight = weight;
  }
  Edge(const Edge& edge) {
    this->weight = edge.weight;
    this->start = edge.start;
    this->end = edge.end;
  }
};
#endif