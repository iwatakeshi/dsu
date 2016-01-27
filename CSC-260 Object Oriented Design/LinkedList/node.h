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
    /* @constructor {Node} */
    Node () {
      data = 0;
      next = NULL;
    }
    /* 
      @constructor {Node}
      @param {data: int} - The data stored as an integer.
    */
    Node (int data) {
      this->data = data;
      next = NULL;
    }
    /* 
      @method {setData} - Sets the data.
      @param {data: int} - The data stored as an integer.
    */
      void setData (int data) {
        this->data = data;
      }
    /* 
      @method {setNext} - Sets the next node.
      @param {node: Node*} - The address to the next node.
    */
      void setNext(Node* node) {
        next = node;
      }
    /* 
      @method {getData} - Returns the data.
      @return {int}
    */
      int getData () {
        return this->data;
      }
    /* 
      @method {getNext} - Returns the next node.
      @return {Node*}
    */
    Node* getNext () {
      return next;
    }
    /* 
      @method {print} - Prints the data in the node.
    */
    void print () {
      std::cout << "Data: " << data << std::endl;
    }
    /* 
      @method {print} - Prints the data in the node with an index.
      @param {index: int}
    */
    void print (int index) {
      std::cout << "Data: " << data << " at index: " << index << std::endl;
    }
};

#endif