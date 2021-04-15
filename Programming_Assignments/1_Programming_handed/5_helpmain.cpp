#include "5_helpmain.h"


int search_people(int id, Fheap<int> &fib, queue<Appoint_People*> &waiting, queue<Appoint_People*> &treating,
                   queue<Appoint_People*> &treated, Withdraw &withdraw)
{   
    Node<int> *temp = fib._find_handle_people(id);
    if (NULL == temp)   cout << "NULLexists\n";
    if (NULL != temp && temp->person != NULL && temp->person->withdraw != -1 && temp->person->leave != 1) {
        cout << "\033[33m";
        cout << temp->person->firstname << " is in Treatment Center.\n\033[0m";
        return 0;
    } else {
        // search in waiting queue
        for (int i = 0, size = waiting.size(); i < size; i++) {
            Appoint_People *tmp = waiting.front();
            if (waiting.front()->person->id_number == id) {
                cout << "\033[33m";
                cout << tmp->person->firstname << " is waiting for appointment.\n\033[0m";
                return 1;
            }
            waiting.pop();
            waiting.push(tmp);
        }
        // search in treating queue
        for (int i = 0, size = treating.size(); i < size; i++) {
            Appoint_People *tmp = treating.front();
            if (treating.front()->person->id_number == id) {
                cout << "\033[33m";
                cout << tmp->person->firstname << " is waiting for treatment.\n\033[0m";
                return 2;
            }
            treating.pop();
            treating.push(tmp);
        }
        // search in treated queue
        for (int i = 0, size = treated.size(); i < size; i++) {
            Appoint_People *tmp = treated.front();
            if (treated.front()->person->id_number == id) {
                cout << "\033[33m";
                cout << tmp->person->firstname << " has been treated.\n\033[0m";
                return 3;
            }
            treated.pop();
            treated.push(tmp);
        }
        // search in withdrawn class
        for (int i = 0; i < withdraw.withdraw_num; i++) {
            if (withdraw.withdraw_list[i]->id_number == id) {
                cout << withdraw.withdraw_list[i]->firstname << " has withdrawn.\n";
                return 4;
            }
        }
    } return -1;    //not found
}

void fib_people(Fheap<int> &fib, int id, int operate, Withdraw &withdraw)
{
    if (operate == 1) { // change profession
        int new_prof;
        bool test = true;
        while (test)
        {
            cout << "Enter new profession category: (1~8)";
            cin >> new_prof;
            if(new_prof>=1 && new_prof<=8)
            {
                test = false;
            } else
            {
                cout<<"ERROR: invalid input"<<endl;
            }
        }
        System_load("Changing");
        if (fib._find_handle_people(id) != NULL)
            fib.change_profession(id, new_prof);
        cout << "Profession is now: " << new_prof << endl;
    } else if (operate == 2) {  // change risk
        int new_risk;
        bool test = true;
        while (test)
        {
            cout << "Enter new risk: (0~3)";
            cin >> new_risk;
            if (new_risk>=0 && new_risk<=3)
            {

                test = false;
            } else
            {
                cout<<"ERROR: invalid input"<<endl;
            }
        }
        System_load("Changing");
        if (fib._find_handle_people(id) != NULL)
            fib.change_risk(id, new_risk);
        cout << "Risk status is now: " << new_risk << endl;
    } else if (operate == 3) {  // apply for priority
        int letter_temp;
        bool test = true;
        while (test)
        {
            cout<<"Choose if you want to give up a letter or apply for one: (1 for apply, 0 for give up): ";
            cin >> letter_temp;
            if(letter_temp>=0 && letter_temp<=1)
            {
                test = false;
            } else
            {
                cout<<"ERROR: invalid input"<<endl;
            }
        }
        System_load("Changing");
        fib.change_letter(id,letter_temp);
    } else if (operate == 4) { // withdraw
        withdraw.withdraw_p(fib.delete_people(id));   
        System_load("Withdraw");
        cout << "Withdraw Done.\n";
    } else if (operate == 5) {  // show info
        System_load("Loading");
        if (fib._find_handle_people(id) != NULL) {
            cout << "\033[32m";
            cout << "\nName: " <<  fib._find_handle_people(id)->person->firstname << " " << fib._find_handle_people(id)->person->surname;
            cout << "\nID:" << fib._find_handle_people(id)->person->id_number;
            cout << "\nRisk: " << fib._find_handle_people(id)->person->risk << " (" << fib._find_handle_people(id)->person->trapped/3 << " days remain)";
            cout << "\nProfession: " << fib._find_handle_people(id)->person->profession;
            cout << "\nRegister Date: " << fib._find_handle_people(id)->person->register_date.first << "." <<fib._find_handle_people(id)->person->register_date.second;
            cout << "\nWithdraw Status: ";
            if (fib._find_handle_people(id)->person->withdraw == 0)     cout << "Never Withdrawn.";
            if (fib._find_handle_people(id)->person->withdraw == 1)     cout << "Have Withdrawn before.";
            cout << "\nPriority Application: ";
            if (fib._find_handle_people(id)->person->deadline == 0)     cout << "None";
            if (fib._find_handle_people(id)->person->deadline == 1)     cout << "Applied";
            cout << "\033[0m\n";
        }
    } 
    else {
        return;
    } return;
}

void show_info(Appoint_People* person)
{
    cout << "\033[32m";
    cout << "\nName: " <<  person->person->firstname << " " << person->person->surname;
    cout << "\nID:" << person->person->id_number;
    cout << "\nRisk: " << person->person->risk;
    cout << "\nProfession: " << person->person->profession;
    cout << "\nRegister Date: " << person->person->register_date.first << "." <<person->person->register_date.second;
    cout << "\nWithdraw Status: ";
    if (person->person->withdraw == 0)     cout << "Never Withdrawn.";
    if (person->person->withdraw == 1)     cout << "Have Withdrawn before.";
    cout << "\nPriority Application: ";
    if (person->person->deadline == 0)     cout << "None";
    if (person->person->deadline == 1)     cout << "Applied";
    cout << "\033[0m\n";
}