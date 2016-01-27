#include "link.h"
#include <iostream>
#include <exception>
using namespace std;
int main () {
  
  LinkedList list;
  list.append(0);
  list.append(1);
  list.append(2);
  list.print();

  list.remove(1);
  list.print();

  list.insert(3, 1);
  list.print();

  try {
    list.insert(12, 4);
  }
  catch (exception& e) {
    cerr << e.what() << endl;
  }
  cout << endl;

  list.clear();
  list.print();

  return 0;
}