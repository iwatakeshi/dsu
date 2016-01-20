#include "link.h"
int main () {
  LinkedList * list = new LinkedList();
  list->append(2);
  list->append(3);
  list->append(5);
  list->print();
  std::cout << std::endl;
  list->remove();
  list->print();
  return 0;
}