#include <ctime>
#include <stdio.h>
#include "tsp.hpp"

int main() {
  srand(time(0));
  TSP tsp(4, 1, 10);
  tsp.graph.print();
  printf("\n");
  TSP::print(tsp.dynamic());
  TSP::print(tsp.brute());
  return 0;
}