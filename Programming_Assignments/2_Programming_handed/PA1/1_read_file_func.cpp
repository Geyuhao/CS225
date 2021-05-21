#include "1_read_file.h"
#include <iostream>
#include <fstream>      // use for file reading
#include <vector>
#include <ctime>        // realize the time delay
#include <stdlib.h>
using namespace::std;



// Time Delay function
void Delay(double delay_time)
{
    clock_t delay = delay_time*CLOCKS_PER_SEC;
    clock_t start = clock();
    while(clock() - start < delay){}
}

//date calculate func
pair<int, int> date_calc(int day_offset)
{
    time_t now = time(0);   // used to indicate the time of appointment
    tm *today = localtime(&now);

    pair<int, int> result;
    int month[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (today->tm_mday + day_offset <= month[today->tm_mon]) {
        result.first = today->tm_mon+1;
        result.second = today->tm_mday+day_offset;
        return result;
    } else {
        result.first = today->tm_mon+2;
        result.second = today->tm_mday + day_offset - month[today->tm_mon];
        return result;
    }
}

void System_load(string name)
{
    printf("\033[31m");
    cout << name;
    printf("\033[0m");
    for (int i = 0; i < 4; i++) {
        cout << "\033[31m.\033[0m" << flush;Delay(0.12);
    }
    printf("\n");
}


// File Read function
void File_Read(string file_name, queue<People*> &local_queue, int day)
{
    time_t now = time(0);   // used to indicate the time of appointment
    tm *today = localtime(&now);

    ifstream FILE_IN(file_name);
    if (!FILE_IN) { // if file open failed, reject and return
        cout << "File open failed.\n";
        return;
    }
    // if file open succeed, reading
    // The format of the file is:
    // Firstname Surname Age ID Address_x Address_y Profession Risk Phone Email
    while (!FILE_IN.eof()) {    // check if the reading has reached the end of the file
        People *person = new People;    // use to store the information of a person
        // information declaration
        string firstname, surname, email;
        int age, age_group, id;
        int risk, profession;
        unsigned long long int phone;
        int address_x, address_y;

        // read from stream FILE_IN
        FILE_IN >> firstname >> surname;        // read and store name from stream into person
        person->firstname = firstname;      
        person->surname = surname;

        FILE_IN >> age >> id;      // basic info of the person
        if (age <= 12) {
            age_group = 0;      // children
        } else if (age <= 18) {
            age_group = 1;      // adolescents
        } else if (age <= 35) {
            age_group = 2;      // young adults
        } else if (age <= 50) {
            age_group = 4;      // adults
        } else if (age <= 65) {
            age_group = 5;      // seniors
        } else if (age <= 75) {
            age_group = 6;      // elderly people
        } else age_group = 7;   // old people
        person->age.first = age;            // store age and age_group as pair
        person->age.second = age_group;
        
        person->id_number = id;
        // store the address coordinate as pair
        FILE_IN >> address_x >> address_y;  
        person->address.first = address_x;
        person->address.second = address_y;
        // read and store other information
        FILE_IN >> profession >> risk >> phone >> email;    
        person->profession = profession;
        person->risk = risk;
        if (risk >= 2)  person->trapped = 90;
        person->phone_num = phone;
        person->email = email;
        // set the register date of the people
        person->register_date.first = today->tm_mon+1;
        person->register_date.second = today->tm_mday+day;
        // one person's information has been read and push the person into the local queue
        person->Treatment_Type = rand()%3;
        local_queue.push(person);
    } FILE_IN.close();  // file reading finishes and close the file
    return;
}