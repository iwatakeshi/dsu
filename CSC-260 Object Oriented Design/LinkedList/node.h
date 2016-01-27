#include <iostream>

#ifndef NODE_H
#define NODE_H

class Node {
  private:
    /* Stores the data. */
    int data;
    /* Stores the next node. */
    Node* next;
  public:
    Node () {
      data = 0;
      next = NULL;
    }
    Node (int data) {
      this->data = data;
      next = NULL;
    }
    /* Sets the data. */
      void setData (int data) {
        this->data = data;
      }
    /* Sets the next node. */
      void setNext(Node* node) {
        next = node;
      }
    /* Returns the data. */
      int getData () {
        return this->data;
      }
    /* Returns the next node. */
    Node* getNext () {
      return next;
    }
    /* Prints the data in the node. */
    void print () {
      std::cout << "Data: " << data << std::endl;
    }
    /* Prints the data in the node with an index. */
    void print (int index) {
      std::cout << "Data: " << data << " at index: " << index << std::endl;
    }
};

#endif