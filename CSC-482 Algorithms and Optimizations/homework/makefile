all: random hw1 hw3 hw5 hw6 hw7 hw8

# random: random.cpp
# 	g++ -g -std=c++11 -g random.cpp -o random.o

gen: numgen.cpp
	g++ -g -Wno-write-strings -I ./boost_1_65_1 -std=c++14 numgen.cpp -o numgen.o

hw1: hw1-mergesort hw1-bubblesort
hw3: hw3-fibonacci
hw5: hw5-zero-triplet
hw6: hw6-quicksort
hw7: hw7-tsp
hw8: hw8-dtsp

hw1-mergesort: hw1-mergesort.cpp
	g++ -g -std=c++11 hw1-mergesort.cpp -o hw1-mergesort.o

hw1-bubblesort: hw1-bubblesort.cpp
	g++ -g -std=c++11 hw1-bubblesort.cpp -o hw1-bubblesort.o

hw3-fibonacci: hw3-fibonacci.cpp
	g++ -g -std=c++14 -I ./boost_1_65_1 hw3-fibonacci.cpp -O2 -o hw3-fibonacci.o

hw5-zero-triplet: hw5-zero-triplet.cpp
	g++ -g -std=c++11 -I ./boost_1_65_1 hw5-zero-triplet.cpp -o hw5-zero-triplet.o

hw6-quicksort: hw6-quicksort.cpp
	g++ -g -std=c++14 -Wno-write-strings -I ./boost_1_65_1 hw6-quicksort.cpp -o hw6-quicksort.o -lboost_timer -lboost_system

hw7-tsp: hw7-tsp.cpp
	g++ -g -std=c++14 -Wno-write-strings -I ./boost_1_65_1 hw7-tsp.cpp -o hw7-tsp.o -lboost_timer -lboost_system

hw8-dtsp: hw8-dtsp.cpp
	g++ -g -std=c++14 -Wno-write-strings -I ./boost_1_65_1 hw8-dtsp.cpp -o hw8-dtsp.o -lboost_timer -lboost_system

clean:
	rm -f ./*.o
	rm -f -r ./*.dSYM
