#ifndef VECTOR_H
#define VECTOR_H
#include <vector>
/**
 * https://discuss.leetcode.com/topic/20694/c-solution-based-on-vector-iterator
 */
template <typename T>
class vector_1d {
  std::vector<T>::iterator outer, outer_end; // Outer iterators
  std::vector<T>::iterator inner, inner_end; // Inner iterators
  std::vector<T> dummy;

  public:
  vector_2d(std::vector<T> vector) {
    outer = vector.begin();
    outer_end = vector.end();
    if (outer != outer_end) {
      inner = outer->begin();
      inner_end = outer->end();
    } else { // If vector is empty, then the inner iterators have nothing to point to
      inner = dummy.begin(); // therefore we create an empty array 'dummy'
      inner_end = dummy.end(); // which inner iterators could point to.
    }
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

template <typename T>
class vector_2d {
  std::vector<T>::iterator outer, outer_end; // Outer iterators
  std::vector<T>::iterator inner, inner_end; // Inner iterators
  std::vector<T> dummy;

  public:
  vector_2d(std::vector<T> vector) {
    outer = vector.begin();
    outer_end = vector.end();
    if (outer != outer_end) {
      inner = outer->begin();
      inner_end = outer->end();
    } else { // If vector is empty, then the inner iterators have nothing to point to
      inner = dummy.begin(); // therefore we create an empty array 'dummy'
      inner_end = dummy.end(); // which inner iterators could point to.
    }
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

#endif