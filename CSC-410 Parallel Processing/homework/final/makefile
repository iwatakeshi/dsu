part1: part1-f-pthread part1-f-omp part1-g-omp part1-h-pthread

part1-f-pthread:
	gcc -g -pthread ./part1/f-pthread.c -o "p1-fpthread.o"

part1-f-omp: ./part1/f-omp.c
	gcc -g -fopenmp ./part1/f-omp.c -o "p1-fomp.o"

# part1-g-pthread: ./part1/g-pthread.c
# 	gcc -g -pthread ./part1/g-pthread.c -o "p1-gpthread.o"

part1-g-omp: ./part1/g-omp.c
	gcc -g -fopenmp ./part1/g-omp.c -o "p1-gomp.o"

# part1-h-omp: ./part1/h-omp.c
# 	gcc -g -fopenmp ./part1/h-omp.c -o "p1-homp.o"

part1-h-pthread: ./part1/h-pthread.c
	gcc -g -pthread ./part1/h-pthread.c -o "p1-hpthread.o"

clean:
	rm -f ./**/*.o