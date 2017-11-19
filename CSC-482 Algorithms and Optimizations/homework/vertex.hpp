#ifndef VERTEX_H
#define VERTEX_H
class Vertex {
  private:
  int x_;
  int y_;
  Vertex(int x, int y) {
    x_ = x;
    y_ = y;
  }

  int x() {
    return x_;
  }
  int y() {
    return y_;
  }
};
#endif
