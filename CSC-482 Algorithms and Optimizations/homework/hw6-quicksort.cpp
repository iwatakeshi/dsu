#include "commander.h"
#include <functional>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

void quicksort(int*, int, int, std::function<int(int*, int, int)>);
int split(int*, int, int);
int splitrand(int*, int, int);
void printv(std::vector<int>);

int main(int argc, char* argv[]) {

  int option = 0;
  bool silent = false, random = false;
  char* filename;
  std::vector<int> S = { 2, 4, 1, 7, 29, 3, 54, 5 };

  cmd_opt_value();
  cmd_opt("-s", "--silent", false);
  cmd_opt("-r", "--random", false);

  while ((option = cmd_parse(argc, argv)) != -1) {
    switch (option) {
    case 1:
      filename = argv[cmd_val_index()];
      break;
    case 2:
      silent = true;
      break;
    case 3:
      random = true;
      break;
    default:
      break;
    }
  }

  if (random) {
    if (!silent) printf("Running QuickSort (Random)\n");
    quicksort(&S[0], 0, S.size() - 1, splitrand);
  } else {
    if (!silent) printf("Running QuickSort (Random)\n");
    quicksort(&S[0], 0, S.size() - 1, split);
  }

  if (!silent) printv(S);

  return cmd_free();
}

void quicksort(int* S, int a, int b, std::function<int(int* S, int a, int b)> splitter) {
  if (a >= b) return;
  int index = splitter(S, a, b);
  quicksort(S, a, index - 1, splitter);
  quicksort(S, index + 1, b, splitter);
}

int split(int* S, int a, int b) {
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

int splitrand(int* S, int a, int b) {
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

void printv(std::vector<int> S) {
  printf("[ ");
  for (auto a : S) {
    printf("%d ", a);
  }
  printf("]\n");
}