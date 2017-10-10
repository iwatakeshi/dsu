all: random hw1 h3

random: random.cpp
	g++ -g -std=c++11 -g random.cpp -o random.o

hw1: hw1-mergesort hw1-bubblesort

hw3: hw3-fibonacci

hw1-mergesort: hw1-mergesort.cpp
	g++ -g -std=c++11 hw1-mergesort.cpp -o hw1-mergesort.o

hw1-bubblesort: hw1-bubblesort.cpp
	g++ -g -std=c++11 hw1-bubblesort.cpp -o hw1-bubblesort.o

hw3-fibonacci: hw3-fibonacci.cpp
	g++ -g -std=c++14 -I ./boost_1_65_1 hw3-fibonacci.cpp -O2 -o hw3-fibonacci.o

hw5-zero-triplet: hw5-zero-triplet.cpp
	g++ -g -std=c++11 hw5-zero-triplet.cpp -o hw5-zero-triplet.o

clean:
	rm -f ./*.o
	rm -f -r ./*.dSYM
