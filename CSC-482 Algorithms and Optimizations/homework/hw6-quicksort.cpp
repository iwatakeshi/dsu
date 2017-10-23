#include "bench.h"
#include "commander.h"
#include <fstream>
#include <functional>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <chrono>

void quicksort(long long int*, int, int, std::function<int(long long int*, int, int)>);
int split(long long int*, int, int);
int splitrand(long long int*, int, int);
void printv(std::vector<long long int>);

int main(int argc, char* argv[]) {

  int option = 0;
  bool silent = false, random = false, readfile = false, benchmark = false;;
  std::vector<long long int> S;
  std::string input;
  std::ifstream file;

  cmd_opt_value();
  cmd_opt("-s", "--silent", false);
  cmd_opt("-r", "--random", false);
  cmd_opt("-b", "--benchmark", false);
  while ((option = cmd_parse(argc, argv)) != -1) {
    switch (option) {
      break;
    case 1:
      readfile = true;
      file.open(argv[cmd_val_index()], std::ifstream::in);
    case 2:
      silent = true;
      break;
    case 3:
      random = true;
      break;
    case 4:
      benchmark = true;
    default:
      break;
    }
  }

  while (std::getline(readfile ? file : std::cin, input)) {
    std::stringstream line(input);
    long long int n;
    while (line >> n) {
      printf("%lld\n", n);
      S.push_back(n);
    }
  }

  
  if (!silent) { 
    printf("Input: \n");
    printv(S);
  }
  if (random) {
    if (!silent) printf("Running QuickSort (Random)\n");
    if (S.size() > 1) {
      quicksort(&S[0], 0, S.size() - 1, splitrand);
      // if (!silent) std::cout << t << std::endl;
    }
  } else {
    if (!silent) printf("Running QuickSort\n");
    if (S.size() > 1) {
      auto start = bench::start();
      quicksort(&S[0], 0, S.size() - 1, splitrand);
      if (benchmark) std::cout << "Time(ms) : " << bench::measure(start, bench::end()) << std::endl;
    }
  }

  if (!silent) printv(S);

  return cmd_free();
}

void quicksort(long long int* S, int a, int b, std::function<int(long long int* S, int a, int b)> splitter) {
  if (a >= b) return;
  int index = splitter(S, a, b);
  quicksort(S, a, index - 1, splitter);
  quicksort(S, index + 1, b, splitter);
}

int split(long long int* S, int a, int b) {
  int pivot = S[b];
  int index = a;
  for (int i = a; i < b; i++) {
    if (S[i] <= pivot) {
      std::swap(S[i], S[index]);
      index++;
    }
  }
  std::swap(S[index], S[b]);
  return index;
}

int splitrand(long long int* S, int a, int b) {
  srand(time(NULL));
  int r = a + rand() % (b - a + 1);
  std::swap(S[r], S[b]);
  int pivot = S[b];
  int index = a;
  for (int i = a; i < b; i++) {
    if (S[i] <= pivot) {
      std::swap(S[i], S[index]);
      index++;
    }
  }
  std::swap(S[index], S[b]);
  return index;
}

void printv(std::vector<long long int> S) {
  printf("[ ");
  for (auto a : S) {
    printf("%lld ", a);
  }
  printf("]\n");
}