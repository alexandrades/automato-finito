all: tp

tp: tp.o main.o
	gcc -o tp main.o tp.o
	rm -rf *.o

tp.o: src/tp.c
	gcc -c src/tp.c

main.o: src/main.c
	gcc -c src/main.c