/* 
 * File name: main_program.cpp
 * Linked File: report.h, report.cpp
 * Creat Date: 2021.4.5
 * Created By: Guanshujie Fu, Yuhao Ge
 * 
 * Mainly: this file contains main program for Computing assignment
 * 
 */
#include "5_helpmain.cpp"
#include <cstdlib>
#include <iostream>

int search_people(int id, Fheap<int> &fib, queue<Appoint_People*> &waiting, queue<Appoint_People*> &treating,
                   queue<Appoint_People*> &treated, Withdraw &withdraw);
void fib_people(Fheap<int> &fib, int id, int operate, Withdraw &withdraw);
void show_info(Appoint_People* person);




int main()
{
    // decalaration of needed class and queue
    //  three queues to store the people
    queue<Appoint_People*> waiting_q;
    queue<Appoint_People*> treating_q;
    queue<Appoint_People*> treated_q;
    // queues of different locations
    queue<People*> local_1;
    queue<People*> local_2;
    queue<People*> local_3;
    // hospital needed
    Hospital **hospital_list = new Hospital*[5];
    for (int i = 0; i < 5; i++) {   // three hospitals, append later
        Hospital *temp = new Hospital;
        temp->address.first = (i+1)*i*23%5;
        temp->address.second = (i+6)*i*i*32%5;
        temp->hos_id = i;
        hospital_list[i] = temp;
    }
    // file names
    string local1 = "local1.txt";
    string local2 = "local2.txt";
    string local3 = "local3.txt";
    string weekly = "week_report.txt";
    string monthly = "month_report.txt";
    // time field
    int day_offset = 0;
    // statistic field
    const int day_reg = 20;  // people taken from local queue every day
    const int day_appo = 40; // people assign appointments everyday
    int month_reg = 0;      // number of people registered in a month
    int daily_reg = 0;
    Withdraw withdraw_info;     // store the info of withdrawn people
    // fibonacci filed
    Fheap<int> Fib_center;

    int operation;
// main program starts here
    printf("\033[31mSystem Loading\033[0m");
        for (int i = 0; i < 3; i++) {
            cout << "\033[31m.\033[0m" << flush;Delay(0.2);
        } Delay(1);
    printf("\033[31m\n");

    printf("\t\t|---|           |---|       \t|---|         \n");Delay(0.1);
    printf("\t\t|   |           |   |       \t|___|         \n");Delay(0.1);
    printf("\t\t|   |           |   |       \t ___          \n");Delay(0.1);
    printf("\t\t|   |           |   |       \t|   |         \n");Delay(0.1);
    printf("\t\t|   |           |   |       \t|   |         \n");Delay(0.1);
    printf("\t\t|   |___________|   |       \t|   |         \n");Delay(0.1);
    printf("\t\t|   |___________|   |       \t|   |         \n");Delay(0.1);
    printf("\t\t|   |           |   |       \t|   |         \n");Delay(0.1);
    printf("\t\t|   |           |   |       \t|   |         \n");Delay(0.1);
    printf("\t\t|   |           |   |       \t|   |         \n");Delay(0.1);
    printf("\t\t|   |           |   |       \t|   |         \n");Delay(0.1);
    printf("\t\t|   |           |   |       \t|   |         \n");Delay(0.1);
    printf("\t\t|---|           |---|       \t|___|         \n");Delay(0.1);

    printf("\033[0m");
    printf("\033[33m");printf("\033[2m");printf("\033[3m");
    printf("System Name:    Hospital Interactive System.\n");
    printf("System Designer: \n");
    printf("                Guanshujie Fu\n");
    printf("                Xiaomin Qiu\n");
    printf("                Haina Lou\n");
    printf("                Yuhao Ge\n\033[0m");



    cout << "\n\n--------------------------- Welcome -------------------------------\n";
    //printf("\033[31mThis is RED.\n\033[0m");
    printf("\033[33mPlease choose your operation: \n\033[0m");
    cout << "1. File registration for all locations.\n";
    cout << "2. Quit systems.\n";
    cin >> operation;
    
    switch (operation) {
    case 1:
        printf("\033[31mRegistering\033[0m");
        for (int i = 0; i < 4; i++) {
            cout << "\033[31m.\033[0m" << flush;Delay(0.7);
        } Delay(0.4);
        File_Read(local1, local_1, 0);
        File_Read(local2, local_2, 0);
        File_Read(local3, local_3, 0);
        cout << "\nAll three locations have people registered:\n";Delay(0.3);
        cout << "Hangzhou: " << local_1.size() << " people registered.\n";Delay(0.3);
        cout << "Jiaxing: " << local_2.size() << " people registered.\n";Delay(0.3);
        cout << "Ningbo: " << local_3.size() << " people registered.\n\n";Delay(0.3);
        break;
    case 2:
        return 0;
    default:
        cout << "Invalid Choice\n";
        return 0;
        break;
    }

    // interactive menu 1
    printf("\033[33mPlease choose your operation: \n\033[0m");
    cout << "1. Automaticaly System Performance. (Automatic operations from systems)\n";
    cout << "2. Interactive System Performance. (Interaction required)\n";
    cin >> operation;
    int auto_op;
    if (operation == 1)     auto_op = 1;
    else     auto_op = 0;

    System_load("System Loading");
    printf("\033[0m");

    //############## automatic operation begins there ########################
    if (auto_op == 1) {
        cout << "\n------------------- Automatic Performance -----------------\n";
        cout << "\033[31mAutomatic Performance System successfully loaded!\n\033[0m";Delay(0.5);
        cout << "Automatic Performance will perform operations during a time of a month.\n";
        cout << "All operations are defined inside the system\n";
        cout << "Weekly Report, Monthly Report will also be generated.\n";
        cout << "\033[33mPress random key to continue: \033[0m";
        cin >> operation;

        // monthly loop starts
        for (day_offset = 0; day_offset < 29; day_offset++) {    // represent a month
            cout << "\n\n\033[33m--------- Today is 2021." <<  date_calc(day_offset).first << "." << date_calc(day_offset).second << "----------\n\033[0m";

            // register into central
            int origin1 = local_1.size(), origin2 = local_2.size(), origin3 = local_3.size();
            register_in(Fib_center, local_1, day_reg, day_offset);   // register local1 into the center
            register_in(Fib_center, local_2, day_reg, day_offset);   // register local2 into the center
            register_in(Fib_center, local_3, day_reg, day_offset);   // register local3 into the center
            daily_reg = origin1-local_1.size() + origin2-local_2.size() + origin3-local_3.size();
            month_reg += origin1-local_1.size() + origin2-local_2.size() + origin3-local_3.size();  // calculate number of people registered
            // now people from local have been registered into the center
            // appointment can be processe
            appointment(Fib_center, waiting_q, day_appo);
            // withdraw happened when the people are int 'waiting' queue
            for (int i = 0, rd = rand()%6; i < rd; i++) {
                if (waiting_q.empty())  break;
                withdraw_info.withdraw_p(waiting_q.front()->person);
                waiting_q.pop();
            }
            // assign appointment
            treating(waiting_q, treating_q, treated_q, hospital_list, 5, day_offset);
            // withdraw when appointments assigned
            for (int i = 0; i < rand()%5; i++) {
                if (treating_q.empty())   break;
                withdraw_info.withdraw_p(treating_q.front()->person);
                treating_q.front()->hospital_togo->current_num--;
                treating_q.pop();
            }
            // now treating appointments for next have been assigned

            // generate a simple daily report
            cout << "|System Daily Report\n";Delay(0.5);
            //cout << hospital_list[0]->current_num+hospital_list[1]->current_num+hospital_list[2]->current_num+hospital_list[3]->current_num+hospital_list[4]->current_num << endl;
            cout << "| " << daily_reg << " people registed into center system                   \n";Delay(0.2);
            cout << "| " << waiting_q.size() << " people are waiting for appointments assgined  \n";Delay(0.2);
            cout << "| " << treating_q.size() << " people are assigned with appointments        \n";Delay(0.2);
            cout << "| " << treated_q.size() << " people have been treated                      \n";Delay(0.2);
            cout << "| " << withdraw_info.withdraw_num << " people withdrawn until today.       \n";Delay(0.2);
            // generate weekly and monthly report
            if (day_offset != 0 && day_offset%7 == 0) {
                weekly_report(treated_q, treating_q, waiting_q, day_offset, weekly, 1);
                cout << "Weekly report generated.\n";
                cout << "Press '1' to confirm the Weekly Report and continue.\n";
                cin >> operation;
                operation = 'N';
                Delay(0.5);
                //getchar();
            } else if ((day_offset != 0 && day_offset % 29 == 0) || ((int)treated_q.size()+(int)withdraw_info.withdraw_num == month_reg)) {
                monthly_report(month_reg, withdraw_info.withdraw_num, Fib_center.people_num(), waiting_q, treating_q, treated_q, monthly);
                cout << "Monthly report generated.\n";
                cout << "Press '1' to confirm the Monthly Report and see the result after one month.\n";
                cin >> operation;
                operation = 0;
                Delay(0.6);
                cout << "System Shutdown";
                for (int i = 0; i < 5; i++) {
                    cout << "." << flush; Delay(0.5);
                }
                cout << "Short System Running Report generating\n";
                for (int i = 0; i < 5; i++) {
                    cout << "." << flush            ; Delay(0.5);
                } Delay(0.8);
                break;
            }

        }
        cout << "\n\033[33m------------------- System Running Result ------------------\n";
        cout << "After simulation of one month running: \n";
        cout << "System Registered " << month_reg << " people into the center.\n";
        cout << treated_q.size() << " people have been treated.\n";
        cout << withdraw_info.withdraw_num << " people withdrawn.\n";
        cout << "All people are treated in " << day_offset << " days.\n";
        cout << "------------------- System Running Result ------------------\n\033[0m";
        // automatic performance finishes
    }  
    
    
    
    else {  
        //############## interactive operation begins there ########################
        int quit = 0;
        cout << "\n------------------- Interactive Performance -----------------\n";
        cout << "\033[31mInteractive Performance System successfully loaded!\n\033[0m";Delay(0.5);
        cout << "Interactive Performance will perform operations that you choose.\n";
        cout << "Weekly Report, Monthly Report will also be generated.\n";
        cout << "\033[33mPress '1' to continue: \033[0m";
        cin >> operation;
        for (day_offset = 0; quit != 1; day_offset++) {
        operation = 1;
        System_load("Menu Loading");
        cout << "\n\n\033[33m--------- Today is 2021." <<  date_calc(day_offset).first << "." << date_calc(day_offset).second << "----------\n\033[0m";
        while (operation != 0) {
            cout << "\033[33m\nPlease choose your operation:\n\033[0m";
            cout << "1. Register People from local registries to the Treatment Center.\n";
            cout << "2. Set appointments for people queueing.\n";
            cout << "3. Operation for single patient.\n";
            cout << "4. Report System Situation.\n";
            cout << "5. Go Next Day.\n";
            cout << "6. Display Central Structure (Fibonacci Heap).\n";
            cout << "0. Quit System.\n";        
            cin >> operation;
            switch (operation){
            case 0:
                quit = 1;
                break;
            case 1: {
                System_load("Process Handling");
                cout << "Local_1 registry remains " << local_1.size() << " people\n";
                cout << "Local_2 registry remains " << local_2.size() << " people\n";
                cout << "Local_3 registry remains " << local_3.size() << " people\n";
                int temp[3] = {(int)local_1.size(), (int)local_2.size(),(int)local_3.size()};
                for (int i = 1, num; i < 4; i++) {
                    cout << "How many people you want to register to Treatment Center from local_" << i << ": ";
                    cin >> num;
                    if (num > temp[i-1]) {
                        num = temp[i-1];
                    } temp[i-1] = num;
                }
                register_in(Fib_center, local_1, temp[0], day_offset);
                register_in(Fib_center, local_2, temp[1], day_offset);
                register_in(Fib_center, local_3, temp[2], day_offset);
                System_load("Instruction Handling");
                cout << "\033[33m";
                cout << temp[0]+temp[1]+temp[2] << " people are registered into Treatment Center from three registries.\n\033[0m";
                month_reg += temp[0]+temp[1]+temp[2]; 
                break;
            }
            case 2: {
                System_load("Process Handling");
                cout << "Treatment Center remains " << Fib_center.people_num() << " people.\n";
                cout << "People waiting for appointment: " << waiting_q.size() << "\n";
                cout << "How many people you want to set appointments: ";
                int num, origin;
                cin >> num;
                if (num > Fib_center.people_num())  num = Fib_center.people_num();
                origin = Fib_center.people_num();
                appointment(Fib_center, waiting_q, num);
                System_load("Instruction Handling");
                cout << "\033[33m";
                cout << origin-Fib_center.people_num() << " people from Treatment Center has been added to wait for appointments assigned.\n";
                cout << Fib_center.people_num() << " reamins in Treatment Center\n\033[0m";
                break;
            }
            case 3: {       // operation for single people
                System_load("Process Handling");
                cout << "Enter the ID number of the patient: ";
                int id, result;
                cin >> id;
                System_load("Searching");
                result = search_people(id, Fib_center, waiting_q, treating_q, treated_q, withdraw_info);
                if (result == -1) { // patient not found
                    cout << "Patient not registered.\n";
                    break;
                } else {        // patient found
                    switch (result) {
                    case 0: {   // in fib_heap
                        while (result == 0) {   // while loop for personal operation
                        cout << "\033[33mThis patient is now in the Treatment Center\n\033[0m";
                        cout << "\033[33mChoose Operation for this Patient:\n\033[0m";
                        cout << "1. Change Profession.\n";
                        cout << "2. Change Risk.\n";
                        cout << "3. Apply for Priority Letter.\n";
                        cout << "4. Withdraw.\n";
                        cout << "5. Show Personal Info.\n";
                        cout << "0. Quit.\n";
                        int tmp;
                        cin >> tmp;
                        // operations of people
                        fib_people(Fib_center, id, tmp, withdraw_info);
                        if (tmp == 0 || tmp == 4)   result = -1;    // quit
                        } // personal operation ended here
                        break;
                    } // case 0 end
                    case 1: {   // in waiting_q
                        cout << "\033[33mThis patient is now in the waiting queue\n\033[0m";
                        cout << "\033[33mChoose Operation for Patient:\n\033[0m";
                        cout << "1. Withdraw.\n";
                        cout << "2. Show Personal Info.\n";
                        cout << "0. Quit.\n";
                        int tmp;
                        cin >> tmp;
                        if (tmp != 1 && tmp != 2)   break;
                        // find in waiting_q, pop out and added into withdraw_list
                        for (int i = 0; i < (int)waiting_q.size(); i++) {
                            Appoint_People *temp = waiting_q.front();
                            if (temp->person->id_number == id) {
                                if (tmp == 1) {
                                    withdraw_info.withdraw_p(temp->person);
                                    waiting_q.pop();
                                } else {
                                    System_load("Loading");
                                    show_info(temp);
                                }
                                break;
                            }
                            waiting_q.pop();
                            waiting_q.push(temp);
                        } break;
                    } // case 1 end
                    case 2: {   // in treating_q
                        cout << "\033[33mThis patient is now in the Treating queue\n\033[0m";
                        cout << "\033[33mChoose Operation for Patient:\n\033[0m";
                        cout << "1. Withdraw.\n";
                        cout << "2. Show Personal Info.\n";
                        cout << "0. Quit.\n";
                        int tmp;
                        cin >> tmp;
                        if (tmp != 1 && tmp != 2)   break;
                        // find in waiting_q, pop out and added into withdraw_list
                        for (int i = 0; i < (int)treating_q.size(); i++) {
                            Appoint_People *temp = treating_q.front();
                            if (temp->person->id_number == id) {
                                if (tmp == 1) {
                                    withdraw_info.withdraw_p(temp->person);
                                    treating_q.pop();
                                } else {
                                    System_load("Loading");
                                    show_info(temp);
                                }
                                break;
                            }
                            treating_q.pop();
                            treating_q.push(temp);
                        } break;
                    }   // case 2 ended here
                    case 3: {
                        break;
                    }
                    case 4: {   // in withdraw_list
                        cout << "\033[33mThis patient has been withdrawn\n\033[0m";
                        cout << "\033[33mDo you want to register this person again or quit:\n\033[0m";
                        cout << "1. Register Again.\n";
                        cout << "0. Quit.\n";
                        int tmp;
                        cin >> tmp;
                        if (tmp != 1)   break;
                        if (withdraw_info.find(id) != NULL) {
                            re_register(Fib_center, withdraw_info.find(id));
                        }
                        break;
                    } 
                    default:
                        break;
                    } // inside switch ended here
                }
            break;
            } 
            case 4: {       // report system information
                System_load("Read");
                cout << "\033[32mSystem Information\n";
                cout << "Number of People waiting in local queues: " << local_1.size()+local_2.size()+local_3.size()<<endl;
                cout << "Number of People in Treatment Center: " << Fib_center.people_num() << endl;
                cout << "Number of People waiting for appointments: " << waiting_q.size() << endl;
                cout << "Number of People waiting for treatment: " << treating_q.size() << endl;
                cout << "Number of People have been treated: " << treated_q.size() << endl;
                cout << "\033[0m";
                break;
            }
            case 5: {   // next day
                operation = 0;
                break;
            }
            case 6: {
                Fib_center.print_heap_people();
                break;
            }
            default:
                break;
            }   // switch ended there
            if (quit == 1)  break;
        } // while loop ended here
        // go next day starts 
        treating(waiting_q, treating_q, treated_q, hospital_list, 5, day_offset);
        Fib_center.decrease_trap();
        if (day_offset != 0 && day_offset%7 == 0) {
            cout << "\033[33mChoose Weekly Report Sorting Method:\n\033[0m";
            cout << "1. Name    2. Profession    3. Age"; 
            int sort;
            cin >> sort;
            System_load("Weekly Report Generating");
            weekly_report(treated_q, treating_q, waiting_q, day_offset, weekly, sort);
        } else if (day_offset != 0 && day_offset%29 == 0) {
            System_load("Monthly Report Generating");
            monthly_report(month_reg, withdraw_info.withdraw_num, Fib_center.people_num(), waiting_q, treating_q, treated_q, monthly);
        }
        } // monthly loop ended here
        
    } // Interactive Performance ended here
    

}
/*
*/
