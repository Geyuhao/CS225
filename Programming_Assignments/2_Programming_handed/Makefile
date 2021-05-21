CC = g++
CFLAGS = -Wall -g
LDFLAGS = -lm

all: clean 0_main_program.o 1_read_file_func.o 2_fibo_heap.o 3_appointment1.o 4_report.o \
	 1_relations.o 3_BPlus_node.o 3_BPlus_tree.o 4_bTree.o 5_hash.o 7_helpmain.o program

1_read_file_func.o: PA1/1_read_file.h
	${CC} ${CFLAGS} -c PA1/1_read_file_func.cpp
2_fibo_heap.o: PA1/2_fibo_heap.h
	${CC} ${CFLAGS} -c PA1/2_fibo_heap.cpp
3_appointment1.o: PA1/3_appoint.h
	${CC} ${CFLAGS} -c PA1/3_appointment1.cpp
4_report.o: PA1/4_report.h
	${CC} ${CFLAGS} -c PA1/4_report.cpp



1_relations.o: 1_relations.h
	${CC} ${CFLAGS} -c 1_relations.cpp
3_BPlus_node.o: 3_BPlus_node.h
	${CC} ${CFLAGS} -c 3_BPlus_node.cpp
3_BPlus_tree.o: 3_BPlus_tree.h
	${CC} ${CFLAGS} -c 3_BPlus_tree.cpp
4_bTree.o: 4_bTree.h
	${CC} ${CFLAGS} -c 4_btree.cpp
5_hash.o: 5_hash.h
	${CC} ${CFLAGS} -c 5_hash.cpp
7_helpmain.o: 7_helpmain.h
	${CC} ${CFLAGS} -c 7_helpmain.cpp

# Main file compile part
0_main_program.o: 7_helpmain.o
	${CC} ${CFLAGS} -c 0_main_program.cpp
program : 0_main_program.o
	${CC} ${CFLAGS} 0_main_program.o ${LDFLAGS} -o program
clean:
	rm -rf *.o
	rm -rf program