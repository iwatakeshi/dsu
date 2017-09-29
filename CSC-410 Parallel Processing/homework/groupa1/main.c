#include "matrix.h"
#include <stdio.h>

int main() {
  int n = 5;
  int** A = mallocm(n, n);
  int** B = mallocm(n, n);
  zerom(A, n, n);
  printf("A\n");
  A[1][1] = 2;
  printm(A, n, n);

  copym(A, B, n, n);
  printf("B\n");
  B[0][0] = 1;
  printm(B, n, n);
  freem(A, n);
  freem(B, n);
  return 0;
}