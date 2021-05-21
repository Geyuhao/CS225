#include "7_helpmain.h"


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

void show_info(Person_BP* person)
{
    cout << "\033[32m";
    cout << "\nName: " <<  person->people->firstname << " " << person->people->surname;
    cout << "\nID: " << person->people->id_number;
    //cout << "\nTreatment Type: " << person->treat->Treatment_type;
    cout << "\nRisk: " << person->people->risk;
    cout << "\nProfession: " << person->people->profession;
    cout << "\nStatus: ";
    if (person->status == REGISTER)     cout << "Not Registered.";
    if (person->status == IN_HEAP)      cout << "Waiting In Treatment Center.";
    if (person->status == WAITING)      cout << "Waiting For Appointment.";
    if (person->status == TREATING)     cout << "Treating.";
    if (person->status == TREATED)      cout << "Treated.";
    if (person->status == WITHDRAW)     {cout << "Withdrawn.\033[0m\n";return;}
    cout << "\nRegister Date: " << person->people->register_date.first << "." <<person->people->register_date.second;
    cout << "\nWithdraw Status: ";
    if (person->people->withdraw == 0)     cout << "Never Withdrawn.";
    if (person->people->withdraw == 1)     cout << "Have Withdrawn before.";
    cout << "\nPriority Application: ";
    if (person->people->deadline == 0)     cout << "None";
    if (person->people->deadline == 1)     cout << "Applied";
    cout << "\033[0m\n";
}

void Update(queue<Appoint_People*> q, CBPlusTree* &bptree, STATUS_TYPE s)
{
    if (q.size() == 0)  return;
    int size = q.size();
    for (int i = 0; i < size; i++) {
        Appoint_People* temp = q.front();
        bptree->update_status(temp->person->id_number, s);
        q.pop();
        q.push(temp);
    }
}


void big_register(Fheap<int> &fib, CBPlusTree* &bptree, BTree<Person_BP> &mybtree, MultiSet_Chaining* hash_treatment, MultiSet_Chaining* hash_med, queue<People*> &local_q, int num_people, int day_offset)
{

    vector<People*> temp_list;
    int counter = num_people;

    while (!local_q.empty() && counter != 0) 
    {
        temp_list.push_back(local_q.front());
        local_q.pop();
        counter--;
    }

    while(temp_list.size()!=0)
    { 
        People* one_people = temp_list.back();
        temp_list.pop_back();

        // register into fibonacci heap
        register_in(fib,one_people,day_offset);

        // register into btree
        mybtree.register2btree(one_people);

        // register to hash table

        // need correction????
        Person_BP* temp = new Person_BP(one_people);
        
        hash_treatment->insert_hash_treat(temp);
        hash_med->insert_hash_medstatus(temp);

        // bptree information updated
        bptree->update_status(one_people->id_number, IN_HEAP);
        

    }
    // from remote gyh
    fib.consolidate_people();       // check the print function when only insert is provoked.
}

void print_people_BP(Person_BP* person)
{
    cout << "\033[32m";
    cout<<person->people->id_number<<"\t"<<person->people->firstname << "\t";
    cout<<"\t"<<person->people->risk<<"\t"<<person->people->register_date.first<<"."<<person->people->register_date.second;

    cout<<"\t"<<person->treat->Treatment_type;
    cout << "\033[0m";
}


void Generate_data(CBPlusTree* &bptree, string filename)
{
    ofstream DATA(filename);
    if (!DATA.is_open()) {
        cout << "Open file failed\n";
        return;
    }
    DATA << 723 << "\n";
    CLeafNode* temp = bptree->get_head();
    while(temp!=NULL)
	{
		for (int i=0; i<temp->getKeyNum(); ++i)
		{
			DATA << temp->getData(i)->Person_[0]->id << ",";
            DATA << temp->getData(i)->Person_[0]->people->address.first << ",";
            DATA << temp->getData(i)->Person_[0]->people->address.second << ",";
            DATA << temp->getData(i)->Person_[0]->people->Treatment_Type << ",";
            DATA << 0 << "\n";
            if (temp->getRightSibling() == NULL && i == temp->getKeyNum()-1) {
                DATA << temp->getData(i)->Person_[0]->id << ",";
                DATA << temp->getData(i)->Person_[0]->people->address.first << ",";
                DATA << temp->getData(i)->Person_[0]->people->address.second << ",";
                DATA << temp->getData(i)->Person_[0]->people->Treatment_Type << ",";
                DATA << 0;
            }
		}
        
		temp = temp->getRightSibling();
	} DATA.close();
    return;
}
