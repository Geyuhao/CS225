CC = g++
CFLAGS = -Wall -g
LDFLAGS = -lm

all: clean B_tree.o Btree_main.o Btree

B_tree.o: B_tree.h
	${CC} ${CFLAGS} -c B_tree.cpp
Btree_main.o: B_tree.h
	${CC} ${CFLAGS} -c Btree_main.cpp
Btree: Btree_main.o
	${CC} ${CFLAGS} Btree_main.o ${LDFLAGS} -o Btree
clean:
	rm -rf *.o
	rm -rf Btree