/*
 * File name: read_file.h
 * Creat date: 2021.3.24
 * Guanshujie Fu;
 * Mainly: this file contains the necessary function and class definiton needed
 *         for reading formated file into code
 * 
 * 
 */


#ifndef READ_FILE_H
#define READ_FILE_H

#include <vector>
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>    // use for Delay
#include <queue>

using namespace::std;


class People
{
public:
    People();
    // Basic information of a person
    string firstname;     // name of the people
    string surname;
    pair<int,int> age;    // age pair which works as (age, age_group)

    int id_number;      // id number of this person
    long long int phone_num;      // contact info
    string email;       
    int risk;           // risk rank from 0~3
    int profession;     // profession categories from 1~8
    pair<int, int> address;// represent address as (x, y)
    // Updated information of a person
    int withdraw;       // denote if he has withdrawn
    int leave;
    int deadline;       // the deadline of treatment if this person has applied for it
    int trapped;        // if the risk of the person is 2, trapped 30 days;
    pair<int, int> register_date;  // date of the register
    int hospital_id;    // the hospital where he/she shoule go;
    int key_weight;
    int Treatment_Type;
};

People::People()        // This the constructor for class People;
{
    id_number = phone_num = leave = 0;
    risk = profession = withdraw = 0;
    trapped = 0;
    address.first = address.second = 0;
    key_weight = 0;
}


/*
 * Delay (double delay_time)
 * Input: time delay (s)
 * Output: None
 * 
 * This function realizes the time delay by setting delay_time expected
 */
void Delay(double delay_time);



/*
 * date_calc
 * Input: day_offset
 * Output: pair <month, date>
 * 
 * This function calculate the exact date
 */
pair<int, int> date_calc(int day_offset);

void System_load(string name);

/* 
 * File_Read
 * Input: file_name, queue to store, day offset
 * Output: None
 * 
 * This Function will read the file given and store the information into the queue
 */
void File_Read(string file_name, queue<People*> &local_queue, int day);







#endif  /*read_file.h*/