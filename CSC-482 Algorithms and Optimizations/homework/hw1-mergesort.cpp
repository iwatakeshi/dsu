#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <vector>

void merge(int array[], int left, int center, int right);
void sort(int array[], int left, int right);
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
  sort(&integers[0], 0, integers.size());
  if (argc > 1 && (strcmp(argv[1], "-s") || strcmp(argv[1], "--stat"))) {
    std::cout << "There were "<< comparisons << " comparisons made." << std::endl;  
  }
  // for (auto i = integers.begin(); i != integers.end(); ++i) {
  //   std::cout << *i << ' ';
  // }
  return 0;
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
  int n = left, m = mid + 1;
  
  int sorted[right - left + 1], k = 0;

  for (int i = left; i <= right; i++) {
    if (n > mid) {
      sorted[k++] = array[m++];
      comparisons++;
    } else if (m > right) {
      sorted[k++] = array[n++];
      comparisons++;
    }
    else if (array[n] < array[m]) {
      sorted[k++] = array[n++];
      comparisons++;
    } else {
      sorted[k++] = array[m++];
      comparisons++;
    }
  }
  for(int i = 0; i < k; i++) {
    array[left++] = sorted[i];
  }
}