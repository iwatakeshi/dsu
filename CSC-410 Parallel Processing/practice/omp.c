#include <omp.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
  int N = 10, P = 3;
  int i, tid;
  omp_set_num_threads(P);
#pragma omp parallel for private(tid)
  for (i = 1; i <= N; ++i)
  {
    tid = omp_get_thread_num();
    printf("%2d by %3d\n", i, tid);
  }

  return 0;
}