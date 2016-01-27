#include "node.h"

#ifndef LINK_H
#define LINK_H

class LinkedList {
  private:
    Node* head;
    Node* operator() (int index);
  public:
    LinkedList();
    ~LinkedList();
    int operator[] (const int index);

    void insert(int data, int index);
    /* Adds the data to the end of the list. */
    void append(int data);
    /* Removes the data from the top */
    void remove();
    /* Removes the data at the specified index. */
    void remove(int index);
    /* Removes all data in the list. */
    void clear();
    /* Prints the data in the list. */
    void print();
    /* Returns the size of the list. */
    int size() const;
    /* Determines whether the list is empty. */
    bool isEmpty();
};

#endif