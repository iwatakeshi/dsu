#include "link.h"
#include <stdexcept>
/* Constructors and Destructors */

LinkedList::LinkedList() { head = NULL; }

LinkedList::~LinkedList() { delete head; }

/* Operators */
Node* LinkedList::operator() (int index) {
  // Base case
  if (isEmpty()) std::cout << "Info: The list is empty." << std::endl;
  else if (index < 0 || index >= size()) throw std::out_of_range("Error: Index out of bounds.");
  else {
    auto current = head;
    int count = 0;
    while (current != NULL) {
      if (count++ == index) {
        return current;
      }
      current = current->getNext();
    }
  }
  return NULL;
}

int LinkedList::operator[] (const int index) {
 if (index < 0 || index >= size() || isEmpty()) throw std::out_of_range("Error: Index out of bounds.");
  else {
    return (*this)(index)->getData();
  }
  return -1;
}

/* Public Methods */

void LinkedList::insert(int data, int index) {
  // Base case
  if (isEmpty()) {
    std::cout << "Info: The list is empty. Inserting data at index 0." << std::endl;
    append(data);
  }
  else if (index < 0 || index >= size()) throw std::out_of_range("Error: Index out of bounds.");
  else {
    auto current = head;
    while (current->getNext() && --index) {
      current = current->getNext();
    }
    auto next = new Node(data);
    next->setNext(current->getNext());
    current->setNext(next);
  }
}

void LinkedList::append(int data) {
  if (isEmpty()) head = new Node(data);
  else {
    auto current = head;
    auto next = new Node(data);
    while (current->getNext()) current = current->getNext();
    current->setNext(next);
  }
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
  else if (index < 0 || index >= size()) throw std::out_of_range("Error: Index out of bounds.");
  else if (size() == 0) remove();
  else {
    auto current = head;
    while (current->getNext() && --index) {
      current = current->getNext();
    }
    // The next contains the unwanted node
    auto next = current->getNext();
    // Set the next to the one following after the next
    current->setNext(next->getNext());
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

int LinkedList::size() const {
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