CC = g++
CFLAGS = -Wall -g
LDFLAGS = -lm

all: clean bptree.o bp_main.o bptree

bptree.o: bptree.h
	${CC} ${CFLAGS} -c bptree.cpp
bp_main.o: bptree.h
	${CC} ${CFLAGS} -c bp_main.cpp
bptree: bp_main.o
	${CC} ${CFLAGS} bp_main.o ${LDFLAGS} -o bptree
clean:
	rm -rf *.o
	rm -rf bptree