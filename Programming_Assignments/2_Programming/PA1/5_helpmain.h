#ifndef HELP_H
#define HELP_H

#include "4_report.cpp"

int search_people(int id, Fheap<int> &fib, queue<Appoint_People*> &waiting, queue<Appoint_People*> &treating,
                   queue<Appoint_People*> &treated, Withdraw &withdraw);
void fib_people(Fheap<int> &fib, int id, int operate, Withdraw &withdraw);
void show_info(Appoint_People* person);


#endif