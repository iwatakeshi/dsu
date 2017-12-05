#include <iostream>
#include <string.h>
#include <algorithm>
#include <sstream>
#include <vector>
#include <fstream>

bool stat(char *str);
void sort(int array[], int count);
void swap(int * a, int * b);
int comparisons = 0;

int main(int argc, char **argv) {
  std::string input;
  std::vector<int> integers;
  bool show_stat = false;
  bool read_file = false;
  std::ifstream file;

  // bubblesort.o (-s || --stat)
  if (argc > 1 && stat(argv[1])) {
    show_stat = true;
    if (argc > 2) {
      read_file = true;
      file.open(argv[2],std::ifstream::in);
    }
  } else if (argc > 1) {
    read_file = true;
    file.open(argv[1], std::ifstream::in);
    if (argc > 2 && stat(argv[2])) {
      show_stat = true;
    }
  }

  while (std::getline(read_file ? file : std::cin, input)) {
    std::stringstream line(input);
    int n;
    while (line >> n) {
      integers.push_back(n);
    }
  }
  
  sort(&integers[0], integers.size());
  
  int columns = 0;
  
  for (auto i = integers.begin(); i != integers.end(); ++i) {
    std::cout << *i << ' ';
    columns++;
    if (columns == 5) {
      std::cout << '\n';
      columns = 0;
    }
  }

  std::cout << '\n';

  if (show_stat) {
    std::cout << "comparisons: " << comparisons << '\n';    
  }

  return 0;
}

bool stat(char *str) {
  return strcmp(str, "-s") == 0 || strcmp(str, "--stat") == 0;
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
