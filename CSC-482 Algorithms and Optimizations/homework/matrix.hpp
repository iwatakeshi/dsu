#ifndef MATRIX_H
#define MATRIX_H
/*
  Author: Takeshi Iwana
  License: MIT
*/
#include <cstdlib>

/* Matrix helper functions */

void printm(int** a, unsigned int n, unsigned int m) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      printf(" %2d", a[i][j]);
    }
    printf("\n");
  }
}

void printm(long long** a, unsigned int n, unsigned int m) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      printf(" %2llu", a[i][j]);
    }
    printf("\n");
  }
}

void zerom(int** a, unsigned int n, unsigned int m) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      a[i][j] = 0;
    }
  }
}

void zerom(long long** a, unsigned int n, unsigned int m) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      a[i][j] = 0;
    }
  }
}

void randm(int** a, int n, int m, int h) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      a[i][j] = rand() % h;
    }
  }
}

void randm(long long** a, unsigned int n, int m, int l, int h) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      a[i][j] = rand() % (1 + h - l) + l;
    }
  }
}

void randm(long long** a, int n, int m, int h) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      a[i][j] = rand() % h;
    }
  }
}

void randm(int** a, unsigned int n, int m, int l, int h) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      a[i][j] = rand() % (1 + h - l) + l;
    }
  }
}

void symrandm(int ** a, int n, int m, int h) {
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      a[i][j] = rand() % h;
      a[j][i] = a[i][j];
    }
  }
}

void symrandm(long long ** a, int n, int m, int h) {
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      a[i][j] = rand() % h;
      a[j][i] = a[i][j];
    }
  }
}

void symrandm(int ** a, int n, int m, int l, int h) {
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      a[i][j] = rand() % (1 + h - l) + l;
      a[j][i] = a[i][j];
    }
  }
}

void symrandm(long long ** a, int n, int m, int l, int h) {
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      a[i][j] = rand() % (1 + h - l) + l;
      a[j][i] = a[i][j];
    }
  }
}

void copym(int** a, int** b, unsigned int n, unsigned int m) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      b[i][j] = a[i][j];
    }
  }
}

void* callocm(unsigned int n, unsigned int m, unsigned int ptr_size, unsigned int t_size) {
  void** a = (void **)calloc(n, ptr_size);
  for (int i = 0; i < m; i++) {
    a[i] = calloc(m, t_size);
  }
  return (void*)a;
}

void* mallocm(unsigned int n, unsigned int m, unsigned int ptr_size, unsigned int t_size) {
  void** a = (void **)malloc(n * ptr_size);
  for (int i = 0; i < m; i++) {
    a[i] = malloc(m * t_size);
  }
  return (void*)a;
}

void freem(int** a, unsigned int n) {
  for (int i = 0; i < n; i++) {
    free(a[i]);
  }
  free(a);
}

void freem(long long** a, unsigned int n) {
  for (int i = 0; i < n; i++) {
    free(a[i]);
  }
  free(a);
}

#endif