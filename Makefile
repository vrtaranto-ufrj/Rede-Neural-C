matriz.o: matriz.c matriz.h
	gcc -c matriz.c

main.o: main.c matriz.h
	gcc -c main.c

main: main.o matriz.o
	gcc -o main main.o matriz.o

clean:
	rm -f *.o main

run: main
	clear
	./main
