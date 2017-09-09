#include <iostream>
#include <string>
#include <algorithm>

void mergesort(std::string numbers);

int main(int argc, char **argv) {
  std::string input;
  while (std::getline(std::cin, input)) {
    std::cout << input;
  }
  mergesort(input);
    return 0;
}
// https://en.wikipedia.org/wiki/Bubble_sort#Pseudocode_implementation
void mergesort(std::string input) {
  int n = input.length();
  bool swapped = false;
  do {
    swapped = false;
    for (int i = 1; i < n - 1; i++) {
      if (input[i - 1] > input[i]) {
        std::swap(input[i - 1], input[i]);
        swapped = true;
      }
    }
  } while(!swapped);
}