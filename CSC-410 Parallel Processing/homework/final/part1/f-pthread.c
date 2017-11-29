#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct tdata {
  pthread_t tid;
  int id;
};

void* entry(void* param) {
  struct tdata* td = param;
  printf("hi from pid: %d\n", td->id);
  sleep(1);
  pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
  int threads = argc == 2 ? atoi(argv[argc - 1]) : 4;

  struct tdata td[threads];
  void* status;

  for (int i = 0; i < threads; i++) {
    td[i] = (struct tdata){ .id = i };
    pthread_create(&td[i].tid, NULL, entry, &td[i]);
  }

  for (int i = 0; i < threads; i++) {
    pthread_join(td[i].tid, &status);
  }

  return 0;
}