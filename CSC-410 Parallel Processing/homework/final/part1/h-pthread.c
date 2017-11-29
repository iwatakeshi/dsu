#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct tdata {
  pthread_t tid;
  int id;
  int n;
  int s;
  int threads;
  int result;
};

int* array;
void* search(void* param) {
  struct tdata* td = param;
  int threads = td->threads;
  int n = td->n;
  int s = td->s;
  td->result = 0;
  int steps = (int)(n / threads);
  printf("id: %d, search range (%d, %d)\n", td->id, td->id * steps, (td->id + 1) * steps);
  for (int i = td->id * steps; i < (td->id + 1) * steps; i++) {
    if (array[i] == s) {
      td->result++;
    }
  }
  pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
  int n = 30, s = 2;
  int threads = 2;
  int total = 0;

  struct tdata td[threads];
  void* status;

  printf("enter array size: ");
  scanf("%d", &n);

  printf("enter thread count: ");
  scanf("%d", &threads);

  // Allocate memory
  array = (int*)malloc(sizeof(int) * n);

  // Fill array with random numbers
  for (int i = 0; i < n; i++) {
    array[i] = 0 + rand() % (100 + 1 - 0);
  }

  // Print array
  printf("array: [ \n");
  for (int i = 0; i < n; i++) {
    printf("%d, ", array[i]);
    if ((i + 1) % 5 == 0) printf("\n");
  }
  printf("]\n");

  printf("enter number to search: ");
  scanf("%d", &s);
  printf("\n");

  // Create threads
  for (int i = 0; i < threads; i++) {
    td[i] = (struct tdata){ .id = i, .n = n, .s = s, .threads = threads };
    pthread_create(&td[i].tid, NULL, search, &td[i]);
  }

  // Join threads
  for (int i = 0; i < threads; i++) {
    pthread_join(td[i].tid, &status);
  }

  printf("\n");

  // Calculate the total count
  for (int i = 0; i < threads; i++) {
    printf("id: %d, count: %d\n", td[i].id, td[i].result);
    total += td[i].result;
  }

  printf("found '%d' %d time(s).\n", s, total);
  // Free memory
  free(array);
  return 0;
}