#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <string.h>

bool stat(char *str);
void merge(int array[], int left, int center, int right);
void sort(int array[], int left, int right);
int comparisons = 0;

int main(int argc, char **argv) {
  std::string input;
  std::vector<int> integers;
  bool show_stat = false;
  bool read_file = false;
  std::ifstream file;

  // mergesort.o (-s || --stat)
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

  sort(&integers[0], 0, integers.size());
  
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

void sort(int array[], int left, int right) {
  if (left < right) {
    int mid = (left + right) / 2;

    // sort the left half
    sort(array, left, mid);
    // sor the right half
    sort(array, mid + 1, right);
    // merge the sorted arrays
    merge(array, left, mid, right);
  }
}


void merge(int array[], int left, int mid, int right) {

  int n1 = mid - left + 1, n2 =  right - mid;
  std::vector<int> a, b;

  for (int i = 0; i < n1; i++) {
      a.push_back(array[left + i]);
    }
  for (int j = 0; j < n2; j++) {
      b.push_back(array[mid + 1 + j]);
    }

  int i = 0, j = 0, k = left;
  while (i < n1 && j < n2) {
    if (a.at(i) <= b.at(j)) {
      array[k] = a.at(i++);
      comparisons++;
    }
    else {
      array[k] = b.at(j++);
    }
    k++;
  }

  while (i < n1) { array[k++] = a.at(i++); }

  while (j < n2) { array[k++] = b.at(j++); }
}

