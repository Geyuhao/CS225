CC = g++
CFLAGS = -Wall -g
LDFLAGS = -lm

all: clean 0_main_program.o 1_read_file_func.o 2_fibo_heap.o 3_appointment1.o 4_report.o 5_helpmain.o program 

1_read_file_func.o: 1_read_file.h
	${CC} ${CFLAGS} -c 1_read_file_func.cpp
2_fibo_heap.o: 2_fibo_heap.h
	${CC} ${CFLAGS} -c 2_fibo_heap.cpp
3_appointment1.o: 3_appoint.h
	${CC} ${CFLAGS} -c 3_appointment1.cpp
4_report.o: 4_report.h
	${CC} ${CFLAGS} -c 4_report.cpp
5_helpmain.o: 5_helpmain.h
	${CC} ${CFLAGS} -c 5_helpmain.cpp
0_main_program.o: 5_helpmain.h
	${CC} ${CFLAGS} -c 0_main_program.cpp
program : 0_main_program.o
	${CC} ${CFLAGS} 0_main_program.o ${LDFLAGS} -o program
clean:
	rm -rf *.o
	rm -rf program