#include "node.h"

#ifndef LINK_H
#define LINK_H

class LinkedList {
  private:
    Node * head;
  public:
    LinkedList();
    ~LinkedList();
    Node* operator() (int index);

    int& operator[] (const int index);

    void insert(int data, int index);
   /* 
    @method {append} - Adds the data to the end of the list.
   */
   void append(int data);
   /* 
    @method {remove} - Removes the top node.
   */
   void remove();
   /*
    @method {remove} - Removes the node.
    @param {index: int} - The index of the node to remove.
   */
   void remove(int index);
   /*
    @method {clear} - Removes all nodes in the list.
   */
   void clear();
   /* 
    @method {print} - Prints the data in the list.
   */
   void print();
    /*
     @method {size} - Returns the size of the list.
     @return {int}
    */
   int size() const;
   /* 
    @method {isEmpty} - Determines whether the list is empty.
    @return {bool}
   */
   bool isEmpty();
};

#endif Link_H