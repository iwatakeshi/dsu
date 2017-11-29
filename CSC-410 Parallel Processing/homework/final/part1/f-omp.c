#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
  int id = 0, threads = argc == 2 ? atoi(argv[argc - 1]) : 4;

  omp_set_num_threads(threads);

#pragma omp parallel private(id)
  {
    id = omp_get_thread_num();
    printf("hi from pid: %d\n", id);
    sleep(1);
  }

  return 0;
}