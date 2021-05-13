/*
 * File name: 1_relation.h
 * Creat date: 2021.5.9
 * Guanshujie Fu;
 * Mainly: this file contains the necessary function and class definiton needed
 *         for relational database schema
 * 
 * 
 */



#ifndef RELATIONS_H
#define RELATIONS_H

#include <vector>
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <math.h>
#include "PA1/5_helpmain.cpp"
const int ORDER = 7;                   // B+树的阶（非根内结点的最小子树个数）
const int MINNUM_KEY = ORDER-1;        // 最小键值个数
const int MAXNUM_KEY = 2*ORDER-1;      // 最大键值个数
const int MINNUM_CHILD = MINNUM_KEY+1; // 最小子树个数
const int MAXNUM_CHILD = MAXNUM_KEY+1; // 最大子树个数
const int MINNUM_LEAF = MINNUM_KEY;    // 最小叶子结点键值个数
const int MAXNUM_LEAF = MAXNUM_KEY;    // 最大叶子结点键值个数
const int OVERFLOW_SIZE = MAXNUM_LEAF/2;	// size of the overflow block
const int BLOCK_SIZE = OVERFLOW_SIZE;

class Block;
typedef float KeyType;                 // 键类型
typedef Block* DataType;         // 值类型
enum RELATION_TYPE{PERSON, EDGE};      // three relation types
enum STATUS_TYPE{REGISTER, IN_HEAP, WAITING, TREATING, TREATED, WITHDRAW};    // five types of status a person may have
using namespace::std;

/*
 * Four relations: Person, Medical Status, Registration, Treatment
 * We combine into one relation Person_BP as there is no need to exist four relations
 * 
 */
class Person_BP
{
public:
    Person_BP(People* individual);
    // Basic information of a person
    People* people;
    int id;
    STATUS_TYPE status;     // denote the status of the person

    // Medical Status
        // no idea about this part

    // Treatment (this part contains the treatment information for the people)
    int withdraw_counter;   // initially as 14
    int treatment_type; // three types of treatment. (0, 1, 2)
    int treat_time; // time needed to treat, we set it as 1 hour for all people
    pair<int, int> app_date; // date of appointment as <month, day>
    int arrival_time;  // arrival time at the appointment date
    pair<int, int> total_wt; //total waiting time <days, hours> from register date to treated date
    Hospital *hospital_togo;

    // linked list in main_blocks
    Person_BP* next_person;
    Person_BP* previous_person;

};
// constructor for the class Person
Person_BP::Person_BP(People* individual)
{
    people = individual;
    id = individual->id_number;
    treat_time = 1;
    withdraw_counter = 14;
    hospital_togo = NULL;
}



// class Edges 
// for ex4 in PA2
class Edges
{
public:
    Edges(People* &p1, People* &p2);
    pair<People*, People*> edge_;
    int length;

    // linked list in main_block
    Edges* next_edge;
    Edges* prev_edge;
};
// constructor of class Edges
Edges::Edges(People* &p1, People* &p2)
{
    edge_.first = p1;
    edge_.second = p2;
    int len_1 = p1->address.first*p1->address.first + p2->address.first*p2->address.first;
    int len_2 = p1->address.second*p1->address.second + p2->address.second*p2->address.second;
    length = (int)sqrt(len_1 + len_2);
}



// class Block
// This is block for the use of BPtree
class Block
{
public:
    Block(Person_BP* &p, int size_ = 1);
    Block(Edges* &e, int size_);

    RELATION_TYPE type;     // denote whether it is Person or Edges
    Person_BP* Person_;     // the Person records where ID will be the label
    Edges* Edges_;          // the Edge record for ex4 where length will be the label
    // member functions 
    bool search_record(RELATION_TYPE r, KeyType key);
    bool insert_record(RELATION_TYPE r, Person_BP* &p, Edges* &e);   
    bool remove_record(RELATION_TYPE r, KeyType key);
    Block* merge_block(Block* m_block);   // merge current block with input block
    Block* split_block();   // split current block into two blocks
    int record_num(){return Records_num;}
    int remain_space(){return size-Records_num;}
private:
    int label;    // the label of the block
    int size;
    int Records_num;
};
// Constructor for class Block
Block::Block(Person_BP* &p, int size_)
{
    size = size_; Records_num = 1;
    Person_ = p; Edges_ = NULL;
    type = PERSON;
    label = p->people->id_number;
}
// Overloaded constructor for class Block
Block::Block(Edges* &e, int size_)
{
    size = size_; Records_num = 1;
    Edges_ = e; Person_ = NULL;
    type = EDGE;
    label = e->length;
}





#endif