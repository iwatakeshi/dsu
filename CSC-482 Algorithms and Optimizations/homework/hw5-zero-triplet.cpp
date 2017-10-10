#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

int zerotriplet(int * a, int n) {
  int count = 0;
  for(int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      for (int k = j + 1; k < n; k++) {
        if ((a[i] + a[j] + a[k]) == 0) count++;
      }
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
  if (argc > 1) {
    std::cout << argv[1] << std::endl;
    std::vector<int> v = readfile(argv[1]);
    zerotriplet(&v[0], v.size());
  }
  return 0;
}