/* 
 * File name: appoint.h
 * Linked File: fibo_heap.cpp
 * Creat Date: 2021.3.24
 * Created By: Xiaomin Qiu, Guanshujie Fu
 * 
 * Mainly: this file contains class definition of Hospital and 
 *         Appoint People as well as decalerations of functions
 *         used for assigning appointment and withdraw.
 * 
 */
#ifndef APPOINT_H
#define APPOINT_H



#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <string>

#include "2_fibo_heap.cpp"
using namespace std;


class Hospital
{
public:
    Hospital(int open = 8, int close = 18, int ability = 1);  
    int hos_id; // the id number of the hospital
    int ptime;   //窗口所在人的剩余时间
    int current_num;  // current number of people appointed at this hospital
    int capacity;  //daily capacity, depending on how many people can be treated in an hour

    pair<int, int> open_slot; //time slots for the treatment as <open_time, close_time>
    pair<int, int> address;  //address stored as <x, y>
};
//The constructor of the class Hospital
Hospital::Hospital(int open, int close, int ability)
{
    open_slot.first = open;
    open_slot.second = close;
    capacity = ability*(close - open);
}

//############################################

class Appoint_People
{
public:
    Appoint_People(People *individual);

    People *person;     // store the information of the people
    pair<int, int> reg_date; // date of register as <month, day>
    pair<int, int> app_date; // date of appointment as <month, day>
    int arrival_time;  // arrival time at the appointment date
    int treat_time; // time needed to treat, we set it as 1 hour for all people
    pair<int, int> total_wt; //total waiting time <days, hours> from register date to treated date
    pair<int, int> address;

    int withdraw;   // indicate whether the people has applied for withdraw
    int withdraw_counter;

    Hospital *hospital_togo;

    // sort the hospital lists according to distance and set the hospital id
    // also, the selection function will update the hospital's certain info
    int selection(Hospital **hospital_list, int H_num);
    int distance(Hospital *hos);     // function used to calculate the distance

};
// constructor of the class Appoint_People
Appoint_People::Appoint_People(People *individual)
{
    treat_time = 1;     // one hour needed to be treated
    withdraw = 0;       // initially 0 as not withdraw
    withdraw_counter = 14;  // two weeks of waitting time
    person = individual;
}

//############################################

class Withdraw
{
public:
    Withdraw();
    /*
    * withdraw
    * INPUT: People *people
    * OUTPUT: None
    * 
    * This function is used to withdraw people apply for withdraw. 
    * People who apply for the withdraw will be added into 
    * the withdraw_list and their "withdraw" field will be set to -1.
    * 
    */
    void withdraw_p(People *people);
    People* find(int id);
    int withdraw_num;       // number of people who withdraw
    int monthly_withdraw;
    People **withdraw_list; // list which store pointers of people who withdraw
};
// constructor for the class Withdraw
Withdraw::Withdraw()
{
    withdraw_num = 0;
    monthly_withdraw = 0;
    People **temp = new People*[500];
    withdraw_list = temp;
    for (int i = 0; i < 500; i++) {
        withdraw_list[i] = NULL;
    }
}


/*
 * appointment
 * INPUT: queue<Appoint_People> &Fibo_heap, total_capa, time
 * OUTPUT: None
 * 
 * This function is used to assigned appointment to people with high priority in Fib_heap
 * people with highest priority will be added into "waiting" queue. The number of people 
 * added into the queue is constant.
 * 
 */
void appointment(Fheap<int> &fib_heap, queue<Appoint_People*> &waiting, int total_capa);


/*
 * treating
 * INPUT: queue<Appoint_People> &treated
 * OUTPUT: None
 * 
 * This function is used to assign treating to people with appointment, if hospital still have 
 * capacity then the people in the "waiting" queue will be popped and added into "treating" queue.
 * 
 */
void treating(queue<Appoint_People*> &waiting, queue<Appoint_People*> &treating, queue<Appoint_People*> &treated, 
                Hospital **hospital_list, int H_num, int day_offset);



/*
 * re_register
 * INPUT: Fheap<int> fib_heap, People *people
 * OUTPUT: None
 * 
 * This function is used to register withdrawn people who apply for 
 * registration again. The field of the "withdraw" will be 1.
 * 
 */
void re_register(Fheap<int> &fib_heap, People *people);
#endif  /* appoint.h */