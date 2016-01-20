#include "node.h"

#ifndef LINK_H
#define LINK_H

class LinkedList {
  private:
    Node * head;
  public:
    LinkedList () {
      head = NULL;
    }
    ~LinkedList () {
      delete head;
    }
   /* 
    @method {append} - Adds the data to the list.
   */
    void append (int data) {
      Node* link = new Node (data);
      // The link node becomes the previous node.
      link->setNext(head);
      // The head node becomes the next node.
      head = link;
    }
   /* 
    @method {remove} - Removes the top node.
   */
    void remove () {
      Node *next = head->getNext();
      head = next;
    }
   /* 
    @method {print} - Prints the data in the list.
   */
    void print () {
      // Get the current node.
      Node* current = this->head;
      // Loop through the list while it's not null.
      while(current != NULL) {
        // Print the current node.
        current->print();
        // Get the next node.
        auto next = current->getNext();
        // Set the next to the current.
        current = next;
      }
    }
   /* 
    @method {isEmpty} - Determines whether the list is empty.
    @return {bool}
   */
    bool isEmpty () {
      return head == NULL;
    }
};

#endif