#include <algorithm>
#include <boost/timer.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int zerotriplet(int* A, int n) {
  int count = 0;
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      for (int k = j + 1; k < n; k++) {
        if ((A[i] + A[j] + A[k]) == 0) count++;
      }
    }
  }
  return count;
}

int zerotriplet_improved(int* A, int n) {
  int count = 0;
  for (int i = 0; i < n - 2; i++) {
    auto start = i + 1;
    auto end = n - 1;
    while (start < end) {
      if (A[i] + A[start] + A[end] == 0) {
        count++;
        if (A[start] == A[start + 1])
          start++;
        else
          end--;
      } else if (A[i] + A[start] + A[end] < 0)
        start++;
      else
        end--;
    }
  }
  return count;
}

std::vector<int> readfile(const std::string& filename) {
  std::ifstream source;
  source.open(filename);
  std::vector<int> numbers;
  std::string line;
  while (std::getline(source, line)) {
    std::stringstream iss(line);
    int number;
    while (iss >> number)
      numbers.push_back(number);
  }
  return numbers;
}

int main(int argc, char* argv[]) {
  if (argc == 3) {
    std::vector<std::string> sargv(argv, argv + argc);
    sargv.erase(sargv.begin());
    auto flag = sargv.at(0);
    std::vector<int> v = readfile(sargv.at(1));
    if (flag == "-n" || flag == "-naive") {
      boost::timer t;
      auto count = zerotriplet(&v[0], v.size());
      std::cout << count << " " << t.elapsed() << std::endl;
    } else if (flag == "-i" || flag == "-improved") {
      std::sort(v.begin(), v.end());
      boost::timer t;
      auto count = zerotriplet_improved(&v[0], v.size());
      std::cout << count << " " << t.elapsed() << std::endl;
    }
  }

  return 0;
}