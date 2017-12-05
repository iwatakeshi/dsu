#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
  if (argc < 2) {
    printf("Usage: p1-gomp.o [nthreads]\n");
    return 0;
  }
  int i, id = 0, threads = atoi(argv[1]);
  int total = 0;

  int* array = (int*)malloc(sizeof(int) * (threads + 1));
  srand(time(NULL));
  array[0] = 0;

  for (int i = 1; i < threads + 1; i++) {
    array[i] = rand() % (threads + 1 - 1) + 1;
  }

  printf("array: [ ");
  for (int i = 0; i < threads + 1; i++) {
    printf("%d, ", array[i]);
  }
  printf("]\n");

printf("apply: ");
#pragma omp parallel private(id) shared(total) num_threads(threads)
  {
    id = omp_get_thread_num() + 1;
    printf("%c %d ", (!((id) % 2)) ? '+' : '-', array[id]);
#pragma omp critical
    total += (!((id) % 2)) ? array[id] : -(array[id]);
  }

  printf("\ntotal: %d\n", total);
  free(array);
  return 0;
}