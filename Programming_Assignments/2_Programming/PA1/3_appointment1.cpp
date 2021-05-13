//#include <bits/stdc++.h>
#include "3_appoint.h"
using namespace std;

//################## Member functions part ######################

int Appoint_People::selection(Hospital **hospital_list, int H_num)
{
    // sort using selection sort
    for (int i = 0; i < H_num-1; i++) {
        int minimum = distance(hospital_list[i]), min_index = i;
        for (int j = i + 1; j < H_num; j++) {
            if (distance(hospital_list[j]) < minimum) {
                minimum = distance(hospital_list[j]);
                min_index = j;
            } 
        } 
        Hospital *temp = hospital_list[min_index];
        hospital_list[min_index] = hospital_list[i]; 
        hospital_list[i] = temp;
    }
    // select the correct hospital
    int success = 0;
    for (int i = 0; i < H_num; i++) {
        // if the closest hospital still have capacity for treatment
        if (hospital_list[i]->current_num < hospital_list[i]->capacity) {
            hospital_togo = hospital_list[i];
            hospital_list[i]->current_num++;     // update the current people waiting to be treated in that hospital;
            success = 1;    // successfully assigned appointment
            break;
        }   // otherwise, search for the second close hospital
    } return success;
}

int Appoint_People::distance(Hospital *hos)
{
    int dx = hos->address.first - address.first;
    int dy = hos->address.second - address.second;
    return dx*dx+dy*dy;
}

// ######## Member functions for Withdraw ############
void Withdraw::withdraw_p(People *people)
{
    people->withdraw = -1;
    withdraw_list[withdraw_num] = people;
    withdraw_num++;
}

People* Withdraw::find(int id)
{
    People* result = NULL;
    for (int i = 0; i < withdraw_num; i++) {
        if (withdraw_list[i]->id_number == id) {
            result = withdraw_list[i];
            return result;
        }
    }
    return result;
}






//################ Isolated functions part ###################

void appointment(Fheap<int> &fib_heap, queue<Appoint_People*> &waiting, int total_capa)
{
    for (int i = 0; i < total_capa; i++) {
        Node<int> *people = fib_heap.pop_people(); 
        if (people == NULL){
            return;
        }
        if (people->person == NULL) return;
        Appoint_People *temp = new Appoint_People(people->person);
        if (temp == NULL)   cout << "78NULL\n";
        // copy certain information of the people
        temp->reg_date.first = people->person->register_date.first;
        temp->reg_date.second = people->person->register_date.second;
        temp->address.first = people->person->address.first;
        temp->address.second = people->person->address.second;
        //  copy the withdraw information
        temp->withdraw = people->person->withdraw;
        waiting.push(temp);
    }
}


// before treating function is called, the appointment function should be called 
// such that more people are added into the "waiting" queue
void treating(queue<Appoint_People*> &waiting, queue<Appoint_People*> &treating, queue<Appoint_People*> &treated, 
              Hospital **hospital_list, int H_num, int day_offset)
{
    time_t now = time(0);   // used to indicate the time of appointment
    tm *today = localtime(&now);
    int num_treating = 0;   // number of people assigned appointment today
    queue<Appoint_People*> withdraw_temp;

    while (!treating.empty()) { // in the next day, pop out all people in "treating" queue
        treated.push(treating.front()); // add them into the "treated" queue
        treating.front()->hospital_togo->current_num--;     // decreases the number of people in the hospital
        treating.pop();
    }
    
    while (!waiting.empty()) {  // assign appointment to people in the "waiting queue"
        Appoint_People *current = waiting.front();  // current people at the top of "waiting" queue

        if (0 == current->withdraw && 1 == current->selection(hospital_list, H_num)) {    
            // if this people has not withdrawn and successfully assign a hospital
            // set appointment date and arrival time
            current->app_date.second = (today->tm_mday+1+day_offset)%31; // set day
            current->app_date.first = today->tm_mon+1;  // set month          
            current->arrival_time = current->hospital_togo->open_slot.second - 
                                    (current->hospital_togo->capacity - current->hospital_togo->current_num);
            // set how many days and hours he/she has been waiting
            current->total_wt.first = (current->app_date.first - current->reg_date.first)*30 +
                                    (current->app_date.second - current->reg_date.second);
            current->total_wt.second = current->arrival_time;
            // now appointment has been assigned to this people, pop him/her from the "waiting"
            treating.push(waiting.front());
            waiting.pop();
            num_treating++;
        } else if (0 == current->withdraw && 0 == current->selection(hospital_list, H_num)) {
            break;

        // if this people has withdrawn before and registered again
        } else if (1 == current->withdraw) {    
            // if the extended withdraw waiting time is 0, assign hospital
            if (0 == current->withdraw_counter && 1 == current->selection(hospital_list, H_num)) {
                // set appointment date and arrival time
                current->app_date.second = (today->tm_mday+1+day_offset)%31; // set day
                current->app_date.first = today->tm_mon+1;  // set month          
                current->arrival_time = current->hospital_togo->open_slot.second - 
                                        (current->hospital_togo->capacity - current->hospital_togo->current_num);
                // set how many days and hours he/she has been waiting
                current->total_wt.first = (current->app_date.first - current->reg_date.first)*30 +
                                        (current->app_date.second - current->reg_date.second);
                current->total_wt.second = current->arrival_time;
                // now appointment has been assigned to this people, pop him/her from the "waiting"
                treating.push(waiting.front());
                waiting.pop();
                num_treating++;
            } else if (0 == current->withdraw_counter && 0 == current->selection(hospital_list, H_num)) {
                break;
            } else if (current->withdraw_counter > 0) { // if this people still has to wait
                current->withdraw_counter--;    //decrease the counter
                withdraw_temp.push(waiting.front()); //and push into temp queue
                waiting.pop();
            }
        }
    }
    // now some people in "waiting" queue has been assigned to an appointment
    // we need to push people in "withdraw" queue into "waiting" queue
    while (!waiting.empty()) {
        withdraw_temp.push(waiting.front());
        waiting.pop();
    }
    while (!withdraw_temp.empty()) {
        waiting.push(withdraw_temp.front());
        withdraw_temp.pop();
    }

}

void re_register(Fheap<int> &fib_heap, People *people)
{
    Node<int> *newnode = new Node<int>(0, people);
    fib_heap.insert_people(newnode, fib_heap.find_min());
}












