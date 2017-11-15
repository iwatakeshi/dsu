#ifndef DISJOINTSET_H
#define DISJOINTSET_H
class DisjointSet {
  private:
  int* parent;
  int* rank;
  int _size;

  public:
  DisjointSet(int size) {
    _size = size;
    parent = new int[size];
    rank = new int[size];
    // Initially, all vertices are in
    // different sets and have rank 0.
    for (int i = 0; i < size; i++) {
      rank[i] = 0;
      //every element is parent of itself
      parent[i] = i;
    }
  };

  int find(int p) {
    // for(int i = 0; i < _size; i++) {
    //   printf("%d ", parent[i]);
    // }
    // printf("\n");
    while (p != parent[p]) {
      parent[p] = parent[parent[p]]; // path compression by halving
      p = parent[p];
    }
    return p;
  }

  bool connected(int p, int q) {
    return find(p) == find(q);
  }

  void join(int p, int q) {
    int x = find(p);
    int y = find(q);
    if (x == y) return;
    // make root of smaller rank point to root of larger rank
    if (rank[x] < rank[y])
      parent[x] = y;
    else if (rank[x] > rank[y])
      parent[y] = x;
    else {
      parent[y] = x;
      rank[x]++;
    }
    _size--;
  }

  int size() {
    return _size;
  }
};
#endif