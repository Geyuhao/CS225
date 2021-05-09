#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <tuple>
#include "2_fibo_heap.h"
#include <vector>

#define MIN -100000

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::hash;


// Isolated functions
void register_in(Fheap<int> &fib, queue<People*> &local_q, int num_people, int day_offset)
{
    int counter = num_people;
    while (!local_q.empty() && counter != 0) {
        Node<int> *temp = new Node<int>(0, local_q.front());
        temp->person->register_date.first = date_calc(day_offset).first;
        temp->person->register_date.second = date_calc(day_offset).second;
        fib.insert_people(temp, fib.find_min());
        local_q.pop();
        counter--;
    }

    // from remote gyh
    fib.consolidate_people();       // check the print function when only insert is provoked.
}




/* member function for node */

// initialize each node
template<class T> Node<T>::Node(T n, People* newperson)
{
    person = newperson;
    if (newperson != NULL)
    {
        person->key_weight = compute_key();
    }
    degree = 0;     // no child yet
    ifmark = false; // unmarked
    parent = NULL;  // no parent yet
    child = NULL;   // no child yet
    left = this;    // both point to itself
    right = this;

}

// mark one node
template<class T> void Node<T>::mark(void)
{
    ifmark = true;
}

// unmark one node
template<class T> void Node<T>::unmark(void)
{
    ifmark = false;
}

// delete the last child of a node
template<class T> void Node<T>::clear_child(void)
{
    child = NULL;
    degree = 0;
}

// return the address of the left node
template<class T> Node<T>* Node<T>::get_left(void)
{
    return left;
}

// return the address of the right node
template<class T> Node<T>* Node<T>::get_right(void)
{
    return right;
}

// return the address of the child node
template<class T> Node<T>* Node<T>::get_child(void)
{
    return child;
}

// return the address of the parent node
template<class T> Node<T>* Node<T>::get_parent(void)
{
    return parent;
}

// link node to the left
template<class T> void Node<T>::set_left(Node<T> *pt)
{
    left = pt;
}

// link node to the right
template<class T> void Node<T>::set_right(Node<T> *pt)
{
    right = pt;
}

// link node to the parent 
template<class T> void Node<T>::set_parent(Node<T> *pt)
{
    parent = pt;
}

// set the pointer to its child
template<class T> void Node<T>::set_child(Node<T> *pt)
{
    child = pt;
}

// add a child to a node
template<class T> void Node<T>::add_child(Node<T> *pt)
{
    pt->unmark();
    if (child == NULL)      // if no child exist yet, initial one
    {
        child = pt;
        pt->set_right(pt);
        pt->set_left(pt);
        pt->set_parent(this);
    } else                  // if there are some children, add the new one to the list
    {
        child->get_left()->set_right(pt);
        pt->set_left(child->get_left());
        child->set_left(pt);
        pt->set_right(child);
        pt->set_parent(this);
    }
    degree++;
}

// return the degree of the node
template<class T> int Node<T>::get_degree(void)
{
    return degree;
}


// recursively print children, grand children, grand grand children ...
template<class T> void Node<T>::_print_people_child(int layer)
{
    int each_layer = layer;
    Node<T>* new_pt = child;
    for (int j =0; j<degree;j++)
    {
        cout<<"\n";
        for (int i = 0; i<each_layer-1 ; i++)
        {
            cout << "|         ";
        } 
        if (j == 0)
        {
            cout << "|---------";
        } else
        {
            cout << "|         ";
        }
        string value = new_pt->person->firstname;
        //cout<<"["<<left->person->id_number<<"]";
        cout<<"("<<new_pt->person->id_number<<")";

        if (new_pt->ifmark == true)
        {
            cout << "^";    // "^" means marked
        }
        //cout<<"["<<right->person->id_number<<"]";

        cout<<"\t";
        if (new_pt->degree !=0)
        {
            //cout<<"(";
            new_pt->_print_people_child(each_layer+1);
            //cout<<")";
        }
        new_pt = new_pt->get_right();
        //cout<<"\n |";
    }  
}



/* member function for fheap */

// initializ the heap
template<class T> Fheap<T>::Fheap(void)
{  
    root_node = 0;
    total_node = 0;

    // initialize the hash table
    vector< pair< Node<T>*, T > > a;
    for (int i=0; i<10; i++)
    {
        hash_table.push_back(a);
    }
}

// ---------people---------
// insert a new node to the left of a position on root

template<class T> int Fheap<T>::people_num()
{
    return total_node;
}


template<class T> void Fheap<T>::insert_people(Node<T>* pt,Node<T>* pos)
{
    // calculate the hash value and push this node into a list
    if (pt == NULL) cout << "NULL exists.\n";
    int index = (pt->person->id_number) %10;
    pt->person->leave = 0;  // 0 denotes it is in heap
    hash_table[index].push_back(make_pair(pt,pt->person->id_number));

    if (root_node == 0)           // add it as the min node if the root is empty
    {
        min_node = pt;
        pt->set_left(pt);
        pt->set_right(pt);
    } else if (pos == NULL)
    {
        cout<< "ERROR(when insert): Invalid position"<< endl;
        return;
    } else
    {
        
        Node<T>* temp_pt = pos->get_left();
        pos->set_left(pt);
        temp_pt->set_right(pt);
        pt->set_right(pos);
        pt->set_left(temp_pt);
        pt->set_parent(NULL);   // make sure it has no parent as it is on the root
    }
    root_node ++;
    total_node++;


    if(pt->person->key_weight < min_node->person->key_weight)
    {
        min_node = pt;
    }
}


// find the pointer to a node according to the person's id
template<class T> Node<T> *Fheap<T>::_find_handle_people(int id)
{
    // use hash to find the handle of one node through its id
    int index = id % 10;
    for (int i=0; i<(int)hash_table[index].size(); i++)
    {
        if (hash_table[index][i].second == id)
        {
            return hash_table[index][i].first;
        }
    }
    return NULL;
}

// --- function from people----
template<class T> void Fheap<T>::decrease_trap()
{
    for (int i = 0; i < (int)hash_table.size(); i++) {
        for (int j = 0; j < (int) hash_table[i].size(); j++) {
            if (hash_table[i][j].first != NULL && hash_table[i][j].first->person->risk == 2) {
                if (hash_table[i][j].first->person->trapped > 0) {
                    hash_table[i][j].first->person->trapped--;
                }
            }
        }
    }
}
template<class T> void Fheap<T>::print_heap_people(void)
{
    if (root_node == 0)
    {
        cout<<"The heap is empty"<<endl;
        return;
    }
    //int test;
    cout<<"The heap has "<<root_node<<" nodes on root"<<endl;
    cout<<"The heap has "<<total_node<<" nodes"<<endl;
    Node<T>* pt = min_node;
    cout<< "The root nodes are: "<<endl;
    for (int i=0; i<root_node; i++)
    {
        string first_name = pt->person->firstname;
        //cout<<"("<<pt->get_left()->person->firstname<<")  ";
        cout<<"("<<pt->person->id_number<<")";
        if (pt->ifmark == true)
        {
            cout << "*";
        }
        //cout<<"("<<pt->get_right()->person->firstname<<")\t";
        int child_num = pt->get_degree();
        //cout<<"Which has "<<pt->get_degree()<<" childs";
        //cin>>test;

        int layer = 0;
        if (child_num != 0)
        {
            layer++;
            //cout<<"\n";
            pt->_print_people_child(layer);     
        }
        cout<<endl;
        pt = pt->get_right();
    }
}

//-----------people-----------
// Loop through the root to update the min node
template<class T> void Fheap<T>::_update_min_people(void)
{
    T min = min_node->person->key_weight;
    Node<T>* pt = min_node;
    for (int i=0; i<root_node; i++)
    {
        T unit_value = pt->person->key_weight;
        if (unit_value < min)
        {
            min_node = pt;
            min = pt->person->key_weight;
        }
        pt = pt->get_right();
    }
}

// Return the pointer of the min node
template<class T> Node<T>* Fheap<T>::find_min(void)
{
    return min_node;
}

// Delete one node together with all its children from the root, update the relavant pointer
template<class T> Node<T>* Fheap<T>::pop_node(Node<T>* pt)
{
    if (pt->get_right() == pt)        // Check if it is the last node;
    {
        min_node = NULL;
    } else
    {
        pt->get_left()->set_right(pt->get_right());
        pt->get_right()->set_left(pt->get_left());
    }
    root_node--;
    total_node--;
    pt->set_left(NULL);
    pt->set_right(NULL);
    //pt->person->leave = 1;      // indicate that he left the fib_heap
    return pt;
}


// Make sure all the nodes in the root have different degrees
template<class T> void Fheap<T>::consolidate_people(void)
{   
    if (min_node == NULL)   return;
    int len = 10;                   // assume for each node, there is at most 10 child
    int now = 0;                    // store the number of occupied positions
    Node<T>* length[len];           // build and array with null pointer
    for (int i=0; i<len; i++)
    {
        length[i] = NULL;
    }
    Node<T>* snode = min_node;          // store the node to be checked
    Node<T>* cnode;                     // store the last node that put into the function

    while(now != root_node)             // stop when the number of root nodes equal the number of occupied positions
    {
        do                              // loop till one node is added into the array
        {
            cnode = snode;
            snode = _consolidate_unit_people(length, len, now, snode);
        } while (snode != NULL);
        now++;
        snode = cnode->get_right();     // check next node
    }
    _update_min_people();
}


// help function of consolidate, return the node remains in the root, or NULL for no confliction
template<class T> Node<T>* Fheap<T>::_consolidate_unit_people(Node<T>* checkarray[], int arr_length, int &now, Node<T>* pt)
{
    int num_child = pt->get_degree();   // get the number of child
    if (pt == checkarray[num_child])    // return NULL if the node in array is itself
    {
        return NULL;
    }
    if (num_child >= arr_length)
    {
        cout<< "ERROR(when consolidate): The checking array is overflowed"<<endl;
        return NULL;
    }

    Node<T>* original_node = checkarray[num_child];
    if (original_node != NULL)
    {
        int a = pt->person->key_weight;                   // a is the new node
        int b = original_node->person->key_weight;        // b is the original node
        if (b<a)
        {
            pop_node(pt);                       // pop the larger one from the root
            original_node->add_child(pt);
            total_node++;
            pt->unmark();                       // get unmarked
            checkarray[num_child] = NULL;
            now--;                              // number of occupied positions -1
            if (pt == min_node)
            {
                min_node = original_node;
            }
            return original_node;
        } else
        {
            pop_node(original_node);
            pt->add_child(original_node);
            total_node++;
            original_node->unmark();            // get unmarked
            checkarray[num_child] = NULL;
            now--;
            if (original_node == min_node)
            {
                min_node = pt;
            }
            return pt;
        }
    } else
    {
        checkarray[num_child] = pt;
        return NULL;
    }
}



// delete the min_node, consilidate and find the new min_node
// not sure if it's needed to check the empty case
template<class T> Node<T>* Fheap<T>::pop_people()
{
    if (min_node == NULL)   return NULL;
    if (min_node->person->risk == 2) {
        cout << min_node->person->firstname << " is in Risk 2, Reject.\n";
        return NULL; 
    }
    min_node->person->leave = 1;
    if (root_node == 0)
    {
        cout<<"ERROR(when pop people): No node exists"<<endl;
        return NULL;
    }

    Node<T>* tobepop = min_node;
    Node<T>* pt = min_node->get_child();            // find one child of the min node
    Node<T>* next_min = min_node->get_right();      // get to another node on the root

    if (next_min == min_node && pt==NULL)
    {
        pop_node(min_node);
        return tobepop;
    } else if (next_min == min_node && pt != NULL)
    {
        next_min = pt;
    }

    Node<T>* nextchild;
    int degree = min_node->get_degree();
    min_node->clear_child();                        // clear children of the min node

    if (pt == NULL)                                 // if it has no child, pop it directly
    {
        pop_node(min_node);
    } else
    {
        for (int i=0; i<degree; i++)
        {
            nextchild = pt->get_right();
            total_node--;
            insert_people(pt,min_node);
            pt = nextchild;
        }
        pop_node(min_node);
    }

    min_node = next_min;
    consolidate_people();
    return tobepop;
}


// decrease a person's key weight to k
template<class T> void Fheap<T>::_decrease_people(Node<T>* h, T k)
{
    // if the handle is NULL, return error message
    if (h == NULL)
    {
        cout<<"ERROR: Invalid node handle"<<endl;
        return;
    }

    // check if the input is valid
    int origin_value = h->person->key_weight;
    if (origin_value <= k)
    {
        cout<<"ERROR: The new value should be smaller than the original value"<<origin_value<<endl;
        return;
    }

    // decrease directly if it is on the root, or it is larger than its parent
    if ( h->get_parent() == NULL || h->get_parent()->person->key_weight < k)
    {
        h->person->key_weight = k;
        // for root decrease, update min node
        if(min_node->person->key_weight > k)
        {
            min_node = h;
        }
    } else
    {
        h->person->key_weight = k;
        _cut_and_insert_people(h);
    }
}

template<class T> void Fheap<T>::_cut_and_insert_people(Node<T> *h)
{

        Node<T>* parent = h->get_parent();

        // check if this node is one the root list
        if (parent == NULL)
        {
            h->unmark();
            return;
        }
        h->set_parent(NULL);

        // check if it is the only child of a parent
        if (h->get_right() == h)
        {
            parent->clear_child();
        }else
        {
            parent->set_child(h->get_right());
            parent->degree--;
            h->get_left()->set_right(h->get_right());
            h->get_right()->set_left(h->get_left());
        }

        insert_people(h,min_node);
        total_node--;

        // recursively check the parent, redo the progress when a marked node lose child again
        if (parent->ifmark == true)
        {
            parent->unmark();
            _cut_and_insert_people(parent);
        } else
        {
            parent->mark();
        }
}


// delete one person from the heap through its id
template<class T> People* Fheap<T>::delete_people(int id)
{
    // find the handle of the node
    Node<T>* pt = _find_handle_people(id);
    People* temp = pt->person;
    temp->withdraw = -1;            // indicate his withdraw
    _decrease_people(pt,MIN);       // make it have the highest priority
    pop_people();                   // pop this node
    return temp;
}


//-----------compute priority------------
//  min-heap   less weight higher prority
template<class T> int Node<T>::compute_key(void)
{
    int totlweight_value;                                      
    int letter = (1-person->deadline)*10000000;           // -*******
    int risk_weight = person->risk*1000000;               // *-******
    int profession_weight = person->profession * 100000;  // **-*****
    int age_weight = (7 - person->age.second) * 10000;    // ***-****
    int month = person->register_date.first*100;          // ****--**
    int day = person->register_date.second;               // ******--  

    totlweight_value = risk_weight + profession_weight + age_weight + month + day + letter;
    person->key_weight = totlweight_value;
    return totlweight_value; 
}

template<class T> void Fheap<T>::change_profession(int id, int profession)
{   
    // find the handle of this node through its id
    Node<T>* h = _find_handle_people(id);

    // return error message when h is NULL
    if (h == NULL)
    {
        cout<<"ERROR: Invalid node handle"<<endl;
        return;
    }

    // delete this node, and change its information
    delete_people(id);
    h->person->withdraw = 0; // delete changes the withdraw notation
    cout<<"Profession has been changed from "<<h->person->profession;
    h->person->profession = profession;
    cout<<" to "<<h->person->profession<<endl;
    h->person->key_weight = h->compute_key();

    // reinsert this node with new information
    insert_people(h,min_node);
    cout << "Here613\n";
}

template<class T> void Fheap<T>::change_risk(int id, int risk)
{
    Node<T>* h = _find_handle_people(id);
    if (h == NULL)
    {
        cout<<"ERROR: Invalid node handle"<<endl;
        return;
    }
    if (risk == h->person->risk) {
        cout << "Same risk. Unchange.\n";
        return;
    }
    if (risk == 1 || risk == 3 || risk == 0)  h->person->risk = risk;
    delete_people(id);
    h->person->withdraw = 0; // delete changes the withdraw notation
    cout<<"Profession has been changed from "<<h->person->risk;
    h->person->risk = risk;
    if (risk == 2)  h->person->trapped = 90;
    cout<<" to "<<h->person->risk<<endl;
    h->person->key_weight = h->compute_key();

    insert_people(h,min_node);
}

template<class T> void Fheap<T>::change_letter(int id, int letter_temp)
{
    Node<T>* h = _find_handle_people(id);
    if (h == NULL)
    {
        cout<<"ERROR: Invalid node handle"<<endl;
        return;
    }

    if (h->person->deadline == 1)
    {
        if (letter_temp == 1)
        {
            cout<<"ERROR: He already has a letter"<<endl;
            return;
        }
        h->person->deadline = 0;
        cout<<h->person->firstname<<" applys for a letter successfully!"<<endl;
    } else
    {
        if (letter_temp == 0)
        {
            cout<<"ERROR: There is no letter to give up"<<endl;
            return;
        }
        h->person->deadline = 1;
        cout<<h->person->firstname<<" s' letter is deleted successfully!"<<endl;
    }

    delete_people(id);
    h->person->withdraw = 0;    // delete changes the withdraw notation
    h->person->key_weight = h->compute_key();
    insert_people(h,min_node);
}

//-------------------end--------------