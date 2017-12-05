#ifndef ITERABLE_PRIORITY_QUEUE_H
#define ITERABLE_PRIORITY_QUEUE_H
#include <algorithm>
#include <vector>

template <typename T>
class iterable_priority_queue : public std::iterator<std::input_iterator_tag, T> {
  public:
  iterable_priority_queue(int size) {
    pq.resize(size);
    N = 0;
  }
  iterable_priority_queue() {
    N = 1;
    pq.resize(1);
  }
  auto size() {
    return pq.size();
  }
  void push(T item) {
    pq.push_back(item);
    N++;
    std::sort(pq.begin(), pq.end());
  }

  auto top() {
    return *pq.begin();
  }

  bool empty() {
    return pq.empty();
  }
  T delMin() {
    auto top = pq.begin();
    pq.erase(top);
    return *top;
  }

  bool contains(T item) {
    for (auto i : pq) {
      if (i == item) return true;
    }
    return false;
  }
  auto begin() { return pq.begin(); }
  auto end() { return pq.end(); }
  // void update(T item) {
  //   for (int i = 0; i < N + 1; i++) {
  //     if (pq[i] == item) {

  //       if (pq[i] > item) {
  //         pq[i] = item;
  //         exch(i, N);
  //         swim(N);
  //       }
  //     }
  //   }
  // }

  private:
  // Priority Queue
  int N; // queue count
  std::vector<T> pq;
};

#endif