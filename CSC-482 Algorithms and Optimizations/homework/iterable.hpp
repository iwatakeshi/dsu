#ifndef ITERABLE_H
#define ITERABLE_H
#include <vector>

template <class T>
struct iterable {
  T _begin;
  U _end;
  std::vector<T>::iterator outer, outer_end; // Outer iterators
  std::vector<T>::iterator inner, inner_end; // Inner iterators
  std::vector<T> dummy;
  iterable(T begin, T end)
      : _begin(begin)
      , _end(end) {
    outer = begin();
    outer_end = end();
    if (outer != outer_end) {
      inner = begin();
      inner_end = end();
    } else { // If vector is empty, then the inner iterators have nothing to point to
      inner = dummy.begin(); // therefore we create an empty array 'dummy'
      inner_end = dummy.end(); // which inner iterators could point to.
    }
  }

  T begin() {
    return _begin;
  }

  T end() {
    return _end;
  }

  T next() {
    T val = *inner;
    if (hasNext()) {
      inner++; // Increase the inner iterator so that next time 'hasNext()'
    }

    return val; // is called, we'd reach the element that comes after val.
  }

  bool hasNext() {
    if (outer == outer_end) return false; // If we have reached the end of array, return false

    while (inner == inner_end) { // If the inner iterator reaches the end of a subarray
      outer++; // then check the next subarray
      if (outer == outer_end) return false; // If there is no subarray that follows, then there is no 'next' element
      inner = outer->begin(); //  otherwise we reinitialize the inner iterators
      inner_end = outer->end();
    }
    return true;
  }
};

template <class T>
iterable<T> make_iterable(T a, T b) {
  return iterable<T>(a, b);
}

#endif