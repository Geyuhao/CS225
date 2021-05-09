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
#include "PA1/5_helpmain.cpp"

using namespace::std;

/*
 * Four relations: Person, Medical Status, Registration, Treatment
 * We combine Person, Medical Status and Treatment as one relation as there is no need to exist four relations
 * The B+Tree needed will be 2
 * 
 */
class Person
{
public:
    Person();
    // Basic information of a person
    pair<string, string> name;  // name pair stored as (first name, surname)
    pair<int,int> age;    // age pair which works as (age, age_group)

    int id_number;      // id number of this person
    long long int phone_num;      // contact info
    string email;       
    int risk;           // risk rank from 0~3
    int profession;     // profession categories from 1~8
    pair<int, int> address;// represent address as (x, y)
    //
    int withdraw;       // denote if he has withdrawn
    int leave;          // denote if he left the fib_heap
    int deadline;       // the deadline of treatment if this person has applied for it
    int trapped;        // if the risk of the person is 2, trapped 30 days;
    pair<int, int> register_date;  // date of the register (month, date)
    int key_weight;


    // Medical Status
        // no idea about this part


    // Treatment (this part contains the treatment information for the people)
    int withdraw_counter;   // initially as 14
    int treatment_type; // three types of treatment.
    int treat_time; // time needed to treat, we set it as 1 hour for all people
    pair<int, int> app_date; // date of appointment as <month, day>
    int arrival_time;  // arrival time at the appointment date
    pair<int, int> total_wt; //total waiting time <days, hours> from register date to treated date
    Hospital *hospital_togo;

};
// constructor for the class Person
Person::Person()
{
    id_number = phone_num = leave = 0;
    risk = profession = withdraw = 0;
    trapped = 0;
    address.first = address.second = 0;
    key_weight = 0;
    treat_time = 1;
    withdraw_counter = 14;
    hospital_togo = NULL;
}


class Registration
{

};






#endif