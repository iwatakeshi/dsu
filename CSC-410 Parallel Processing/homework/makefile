
a1: ./a1/match.c ./a1/match.o
	gcc -g ./a1/match.c -o ./a1/match.o

a2: ./a2/matrix.c ./a2/matrix.o
	gcc -g -pthread ./a2/matrix.c -o ./a2/matrix.o

t1: ./t1/t1.c ./t1/t1.o
	gcc -g -lpthread -o ./t1/t1.o ./t1/t1.c


clean:
	rm -f ./**/*.o
