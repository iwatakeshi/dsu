all: random hw1 hw2

random: random.cpp
	g++ -g -std=c++11 -g random.cpp -o random.o

hw1: hw1-mergesort hw1-bubblesort

hw2: hw2-fibonacci

hw1-mergesort: hw1-mergesort.cpp
	g++ -g -std=c++11 -g hw1-mergesort.cpp -o hw1-mergesort.o

hw1-bubblesort: hw1-bubblesort.cpp
	g++ -g -std=c++11 -g hw1-bubblesort.cpp -o hw1-bubblesort.o

hw2-fibonacci: hw2-fibonacci.cpp
	g++ -g -std=c++11 -g hw2-fibonacci.cpp -o hw2-fibonacci.o


clean:
	rm -f ./*.o
	rm -f -r ./*.dSYM
