main: main.o matriz.o rede_neural.o read_iris.o
	gcc -o main main.o matriz.o rede_neural.o read_iris.o -lm

O3:
	gcc -O3 -o main main.o matriz.o rede_neural.o read_iris.o -lm

matriz.o: matriz.c matriz.h
	gcc -c matriz.c

main.o: main.c matriz.h
	gcc -c main.c

rede_neural.o: rede_neural.c rede_neural.h
	gcc -c rede_neural.c

read_iris.o: read_iris.c read_iris.h
	gcc -c read_iris.c

clean:
	rm -f *.o main

run: main
	clear
	./main
