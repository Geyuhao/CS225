#ifndef fibo_heap
#define fibo_heap

#include <vector>
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <queue>
#include "1_read_file_func.cpp"

using namespace::std;



// This class represents a node in the fibonacci heap
template<class T> class Node
{
public:
    // ------basic function for each node------
    Node(T n, People* newperson = NULL);
    People* person;             // pointer to class People which contains people's basic information

    void mark(void);
    void unmark(void);
    void set_left(Node<T> *pt);
    void set_right(Node<T> *pt);
    void set_parent(Node<T> *pt);
    void set_child(Node<T> *pt);
    void clear_child(void);
    void add_child(Node<T> *pt);
    void _print_people_child(int layer);  // help function for the function "print_heap_people" in Fheap

    int get_degree(void);
    int compute_key(void);          // compute a key for People according to its information

    Node<T>* get_left(void);        // return the pointer to the left node
    Node<T>* get_right(void);       // return the pointer to the right node
    Node<T>* get_child(void);       // return the pointer to the child node
    Node<T>* get_parent(void);      // return the pointer to the parent node

    bool ifmark;              // check if it is marked
    int degree;               // store the number of children of a node

private:
    Node<T> *left;          // dlist pointer
    Node<T> *right;
    Node<T> *child;         // point to one of the child
    Node<T> *parent; 
};


// This class is for fibonacci heap, this is a min heap for integer,
// for People class, the people with smallest key weight will have the
// highest piority
template<class T> class Fheap
{
public:
    Fheap(void);
    Node<T>* find_min(void);            // return the pointer to the min node
    void print_heap_people(void);           // display the People's information
    Node<T>* pop_people(void);              // pop the person with highest piority
    void insert_people(Node<T>* pt, Node<T>* pos);  // add a new node to the heap, to the left of the min in root
    void change_profession(int id, int profession);     // change a person's profession
    void change_risk(int id, int risk);                 // change a person's risk
    People* delete_people(int id);             // delete a node through its id
    int people_num();
    Node<T> * _find_handle_people(int id);   // find the pointer to a node through its id
    void change_letter(int id, int letter_temp);

    // from remote gyh, change it to public
    void consolidate_people(void);          // To make sure each root nodes' degrees are different
    void decrease_trap();
private:
    Node<T>* _consolidate_unit_people(Node<T>* checkarray[], int arr_length, int &now,Node<T>* pt);      // help function for consolidate_people
    void _cut_and_insert_people(Node<T>* h); // help function for decrease_people
    void _update_min_people(void);           // update the min value pointer
    void _decrease_people(Node<T>* h,T k);   // decrease a person's keyweight to k through a handle 


    Node<T>* pop_node(Node<T>* pt);     // pop the smallest node

    int root_node;                      // store the number of node in root
    Node<T> *min_node;                  // pointer to the min node
    int total_node;                   
    vector < vector< pair< Node<T>*, T > > > hash_table;

};

void register_in(Fheap<int> &fib, People* person, int day_offset);


#endif