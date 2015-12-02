
# Makefile
# Leon Tabak
# CSC311 Systems Software
# 23 November 2015

all:
	gcc src/eratosthenes.c -o eratosthenes -Wall
	gcc src/schedules.c -lm -o schedules -Wall
	gcc src/treesort.c -o treesort -Wall

eratosthenes: src/eratosthenes.c
	gcc src/eratosthenes.c -o eratosthenes -Wall
schedules: src/schedules.c
	gcc src/schedules.c -lm -o schedules -Wall
treesort: src/treesort.c
	gcc src/treesort.c -o treesort -Wall
fcfs: src/fcfs.c src/priorityQueue.c src/process.c src/queue.c
	gcc src/fcfs.c -c -Wall
	gcc src/priorityQueue.c -c -Wall
	gcc src/process.c -c -Wall
	gcc src/queue.c -c -Wall
	gcc fcfs.o priorityQueue.o process.o queue.o -lm -o fcfs

clean:
	rm -f eratosthenes src/eratosthenes.c~
	rm -f schedules src/schedules.c~
	rm -f treesort src/treesort.c~
