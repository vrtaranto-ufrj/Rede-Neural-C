main: main.o matriz.o rede_neural.o read_iris.o
	gcc -Wall -O3 -o main main.o matriz.o rede_neural.o read_iris.o -lm

matriz.o: matriz.c matriz.h
	gcc -Wall -O3 -c matriz.c

main.o: main.c matriz.h
	gcc -Wall -O3 -c main.c

rede_neural.o: rede_neural.c rede_neural.h
	gcc -Wall -O3 -c rede_neural.c

read_iris.o: read_iris.c read_iris.h
	gcc -Wall -O3 -c read_iris.c

clean:
	rm -f *.o main

run: main
	clear
	./main
