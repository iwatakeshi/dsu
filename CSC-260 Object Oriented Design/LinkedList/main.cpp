#include "link.h"
int main () {
  LinkedList * list = new LinkedList();
  list->append(2);
  list->append(3);
  list->append(5);
  list->print();


  list->remove();
  list->print();

  list->append(10);
  list->append(22);
  list->print();

  list->remove(2);
  list->print();

  list->insert(100, 3);
  list->print();

  list->clear();
  list->print();
  return 0;
}