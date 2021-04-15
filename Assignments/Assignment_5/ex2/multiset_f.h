#include "multiset.h"
#include <iostream>
#include <stdio.h>
#include <cstdlib>
using std::cout;
using std::cin;
using std::endl;
using std::hash;

/* Put your implementation here */
template<class T> MultiSet<T>::MultiSet(int size)
{
    maxsize = size;
    if (size < 20)
        maxsize = 20; // default size is 20; no smaller hashtables are considered
    numitems = 0; // initially, the hashtable is empty
    reprarray = new item_node<T>*[maxsize];  // allocate space for the array of pointers
    // the for loop initialises all table entries to be undefined
    for (int i = 0; i < maxsize; i++)
    {
        reprarray[i] = NULL;
    }
    pt_nil = NULL;
}
template<class T> item_node<T>::item_node(T item)
{
    value = item;
    multiplicity=1;
}
template<class T> ch_node<T>::ch_node(T item)
{
    value = item;
    pointer_next=NULL;
}



template<class T> void MultiSet<T>::insertion(T item)
{
    hash<T> hashfunction; // use the predefined hashfunction to get "key" values
    int index;
    index = hashfunction(item) % maxsize; // First determine the position index in the hash table, where the new value is stored, if free.
    int location = -1;  // used to distinguish between undefined entries (null pointer) and placeholders
    while (reprarray[index] != NULL) // We first check, if the item is already in the hashtable
    {
        if ( (*reprarray[index]).value == item){
            (*(reprarray[index])).multiplicity ++;
            //++numitems;
            return;
        }
        index = (index + 1) % maxsize;
        if (location < 0 && reprarray[index] == NULL) // a placeholder object is found; i.e. if the item is not in the hashtable, this will be the place for the insertion
            location = index;
    }
    // after leaving the while loop we either have location < 1, i.e. we store the item at the last examined index (which contains a null pointer),
    // otherwise, if location >= 0 holds, we found a placeholder, so the item will be stored at the location of this placeholder
    if (location < 0)
        location = index;
    item_node<T> *pt = new item_node<T>(item);
    //(*pt).value = item;
    //(*pt).multiplicity=1;
    reprarray[location] = pt;   // store item in the hashtable
    ++numitems;
    // calculate the load factor to determine if rehash is needed;
    int load = 100*numitems/maxsize;
    if (load >= 75) {
        int newsize = maxsize*2;
        rehash(newsize);
    }
    return;
}

template<class T> void MultiSet<T>::deletion(T item)
{
    hash<T> hashfunction;  // use again the predefined hashfunction
    int index;
    index = hashfunction(item) % maxsize;
    while (reprarray[index] != NULL)  // same as for add we search for item in the hashtable; the search starts at the designated hash value, and stops when we find a null pointer
    {
        if (reprarray[index] != NULL && (*reprarray[index]).value == item)
                    // item found
        {
            if (reprarray[index]->multiplicity >= 2 ){
                --(reprarray[index])->multiplicity;
                return;
            }else{
                reprarray[index] = NULL;
                --numitems;

                int load = 100*numitems/maxsize;
                if (load <= 25){
                    int newsize = numitems;
                    rehash(newsize);
                } return;
            }
        }
    }
    cout << item << " is not in the hashtable.\n";
    return;

}
template<class T> void MultiSet<T>::rehash(int newsize)
{

    int newnum = 0;
    if (newsize < 20)   newsize = 20;
    item_node<T> **newarray = new item_node<T>*[newsize];   // allocate space for a new hashtable of the given new size


    for (int i = 0; i < newsize; i++)
    {
        newarray[i] = NULL;   // initialise the new hashtable with only null pointers
    }
    for (int i = 0; i < maxsize; i++)  // we need to copy all existing entries to the new hash table
    {
        if (reprarray[i] != NULL)
        {
            item_node<T> *item = reprarray[i];
            hash<T> hashfunction;
            int index = hashfunction(item->value) % newsize;
                // recompute the new hash value
            while (newarray[index] != 0)  // find the first free place, where the entry can be stored in the new hashtable
            {
                index = (index + 1) % newsize;
            }
            newarray[index] = reprarray[i];  // do the actual copying
        }
        newnum++;
    }
    maxsize = newsize;
    numitems = newnum;
    reprarray = newarray;   // make the new hashtable the one of the hashset object
}

template<class T> item_node<T>* MultiSet<T>::retrieval(T item)
{
    hash<T> hashfunction;  // use the "key" function for the type T (if defined)
    int index;
    index = hashfunction(item) % maxsize;
    while (reprarray[index] != NULL) // again we search for item starting from the index position until we find a null pointer
    {
        if (reprarray[index] != NULL && (*reprarray[index]).value == item)
            return (reprarray[index]);  // item was found
        index = (index + 1) % maxsize;
    }
    cout << item << " is not in the hashtable.\n";
    return NULL;
}


template<class T> void MultiSet<T>::setunion(MultiSet<T> sets)
{
    for (int i = 0; i < sets.maxsize; i++){
        if ((sets.reprarray[i]) != NULL){
            item_node<T> *temp = sets.reprarray[i];
            for (int i = 0; i < temp->multiplicity; i++)
                insertion(temp->value);
        }
    }
    return;
}


template<class T> void MultiSet<T>::intersection(MultiSet<T> sets)
{
    MultiSet<T> newset = 20;

    for (int i = 0; i < sets.maxsize; i++) {
        for (int j = 0; j < maxsize; j++) {
            if ( reprarray[j] != NULL && sets.reprarray[i] != NULL && reprarray[j]->value == sets.reprarray[i]->value ){
                newset.insertion(reprarray[j]->value);
            }
        }
    }

    cout << "[";
    for (int i = 0; i < newset.maxsize; i++) {
        item_node<T> *temp = newset.reprarray[i];
        if (temp == NULL)   continue;
        cout << temp->value << " ";
    } cout << "]\n";

}

template<class T> MultiSet<T> MultiSet<T>::difference(MultiSet<T> sets)
{
    MultiSet<T> newset = 20;

    for (int i = 0; i < sets.maxsize; i++) {
        for (int j = 0; j < maxsize; j++) {
            if ( reprarray[j] != NULL && sets.reprarray[i] != NULL && reprarray[j]->value == sets.reprarray[i]->value ){
                item_node<T> *temp1 = sets.reprarray[i];
                item_node<T> *temp2 = reprarray[j];
                if (temp1->multiplicity == temp2->multiplicity) continue;
                else if (temp1->multiplicity > temp2->multiplicity) {
                    for (int k = 0; k < temp1->multiplicity-temp2->multiplicity; k++) {
                        newset.insertion(temp1->value);
                    }
                } else {
                    for (int k = 0; k < temp2->multiplicity-temp1->multiplicity; k++) {
                        newset.insertion(temp1->value);
                    }
                }
            }
        } 
        
    }

    for (int i = 0; i < newset.maxsize; i++) {
        item_node<T> *temp = newset.reprarray[i];
        if (temp == NULL)   continue;
    } 
    
    return newset;
}


template<class T> void MultiSet<T>::display(void) // only for test purposes
{
    //cout << "The size of the hashtable is: " << maxsize << "\n";
    //cout << "The number of elements in the hashtable is: " << numitems << "\n";
    cout<<"Item : Multiplicity"<<endl;
    for (int i = 0; i < maxsize; ++i)
    {
        if (reprarray[i] == NULL)
            ;
        else{
            cout <<"("<<(*(reprarray[i])).value<<" : "<< (*(reprarray[i])).multiplicity<<")  ";
        }
    }
    cout<<endl;
    return;
}































//***********************************************************************


template<class T> MultiSet_Chaining<T>::MultiSet_Chaining(int size)
{
    maxsize = size;
    if (size < 20)
        maxsize = 20; // default size is 20; no smaller hashtables are considered
    numitems = 0; // initially, the hashtable is empty
    reprarray = new ch_node<T>*[maxsize];  // allocate space for the array of pointers
    // the for loop initialises all table entries to be undefined
    for (int i = 0; i < maxsize; i++)
    {
        reprarray[i] = NULL;
    }    
}


template<class T> void MultiSet_Chaining<T>::insertion(T item)
{
    hash<T> hashfunction;
    int index;
    index = hashfunction(item) % maxsize;
    ch_node<T>* new_item = new ch_node<T>(item);

    if (reprarray[index] == NULL){
        reprarray[index] = new_item;
        numitems++;
        return;
    }
    ch_node<T>* node = reprarray[index];
    while(node!=NULL){
        if (node->pointer_next == NULL){
            node->pointer_next=new_item;
            numitems++;
            return;
        }
        if (node->value==item){
            new_item->pointer_next = node->pointer_next;
            node->pointer_next = new_item;
            numitems++;
            return;
        }
        node = node->pointer_next;
    }
    cout<<"insertion bug";      
}

template<class T> void MultiSet_Chaining<T>::deletion(T item)
{
    hash<T> hashfunction;
    int index;
    index = hashfunction(item) % maxsize;
    if (reprarray[index] == NULL){
        cout<<item<<" is not in the hashtable";
        return;
    }
    ch_node<T>* node = reprarray[index];
    if (node->value==item){
        reprarray[index]= node->pointer_next;
        numitems--;
        return;
    }
    while(node!=NULL){
        if ( node->pointer_next != NULL && (node->pointer_next)->value==item){
            (node->pointer_next) = (node->pointer_next)->pointer_next;
            numitems--;
            return;
        }
        node=node->pointer_next;
    }
    cout<<item<<" is not in the hashtable";
    return;
}

template<class T> T MultiSet_Chaining<T>::retrieval(T item)
{
    hash<T> hashfunction;
    int index;
    index = hashfunction(item) % maxsize;
    ch_node<T>* node = reprarray[index];
    int count=0;
    while (node!=NULL){
        if (node->value==item){
            count++;            
        }
        node=node->pointer_next;
    }    
    return count;
}


template<class T> void MultiSet_Chaining<T>::display_chaining(void) // only for test purposes
{
    for (int i = 0; i < maxsize; ++i)
    {
        if (reprarray[i] == NULL){
        }
        else{
            cout << "The entry " << i + 1 << " is ";
            ch_node<T>* node = reprarray[i];
            while(node != NULL){
                cout << node->value<<" ";
                node=node->pointer_next;
            }
            cout<<"\n";

        }
    }
    return;
}

template<class T> void MultiSet_Chaining<T>::setunion(MultiSet_Chaining<T> sets)
{
    for (int i=0; i<maxsize; i++ ){
        if (reprarray[i]==NULL){
            if (sets.reprarray[i]==NULL){
                continue;
            }else{
                ch_node<T>* node2 = sets.reprarray[i];
                while (node2 != NULL){
                    insertion(node2->value);
                    node2=node2->pointer_next;
                }
            }
        }
        if (reprarray[i]!=NULL && sets.reprarray[i]==NULL){
            continue;
        }

        ch_node<T>* node = reprarray[i];
        while (node != NULL){
            int count1 = retrieval(node->value);                          
            int count2 = sets.retrieval(node->value);
            if (count1 < count2){
                for (int i =0; i <count2-count1; i++){
                    //insertion(node->value);
                }
            }

            if (count2>0){
                for (int i = 0; i<count2; i++ ){
                    sets.deletion(node->value);
                }
            }

            for ( int i = 0; i< count1;i++){
                node = node->pointer_next;
            }
        }
        ch_node<T>* node4= sets.reprarray[i];
        while (node4!=NULL){
            insertion(node4->value);
            node4 = node4->pointer_next;
        }
    }
    return;
}

template<class T> void MultiSet_Chaining<T>::intersection(MultiSet_Chaining<T> sets)
{
    for (int i = 0 ; i < maxsize; i++)
    {
        if (reprarray[i]== NULL)
        {
            continue;
        }
        else
        {
            ch_node<T>* temp = reprarray[i];
            do{
                T val = temp -> value;
                int times = retrieval(val);
                int times2 = sets.retrieval(val);
                for (int m=0; m<times; m++)
                {
                    temp = temp->pointer_next;
                }

                if (times2 < times)
                {
                    for (int m=0; m<times-times2; m++)
                    {
                        deletion(val);
                    }
                }
            } while(temp != NULL);
        }
    }
}


template<class T> void MultiSet_Chaining<T>::difference(MultiSet_Chaining<T> sets)
{
    for (int i=0; i<maxsize; i++)
    {
        if(reprarray[i] != NULL && sets.reprarray[i] != NULL)
        {
            ch_node<T>* temp = reprarray[i];
            do{
                T val = temp->value;
                int times = retrieval(val);
                int times2 = sets.retrieval(val);

                for (int m=0; m<times; m++)
                {
                    temp = temp->pointer_next;
                }

                if (times2 < times)
                {
                    for (int m=0; m<times2; m++)
                    {
                        deletion(val);
                    }
                } else
                {
                    times2 = times;
                    for (int m=0; m<times2; m++)
                    {
                        deletion(val);
                    }
                }
                times = retrieval(val);
            } while(temp != NULL) ;
        }
    }
}