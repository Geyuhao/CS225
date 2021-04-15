


#include "4_report.h"
void weekly_report(queue<Appoint_People*> &treated_q, queue<Appoint_People*> &treating_q, 
                   queue<Appoint_People*> &waiting_q, int day_offset, string filename, int sort)
{
    // ####### Prepare for generating report ########
    ofstream REPORT(filename);
    if (!REPORT.is_open()) {
        cout << "Open file failed\n";
        return;
    }

    queue<Appoint_People*> temp_q;  
    Appoint_People **temp_l = new Appoint_People*[1000];     // list to store treated people
    Appoint_People **temp_i = new Appoint_People*[1000];     // list to store treating people
    Appoint_People **temp_w = new Appoint_People*[1000];     // list to store waiting people
    int treated_num, treating_num, waiting_num;
    treated_num = treating_num = waiting_num = 0;
    for (int i = 0; i < 1000; i++) {
        temp_l[i] = NULL;
        temp_i[i] = NULL;
        temp_w[i] = NULL;
    }
    for (int i = 0; i < (int) treated_q.size(); i++) {
        temp_l[treated_num++] = treated_q.front();
        temp_q.push(treated_q.front());
        treated_q.pop();
        // add this people tp treated_q again
        treated_q.push(temp_q.front());
        temp_q.pop();
    }
    for (int i = 0; i < (int)treating_q.size(); i++) {
        temp_i[treating_num++] = treating_q.front();
        temp_q.push(treating_q.front());
        treating_q.pop();
        // add this people tp treating_q again
        treating_q.push(temp_q.front());
        temp_q.pop();
    }
    for (int i = 0; i < (int)waiting_q.size(); i++) {
        temp_w[waiting_num++] = waiting_q.front();
        temp_q.push(waiting_q.front());
        waiting_q.pop();
        // add this people tp waiting_q again
        waiting_q.push(temp_q.front());
        temp_q.pop();
    }
    // as there are requests for the sorting way of report, we will sort according to name, profession and age
    switch (sort) {
    case 1:     // sort by name
        sort_name(temp_l, treated_num);
        sort_name(temp_i, treating_num);
        sort_name(temp_w, waiting_num);
        break;
    case 2:     // sort by profession
        sort_profession(temp_l, treated_num);
        sort_profession(temp_i, treating_num);
        sort_profession(temp_w, waiting_num);
        break;
    case 3:
        sort_age(temp_l, treated_num);
        sort_age(temp_i, treating_num);
        sort_age(temp_w, waiting_num);
        break;
    default:
        cout << "Invalid Choice\n";
        REPORT.close();
        return;
    }
    // Now we can generate report
    REPORT << "\t\t\tWEEKLY REPORT\n\n";
    // first we print out people who have been treated
    REPORT << "Treated People\n";
    // now people has been sorted according to choices
    
    for (int i = 0; i < treated_num; i++) {
        People* current = temp_l[i]->person;
        REPORT << "\t" << current->firstname << " " << current->surname << ":\n";
        REPORT << "\t\t" << "Profession Category: " << current->profession << endl;
        REPORT << "\t\t" << "Age Category:  " << current->age.second << endl;
        REPORT << "\t\t" << "Risk Status:  " << current->risk << endl;
        REPORT << "\t\t" << "Waiting Time:  " << temp_l[i]->total_wt.first << " days " <<temp_l[i]->total_wt.second << " hours" << endl;
    }

    REPORT << "Treating People\n";
    for (int i = 0; i < treating_num; i++) {
        People* current = temp_i[i]->person;
        REPORT << "\t" << current->firstname << " " << current->surname << ":\n";
        REPORT << "\t\t" << "Profession Category: " << current->profession << endl;
        REPORT << "\t\t" << "Age Category:  " << current->age.second << endl;
        REPORT << "\t\t" << "Risk Status:  " << current->risk << endl;
        REPORT << "\t\t" << "Waiting Time:  " << temp_i[i]->total_wt.first << " days" << temp_i[i]->total_wt.second << "hours" << endl;
    }

    REPORT << "Waiting People\n";
    for (int i = 0; i < waiting_num; i++) {
        People* current = temp_w[i]->person;
        REPORT << "\t" << current->firstname << " " << current->surname << ":\n";
        REPORT << "\t\t" << "Profession Category: " << current->profession << endl;
        REPORT << "\t\t" << "Age Category:  " << current->age.second << endl;
        REPORT << "\t\t" << "Risk Status:  " << current->risk << endl;
        REPORT << "\t\t" << "Waiting Time:  " << day_offset << " days" << endl;
    }
    REPORT.close();
}

// sort functions work for the weekly_report function
void sort_name(Appoint_People **list, int num_people)
{
    // Insertion Sort
    for (int i = 1, j; i < num_people; i++) {
        char temp = list[i]->person->firstname[0];
        Appoint_People *temp_people = list[i];
        
        for (j = i; j > 0 && temp < list[j-1]->person->firstname[0]; j--){
            list[j] = list[j-1];
        } list[j] = temp_people;
    }
}

void sort_profession(Appoint_People **list, int num_people)
{
     // Insertion Sort
    for (int i = 1, j; i < num_people; i++) {
        int temp = list[i]->person->profession;
        Appoint_People *temp_people = list[i];
        for (j = i; j > 0 && temp < list[j-1]->person->profession; j--){
            list[j] = list[j-1];
        } list[j] = temp_people;
    }
}

void sort_age(Appoint_People **list, int num_people)
{
     // Insertion Sort
    for (int i = 1, j; i < num_people; i++) {
        int temp = list[i]->person->age.second;
        Appoint_People *temp_people = list[i];
        for (j = i; j > 0 && temp < list[j-1]->person->age.second; j--){
            list[j] = list[j-1];
        } list[j] = temp_people;
    }
}



void monthly_report(int regester_num, int withdraw_num, int fib_size, queue<Appoint_People*> &waiting_q, 
                    queue<Appoint_People*> &treating_q, queue<Appoint_People*> &treated_q, string filename)
{
    ofstream REPORT(filename);
    if (!REPORT.is_open()) {
        cout << "File open failed\n";
        return;
    }
    Appoint_People* temp;
    int total_waiting = 0;
    float avg_waiting = 0;
    int size = waiting_q.size();
    for (int i = 0; i < size; i++) {
        total_waiting += waiting_q.front()->total_wt.first*24 + waiting_q.front()->total_wt.second;
        temp = waiting_q.front();
        waiting_q.pop();
        waiting_q.push(temp);
    }
    if (size != 0)    avg_waiting = total_waiting/size;

    REPORT << "\t\t\t\tMONTHLY REPORT\n";
    REPORT << "\tTotal Register:        " << regester_num << endl;
    REPORT << "\tCurrent Waiting:       " << waiting_q.size() << endl;
    REPORT << "\tTotal Waiting:         " << fib_size+waiting_q.size() << endl;
    REPORT << "\tAppointments Assigned: " << treated_q.size()+treating_q.size() << endl;
    REPORT << "\tAverage Waiting Time:  " << avg_waiting << " hours" << endl;
    REPORT << "\tWithdraw Number:       " << withdraw_num << endl;
    REPORT.close();
}