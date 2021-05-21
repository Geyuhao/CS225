#ifndef HELP_H
#define HELP_H

#include "6_distance.cpp"

int search_people(int id, Fheap<int> &fib, queue<Appoint_People*> &waiting, queue<Appoint_People*> &treating,
                   queue<Appoint_People*> &treated, Withdraw &withdraw);
void fib_people(Fheap<int> &fib, int id, int operate, Withdraw &withdraw);
void show_info(Appoint_People* person);
void show_info(Person_BP* person);

void big_register(Fheap<int> &fib, CBPlusTree* &bptree, BTree<Person_BP> &mybtree, MultiSet_Chaining* hash_treatment, 
                  MultiSet_Chaining* hash_med, queue<People*> &local_q, int num_people, int day_offset);

void print_people_BP(Person_BP* person);

void Update(queue<Appoint_People*> q, CBPlusTree* &bptree, STATUS_TYPE s);

void Generate_data(CBPlusTree* &bptree, string filename);

#endif