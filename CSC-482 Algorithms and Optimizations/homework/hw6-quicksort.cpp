#include "commander.h"
#include <boost/chrono.hpp>
#include <boost/timer/timer.hpp>
#include <cmath>
#include <fstream>
#include <functional>
#include <iostream>
#include <numeric>
#include <sstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <random>

// typedef long long long long;
std::random_device rd;
std::mt19937 gen(rd());

void quicksort(std::vector<long long>&, long long, long long);
void quicksort_rand(std::vector<long long>&, long long, long long);
long long split(std::vector<long long>&, long long, long long);
long long split_rand(std::vector<long long>&, long long, long long);
void printv(std::vector<long long>);

int main(int argc, char* argv[]) {

  int option = 0;
  bool silent = false, random = false, readfile = false, benchmark = false;
  std::ifstream file;

  cmd_opt_value();
  cmd_opt("-s", "--silent", false);
  cmd_opt("-r", "--random", false);
  cmd_opt("-b", "--benchmark", false);
  while ((option = cmd_parse(argc, argv)) != -1) {
    switch (option) {
    case 1:
      readfile = true;
      file.open(argv[cmd_val_index()], std::ifstream::in);
      break;
    case 2:
      silent = true;
      break;
    case 3:
      random = true;
      break;
    case 4:
      benchmark = true;
      break;
    case 5:
      break;
    default:
      break;
    }
  }

  std::vector<long long> S;
  std::string input;
  long long length = 0;
  while (std::getline(readfile ? file : std::cin, input)) {
    std::stringstream line(input);
    long long n;
    while (line >> n) {
      S.push_back(n);
      length++;
    }
  }

  if (!silent) {
    printf("Input: \n");
    printv(S);
  }
  if (random) {
    if (!silent) printf("Running QuickSort (Random)\n");
    boost::timer::auto_cpu_timer timer("%w\n");
    quicksort_rand(S, 0, length - 1);
  } else {
    if (!silent) printf("Running QuickSort\n");
    boost::timer::auto_cpu_timer timer("%w\n");
    quicksort(S, 0, length - 1);
  }

  if (!silent) printv(S);

  return cmd_free();
}

/* Quicksort functions */

void quicksort(std::vector<long long>& S, long long a, long long b) {
  if (a >= b) return;
  long long p = split(S, a, b);
  quicksort(S, a, p - 1);
  quicksort(S, p + 1, b);
}

void quicksort_rand(std::vector<long long>& S, long long a, long long b) {
  if (a >= b) return;
  long long p = split_rand(S, a, b);
  quicksort_rand(S, a, p - 1);
  quicksort_rand(S, p + 1, b);
}

/* Split functions */

long long split(std::vector<long long>& S, long long a, long long b) {
  long long p = S[b];
  long long l = a;
  long long r = b - 1;
  while (l <= r) {
    while (l <= r && S[l] <= p)
      l++;
    while (r >= l && S[r] >= p)
      r--;
    if (l < r) std::swap(S[l], S[r]);
  }
  std::swap(S[l], S[b]);
  return l;
}

long long split_rand(std::vector<long long>& S, long long a, long long b) {
  std::uniform_int_distribution<long long> dist(a, b);
  std::swap(S[dist(gen)], S[b]);
  return split(S, a, b);
}

void printv(std::vector<long long> S) {
  printf("[ ");
  for (auto a : S) {
    printf("%lld ", a);
  }
  printf("]\n");
}
