#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string.h>

int zerotriplet(int * A, int n) {
  int count = 0;
  for(int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      for (int k = j + 1; k < n; k++) {
        if ((A[i] + A[j] + A[k]) == 0) count++;
      }
    }
  }
  return count;
}

/*
  https://en.wikipedia.org/wiki/3SUM 
*/
int zerotriplet_improved(int * A, int n) {
  int count = 0;
  for(int i = 0; i < n - 2; i++) {
    auto a = A[i];
    auto start = i + 1;
    auto end = n - 1;
    while (start < end) {
      auto b = A[start];
      auto c = A[end];
      if (a + b + c == 0) {
        count++;
        if (b == A[start + 1]) start++;
        else end--;
      } else if (a + b + c > 0) end--;
      else start++;
    }
  }
  return count;
}

std::vector<int> readfile(const std::string& filename){
    std::ifstream source;
    source.open(filename);
    std::vector<int> numbers;
    std::string line;
    while (std::getline(source, line)) {
        std::stringstream iss(line);
        int number;
        while(iss >> number) numbers.push_back(number);
    }
    return numbers;
}

int main(int argc, char * argv[]) {
  if (argc == 3) {
    if (strcmp(argv[1], "-n") || strcmp(argv[1], "-naive")) {
      std::vector<int> v = readfile(argv[2]);
      std::cout << zerotriplet(&v[0], v.size()) << std::endl;
    } else if (strcmp(argv[1], "-i") || strcmp(argv[1], "improved")) {
      std::vector<int> v = readfile(argv[2]);
      std::sort(v.begin(), v.end());
      std::cout << zerotriplet_improved(&v[0], v.size()) << std::endl;
    }
  }
  return 0;
}