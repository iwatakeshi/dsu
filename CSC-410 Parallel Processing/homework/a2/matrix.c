#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct tdata {
	pthread_t tid;
	int id;
	int rows, columns;
	int threads;
	int result;
};
int **A, **B;

/* Calculate helper functions */
int add(int **M, int row, int column);
int map(int **M, int row, int column, int value);

/* Calculate functions */
void calculate_sequential(int **M, int **M2, int rows, int columns);
void *calculate(void *param);

/* Matrix helper functions */
void printm(int **M, int rows, int columns);
void zerom(int **M, int rows, int columns);
void copym(int **M, int **M2, int rows, int columns);
void freem(int **M, int rows);

int main(int argc, char* argv[]) {
	int rows = 8, columns = 8, seed = 0, generation = 1, threads = 3, high = 20;
	bool parallel = false;

	for(int i = 0; i < argc; i++) {
		if (strcmp(argv[i], "--rows") == 0 || strcmp(argv[i], "-r") == 0) {
			if (i + 1 < argc) rows = atoi(argv[i + 1]) + 2;
		} else if (strcmp(argv[i], "--columns") == 0 || strcmp(argv[i], "-c") == 0){
			if (i + 1 < argc) columns = atoi(argv[i + 1]) + 2;
		} else if (strcmp(argv[i], "--seed") == 0 || strcmp(argv[i], "-s") == 0) {
			if (i + 1 < argc) seed = atoi(argv[i + 1]);
		} else if (strcmp(argv[i], "--parallel") == 0 || strcmp(argv[i], "-p") == 0) {
			parallel = true;
		} else if (strcmp(argv[i], "--generation") == 0 || strcmp(argv[i], "-g") == 0) {
			if (i + 1 < argc) generation = atoi(argv[i + 1]);
		} else if (strcmp(argv[i], "--threads") == 0 || strcmp(argv[i], "-t") == 0) {
			if (i + 1 < argc) threads = atoi(argv[i + 1]);
		} else if (strcmp(argv[i], "--high") == 0 || strcmp(argv[i], "-h") == 0) {
			if (i + 1 < argc) high = atoi(argv[i + 1]);
		}
	}
	
	// Allocate the arrays;
	A = malloc(rows * sizeof(int *));
	B = malloc(rows * sizeof(int *));
	if(A == NULL || B == NULL) {
		fprintf(stderr, "out of memory\n");
		return -1;
	}
	for(int i = 0; i < rows; i++) {
		A[i] = malloc(columns * sizeof(int));
		B[i] = malloc(columns * sizeof(int));
		if(A[i] == NULL || B[i] == NULL) {
			fprintf(stderr, "out of memory\n");
			return -1;
		}
	}
	zerom(A, rows, columns);
	zerom(B, rows, columns);
	// Seed if necessary
	if (seed > 0) srand(seed);
	// Generate numbers for A
	for (int i = 1; i < rows - 1; i++) {
		for (int j = 1; j < columns - 1; j++) {
			A[i][j] = rand() % high;
		}
	}

	printf("  Gen: %d ---------------------\n", 0);
	printm(A, rows, columns);

	for(int count = 1; count < generation + 1; count++) {
		if (parallel) {
			struct tdata td[threads];
			void * status;

			// Create threads
		for (int i = 0; i < threads; i++)  {
			td[i] = (struct tdata) { .id = i + 1, .rows = rows - 1, .columns = columns - 1, .threads = threads };
			pthread_create(&td[i].tid, NULL, calculate, &td[i]); 
		}
			 
		 // Join threads
		 for (int i = 0; i < threads; i++) {
			 pthread_join(td[i].tid, &status);
		 }
		} else  {
			calculate_sequential(A, B, rows - 1, columns - 1);
		}

		printf("  Gen: %d ---------------------\n", count);
		printm(B, rows, columns);
		copym(B, A, rows, columns);
		zerom(B, rows, columns);
	} 

	freem(A, rows);
	freem(B, rows);
	return 0;
}

/* Calculate functions */

void calculate_sequential(int **M, int **M2, int rows, int columns) {
	for(int i = 1; i < rows; i++) {
		for (int j = 1; j < columns; j++) {
			int result = map(M, i, j, add(M, i, j));
			M2[i][j] = result;
		}
	}	
}

void *calculate(void *param) {
	struct tdata * td = param;
	int threads = td->threads;
	int rows = td->rows, cols = td->columns;
	int result = 0; int nums[threads];
	for (int i = 1; i <= threads; ++i){ nums[i] = i + 1; }
	int steps = rows / threads;
	if (threads > rows) steps = rows % threads;

	for(int i = td->id; i < rows; i += steps) {
		for(int j = 1; j < cols; j++) {
			td->result = result = map(A, i, j, add(A, i, j));
			B[i][j] = result;
		}
	}
	
	pthread_exit(NULL);
}

/* Calculate helper functions */

int add(int **M, int row, int column) {
	int sum = 0;
	for (int i = -1; i < 2; i++) {
		for(int j = -1; j < 2; j++) {
			sum += M[row + i][column + j];
		}
	}
	return sum;
}

int map(int **M, int row, int column, int value) {
	int result = value;
	if (result % 10 == 0) result = 0;
	else if(result < 50) result = A[row][column] + 3;
	else if(result > 50 && result < 150) {
		if (M[row][column] - 3 >= 0) 
			result = M[row][column] - 3;
		else result = 0;
	}
	else if (result > 150) result = 1;
	return result;
}

 /* Matrix helper functions */

void printm(int **M, int rows, int columns) {
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < columns; j++) {
			printf(" %2d", M[i][j]);
		}
		printf("\n");
	}
}

void zerom(int **M, int rows, int columns) {
	for (int i = 0; i < rows; i++) {
		for(int j = 0; j < columns; j++) {
			M[i][j] = 0;
		}
	}
}

void copym(int **M, int **M2, int rows, int columns) {
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < columns; j++) {
			M2[i][j] = M[i][j];
		}
	}
}

void freem(int **M, int rows) {
	for(int i = 0; i < rows; i++) free(M[i]);
	free(M);
}