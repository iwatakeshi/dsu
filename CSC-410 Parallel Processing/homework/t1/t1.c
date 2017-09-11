// CSC 410
// Starting sample file:  Wed 9/6 

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

struct tdata {
	pthread_t tid;
	int id;
	int number;
};

/* Credit: "Algorithms" by S. Dasgupta */
int fib(int n) {
  int f[n + 1];
  f[0] = 0; f[1] = 1;
  for (int i = 2; i <= n; i++) {
		f[i] = f[i - 1] + f[i - 2];
  }
  return f[n];
}

int sum(int n) {
	int total = 0, i = 0;
	while (i <= n) { total = total + i; i++; }
	return total;
}

void *entry( void *param) {
	struct tdata *td = param;
	 if (td->id % 2 == 0) 
	 	td->number = sum(td->id);
	 else td->number = fib(td->id);
	pthread_exit(NULL);	
}

int main() {
	struct tdata td[8];
	int total = 0;
	void *status;

	for(int i = 0; i < 8; i++) {
		td[i] = (struct tdata) { .number = 0, .id = i };
		pthread_create(&td[i].tid, NULL, entry, &td[i]);
	}

	for(int i = 0; i < 8; i++) {
		pthread_join(td[i].tid, &status);
		total += td[i].number;
		printf("thread[%d]: %d\n", i, td[i].number);
	}

	printf("main: %d\n", total);
	
	return 0;
}