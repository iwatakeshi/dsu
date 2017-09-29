
default: main

matrix_zip:
	curl -LOk https://github.com/iwatakeshi/matrix.h/archive/master.zip

matrix: matrix_zip
	unzip master.zip
	cp "matrix.h-master/matrix.c" .
	cp "matrix.h-master/matrix.h" .

main: matrix
	gcc -g main.c matrix.c

clean:
	rm -f master.zip matrix.c matrix.h
	rm -r -f matrix.h-master