#include "link.h"

/* Constructors and Destructors */

LinkedList::LinkedList() { head = NULL; }

LinkedList::~LinkedList() { delete head; }

/* Operators */
Node* LinkedList::operator() (int index) {
  // Base case
  if (index >= 0) {
    int count = 0;
    Node* current = head;
    // Make sure we are within range
    while (count < size()) {
      // Check if we have reached the desired index
      if (count == index) break;
      else {
        count++;
        // Get the next node in the list
        auto next = current->getNext();
        // Check if next is null
        if (next == NULL) break;
        // Move forward
        else current = next;
      }
    }
    return current;
  }
  else {
    std::cout << "Error: Index out of bounds." << std::endl;
    return NULL;
  }
}

int LinkedList::operator[] (int index) {
  return (*this)(index)->getData();
}

/* Public Methods */

void LinkedList::insert(int data, int index) {
  // Base case
  if (isEmpty()) {
    std::cout << "Info: The list is empty. Inserting data at index 0." << std::endl;
    append(data);
  }
  else if (index < 0) std::cout << "Error: Index out of bounds." << std::endl;
  else {
    auto current = head;
    Node* previous = NULL;
    for (int count = 0; count < size(); count++) {
      if (index == count) {
        if (previous == NULL) {
          head = head->getNext();
        }
        else {
          // Create a new node
          auto next = new Node(data);
          // [next]->[current]
          next->setNext(current);
          // [previous] -> [next] -> [current->next]
          previous->setNext(next);
        }
      }
      else {
        // Move forward
        previous = current;
        current = current->getNext();
      }
    }
  }
}

void LinkedList::append(int data) {
  auto current = new Node(data);
  // The link node becomes the previous node.
  current->setNext(head);
  // The head node becomes the next node.
  head = current;
}

void LinkedList::remove() {
  if (isEmpty()) std::cout << "Info: The list is empty." << std::endl;
  else {
    auto current = head;
    head = head->getNext();
    delete current;
  }
}

void LinkedList::remove(int index) {
  // Base case
  if (isEmpty()) std::cout << "Info: The list is empty." << std::endl;
  else if (index < 0) std::cout << "Error: Index out of bounds." << std::endl;
  else if (size() == 0) remove();
  else {
    auto current = head;
    Node* previous = NULL;
    for (int count = 0; count < size(); count++) {
      if (index == count) {
        if (previous == NULL)
          head = head->getNext();
        else previous->setNext(current->getNext());
      }
      else {
        previous = current;
        current = current->getNext();
      }
    }
  }
}

void LinkedList::clear() {
  while (head != NULL) {
    auto current = head;
    head = head->getNext();
    delete current;
  }
}

void LinkedList::print() {
  if (isEmpty()) std::cout << "Info: The list is empty." << std::endl;
  else
    for (int count = 0; count < size(); count++) {
      (*this)(count)->print(count);
    }

  std::cout << std::endl;
}

int LinkedList::size() {
  int count = 0;
  auto current = head;
  while (current != NULL) {
    count++;
    auto next = current->getNext();
    current = next;
  }
  return count;
}

bool LinkedList::isEmpty() {
  return head == NULL;
}