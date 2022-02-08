CC=gcc
CFLAGS= -std=c99 -Wall

wordleSolver: main.o list.o letterWeightCalc.o
	$(CC) $(CFLAGS) -o wordleSolver main.o list.o letterWeightCalc.o

main.o : main.c
	$(CC) $(CFLAGS) -c main.c

list.o : list.c
	$(CC) $(CFLAGS) -c list.c

letterWeightCalc.o : letterWeightCalc.c
	$(CC) $(CFLAGS) -c letterWeightCalc.c