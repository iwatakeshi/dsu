#include <iostream>
#include <string.h>
#include <algorithm>
#include <sstream>
#include <vector>

void sort(int array[], int count);
void swap(int * a, int * b);
int comparisons = 0;

int main(int argc, char **argv) {
  std::string input;
  std::vector<int> integers;
  while (std::getline(std::cin, input)) {
    std::stringstream inputstream(input);
    int n;
    while (inputstream >> n) {
      integers.push_back(n);
    }
  }
  sort(&integers[0], integers.size());
  if (argc > 1 && (strcmp(argv[1], "-s") || strcmp(argv[1], "--stat"))) {
    std::cout << "comparisons: "<< comparisons << std::endl;  
  }
  int columns = 0;
  for (auto i = integers.begin(); i != integers.end(); ++i) {
    std::cout << *i << ' ';
    columns++;
    if (columns == 5) {
      std::cout << std::endl;
      columns = 0;
    }
  }
  return 0;
}

// https://en.wikipedia.org/wiki/Bubble_sort#Pseudocode_implementation
void sort(int array[], int count) {
    for (int i = 0; i < count - 1; i++) {
      for (int j = 0; j < count - i - 1; j++) {
        if (array[j] > array[j + 1]) {
          swap(&array[j], &array[j + 1]);
          comparisons++;
        }
      }
    }
}

void swap(int * a, int * b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}
