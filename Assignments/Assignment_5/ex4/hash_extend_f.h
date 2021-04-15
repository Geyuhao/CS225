#include <stdio.h>
#include <iostream>
#include <cstdlib>

#include "hash_extend.h"
using std::cout;
using std::cin;
using std::hash;
/* Put your implementation here */

template<class T> HashSet_LCFS<T>::HashSet_LCFS(int size)
{
    maxsize = size;
    numitems = 0;
    reprarray = new T*[size];
    for (int i = 0; i < size; i++)
        reprarray[i] = 0;
    
    T *ptr = new T;
    *ptr = 0;
    place_hld = ptr;
}

template<class T> T & HashSet_LCFS<T>::operator[](int index)
{
    if (index < 0 || index >= maxsize){
        cout << "Index error: index out of range\n";
        exit(EXIT_FAILURE);
    }
    if (reprarray[index] != 0 && reprarray[index] != place_hld){
        return *reprarray[index];
    } else {
        cout << "Index not used in hashtable";
        return 0;
    }
}

template<class T> void HashSet_LCFS<T>::insert(T item)
{
    hash<T> hashfunc;
    int index = hashfunc(item) % maxsize;
    
    //cout << index << " ";
    int location = -1;
    T *temp = new T;

    while (reprarray[index] != 0) {
        if (reprarray[index] != place_hld && *reprarray[index] == item)
            return;   // item found; no insertion
        if (location < 0 && reprarray[index] == place_hld) // a placeholder object is found; 
            location = index;
        index = (index + 1) % maxsize;  // loop to next position
    }

    if (location < 0)   location = index;   
    if (location == hashfunc(item)%maxsize) {// if ideal position is NULL
        *temp = item;
        reprarray[location] = temp;
    } else {    // if a place holder is founded
        *temp = *reprarray[hashfunc(item)%maxsize]; // set temp to point to original value
        reprarray[location] = temp;
        T *temp2 = new T;
        *temp2 = item;
        reprarray[hashfunc(item)%maxsize] = temp2;
    } 
    numitems++;
    int load_fac = 100*numitems/maxsize;
    if (load_fac >= 75){
        int newsize = 2*maxsize;
        rehash(newsize);
    } return;
}

template<class T> int HashSet_LCFS<T>::member(T item)
{
    hash<T> hashfunc;
    int index = hashfunc(item) % maxsize;

    while (reprarray[index] != 0) {
        if (reprarray[index] != place_hld && *reprarray[index] == item) {
            return index;
        } else {
            index++;
        }
    }
    return -1;
}

template<class T> void HashSet_LCFS<T>::remove(T item)
{
    int index = member(item);
    if (index == -1) {
        cout << "Item does not exist.\n";
        return;
    } else {
        if (reprarray[(index+1)%maxsize] == 0) {
            reprarray[index] = 0;
            
        } else {
            reprarray[index] = place_hld;
            
        } numitems--;

        int load_fac = 100*numitems/maxsize;
        if (maxsize == 20)  return;
        if (load_fac <= 25) {
            int newsize = numitems;
            rehash(newsize);
        }
    } return;
}

template<class T> void HashSet_LCFS<T>::display()
{
    //cout << numitems;
    cout << "[";
    for (int i = 0; i < maxsize; i++) {
        if (reprarray[i] == 0) cout << "N ";
        else if (reprarray[i] == place_hld) cout << "P ";
        else {cout << *reprarray[i] << " ";}     
    } cout << "]\n";
}

template<class T> void HashSet_LCFS<T>::rehash(int newsize)
{
    
    int newnum = 0;
    if (newsize < 20)   newsize = 20;   // this code must be put before newarray
    T **newarray = new T*[newsize];

    
    for (int i = 0; i < newsize; i++){
        newarray[i] = 0;
    }

    for (int i = 0; i < maxsize; i++) {
        if (reprarray[i] == 0 || reprarray[i] == place_hld)     continue;
        hash<T> hashfunc;
        int index = hashfunc(*reprarray[i]) % newsize;
        T *temp = new T;

        while (newarray[index] != 0) {
            index = (index + 1) % newsize;
        }
        if (index == hashfunc(*reprarray[i]) % newsize) {
            newarray[index] = reprarray[i];
        } else {
            *temp = *newarray[hashfunc(*reprarray[i]) % newsize];
            newarray[index] = temp;
            newarray[hashfunc(*reprarray[i]) % newsize] = reprarray[i];
        }
        newnum++;
    }

    numitems = newnum;
    maxsize = newsize;
    reprarray = newarray;
}














template<class T> HashSet_RH<T>::HashSet_RH(int size)
{
    maxsize = size;
    numitems = 0;
    reprarray = new T*[size];
    for (int i = 0; i < size; i++)
        reprarray[i] = 0;
    
    T *ptr = new T;
    *ptr = 0;
    place_hld = ptr;
}

template<class T> T & HashSet_RH<T>::operator[](int index)
{
    if (index < 0 || index >= maxsize){
        cout << "Index error: index out of range\n";
        exit(EXIT_FAILURE);
    }
    if (reprarray[index] != 0 && reprarray[index] != place_hld){
        return *reprarray[index];
    } else {
        cout << "Index not used in hashtable";
        return 0;
    }
}

template<class T> void HashSet_RH<T>::insert(T item)
{
    hash<T> hashfunc;
    T current = item;       // current stand for the item which is being moved to search for ideal position, it is initially inserted item
    int index = hashfunc(item) % maxsize;

    while (reprarray[index] != 0)  {
        if (reprarray[index] != place_hld && *reprarray[index] == current) {
            return;     // if item already exists, return
        } else if (reprarray[index] != place_hld && *reprarray[index] != current) {   // if ideal position is occupied, apply RH search 
            int compare_c = hashfunc(current) % maxsize - index;   
            int compare_1 = hashfunc(*reprarray[index]) % maxsize - index;

            if (compare_c*compare_c > compare_1*compare_1){     // if current item is further to its ideal position, exchange
                T* temp1 = new T;
                *temp1 = current;   // set temp1's value to current item
                current = *reprarray[index];    // set current item to the closer item in table
                reprarray[index] = temp1;   // set current position's ptr as temp1 i.e. the further item;
            } else {
                index = (index + 1)%maxsize;
                continue;
            }
        } else if (reprarray[index] == place_hld)   break;
    }
    if (reprarray[index] == 0 || reprarray[index] == place_hld)  {
        T *ptr = new T;
        *ptr = current;
        reprarray[index] = ptr;
    } numitems++;

    int load = 100*numitems/maxsize;
    if (load >= 75) {
        int newsize = 2*maxsize;
        rehash(newsize);
    }
}

template<class T> int HashSet_RH<T>::member(T item)
{
    hash<T> hashfunc;
    int index = hashfunc(item) % maxsize;

    while (reprarray[index] != 0) {
        if (reprarray[index] != place_hld && *reprarray[index] == item) {
            return index;
        } else {
            index++;
        }
    }
    return -1;
}

template<class T> void HashSet_RH<T>::remove(T item)
{
    int index = member(item);
    
    if (index == -1) {
        cout << "Item does not exist.\n";
        return;
    } else {
        if (reprarray[(index+1)%maxsize] == 0) {
            reprarray[index] = 0;
        } else {
            reprarray[index] = place_hld;
        } numitems--;

        int load = 100*numitems/maxsize;
        if (maxsize == 20)  return;
        if (load <= 25) {
            int newsize = numitems;
            rehash(newsize);
        }
    } return;
}

template<class T> void HashSet_RH<T>::display()
{
    //cout << numitems;
    cout << "[";
    for (int i = 0; i < maxsize; i++) {
        if (reprarray[i] == 0) cout << "N ";
        else if (reprarray[i] == place_hld) cout << "P ";
        else {cout << *reprarray[i] << " ";}     
    } cout << "]\n";
}

template<class T> void HashSet_RH<T>::rehash(int newsize)
{
    hash<T> hashfunc;
    int newnum = 0;
    if (newsize < 20)   newsize = 20;   // this code must be put before newarray
    T **newarray = new T*[newsize];

    
    for (int i = 0; i < newsize; i++) {
        newarray[i] = 0;
    }

    for (int i = 0; i < maxsize; i++) {
        if (reprarray[i] == 0 || reprarray[i] == place_hld)     continue;
        int index = hashfunc(*reprarray[i])%newsize;
        T current = *reprarray[i];  // item waiting to be inserted
        

        while (newarray[index] != 0) {
            T compare = *newarray[index];   // item already exists
            int compare_c = hashfunc(current)%newsize - index;
            int compare_1 = hashfunc(compare)%newsize - index;

            if (compare_c*compare_c > compare_1*compare_1) {
                T *temp = new T;
                *temp = current;
                current = *newarray[index];
                newarray[index] = temp;
            } else {
                index = (index+1)%newsize;
                continue;
            }
        }
        if (newarray[index] == 0) {
            T *temp = new T;
            *temp = current;
            newarray[index] = temp;
        } newnum++;
    }

    numitems = newnum;
    maxsize = newsize;
    reprarray = newarray;
}
