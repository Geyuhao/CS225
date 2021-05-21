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
#include "PA1/4_report.cpp"
const int ORDER = 7;                   // B+树的阶（非根内结点的最小子树个数）
const int MINNUM_KEY = ORDER-1;        // 最小键值个数
const int MAXNUM_KEY = 2*ORDER-1;      // 最大键值个数
const int MINNUM_CHILD = MINNUM_KEY+1; // 最小子树个数
const int MAXNUM_CHILD = MAXNUM_KEY+1; // 最大子树个数
const int MINNUM_LEAF = MINNUM_KEY;    // 最小叶子结点键值个数
const int MAXNUM_LEAF = MAXNUM_KEY;    // 最大叶子结点键值个数
const int BLOCK_SIZE = 50;	// size of the overflow block
const int OVERFLOW_SIZE = BLOCK_SIZE/2;
int DISTANCE_THETA = 20;

class Block;
class Treatment;
typedef float KeyType;                 // 键类型
typedef Block* DataType;         // 值类型
enum RELATION_TYPE{PERSON, EDGE};      // three relation types
enum STATUS_TYPE{REGISTER, IN_HEAP, WAITING, TREATING, TREATED, WITHDRAW};    // five types of status a person may have
using namespace::std;


class Treatment
{
public:
    Treatment(int t);
    // Treatment (this part contains the treatment information for the people)
    int Person_ID;      // denote who is this
    int Treatment_type; // three types of treatment. (0, 1, 2), this will work as the secondary key
    int withdraw_counter;   // initially as 14
    int treat_time; // time needed to treat, we set it as 1 hour for all people
    pair<int, int> app_date; // date of appointment as <month, day>
    int arrival_time;  // arrival time at the appointment date
    pair<int, int> total_wt; //total waiting time <days, hours> from register date to treated date
    Hospital *hospital_togo;
};
Treatment::Treatment(int t)
{
    Treatment_type = t;
    treat_time = 1;
    withdraw_counter = 14;
    hospital_togo = NULL;
}
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
    int id;
    People* people;
    STATUS_TYPE status;     // denote the status of the person
    // Medical Status
        // no idea about this part
    // Treatment
    Treatment* treat;

};
// constructor for the class Person
Person_BP::Person_BP(People* individual)
{
    people = individual;
    id = individual->id_number;
    Treatment* temp = new Treatment(individual->Treatment_Type);
    treat = temp;
}




// class Edges 
// for ex4 in PA2
class Edges
{
public:
    Edges(People* &p1, People* &p2);
    pair<People*, People*> edge_;
    int length;
    int Edge_ID;
};
// constructor of class Edges
Edges::Edges(People* &p1, People* &p2)
{
    edge_.first = p1;
    edge_.second = p2;
    int len_1 = (p1->address.first - p2->address.first)*(p1->address.first - p2->address.first);
    int len_2 = (p1->address.second - p2->address.second)*(p1->address.second - p2->address.second);
    length = (int)sqrt(len_1 + len_2);
    Edge_ID = length%DISTANCE_THETA;  // length mod theta      
}



// class Block
// This is block for the use of BPtree
class Block
{
public:
    Block(RELATION_TYPE r, int size_);

    RELATION_TYPE type;     // denote whether it is Person or Edges
    Person_BP** Person_;     // the Person records where ID will be the label
    Edges** Edges_;          // the Edge record for ex4 where length will be the label
    // member functions 
    bool search_record(RELATION_TYPE r, KeyType key);
    bool insert_record(Person_BP* &p);   // overloaded insert functions
    bool insert_record(Edges* &e);
    void sort_block();          // sort the block when merged into main block
    bool remove_record(RELATION_TYPE r, KeyType key);
    Block* merge_block(Block* &m_block);   // merge current block with input block
    Block* split_block();   // split current block into two blocks

    int record_num(){return Records_num;}
    int remain_space(){return size-Records_num;}
    int overflow_num(){return Overflow_num;}
    int get_label(){return label;}
    void display_block();
private:
    int label;    // the label of the block
    int size;     // the size of the block
    int Records_num;    // the current num of records in the whole block
    int Overflow_num;   // records in overflow block
    int Main_num;       // records in main block
    Edges** Overflow;    // the overflow block for this block 
};
// Constructor for class Block
Block::Block(RELATION_TYPE r, int size_)
{
    type = r;
    if (r == PERSON) {
        size = 1; Records_num = 0;
        Person_ = new Person_BP*[size];
    }
    if (r == EDGE) {  
        size = size_; Records_num = Overflow_num = Main_num = 0;
        Edges_ = new Edges*[size];
        Overflow = new Edges*[size/2];       // initialize the overflow block
        label = 0;
    }
    
}





#endif