//
//  hashset.cpp
//  
//
//  Created by KD on 6.03.21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "hashset.h"
using std::cout;
using std::cin;
using std::hash;

/* This defines a constructor */
template<class T> hashset<T>::hashset(int size)
{
    maxsize = size;
    if (size < 20)
        maxsize = 20; // default size is 20; no smaller hashtables are considered
    numitems = 0; // initially, the hashtable is empty
    over_num = 0;
    overflow_size = maxsize/2;
    reprarray = new T*[maxsize];  // allocate space for the array of pointers
    overflow = new T*[overflow_size];
    // the for loop initialises all table entries to be undefined
    for (int i = 0; i < maxsize; i++)
    {
        reprarray[i] = 0;
        if (i < overflow_size)  overflow[i] = 0;
    }
    T *pt0 = new T;  // This defines the fixed placeholder pointer
    *pt0 = 0;
    pt_nil = pt0;
}

// template<class T> hashset<T>::~hashset(void)
// {
//     delete[] reprarray;
// }

template<class T> T & hashset<T>::operator[](int index)
{
    if (index <= 0 || index > maxsize)
    {
        cout << "Index error: index out of range\n";
        exit(EXIT_FAILURE);
    }
    if (reprarray[index - 1] != 0 && reprarray[index - 1] != pt_nil)
        return *reprarray[index - 1];
    else
    {
        cout << "Index not used in hashtable";
        return 0;
    }
}

template<class T> void hashset<T>::add(T item)
{
    hash<T> hashfunction; // use the predefined hashfunction to get "key" values
    int index;
    index = hashfunction(item) % maxsize; // First determine the position index in the hash table, where the new value is stored, if free.
    int location = -1;  // used to distinguish between undefined entries (null pointer) and placeholders
    while (reprarray[index] != 0) // We first check, if the item is already in the hashtable
    {
        if (reprarray[index] != pt_nil && *reprarray[index] == item)
            return;   // item found; no insertion
        if (location < 0 && reprarray[index] == pt_nil) // a placeholder object is found; i.e. if the item is not in the hashtable, this will be the place for the insertion
            location = index;
        index = (index + 1) % maxsize;
    }
    // after leaving the while loop we either have location < 1, i.e. we store the item at the last examined index (which contains a null pointer),
    // otherwise, if location >= 0 holds, we found a placeholder, so the item will be stored at the location of this placeholder
    if (location < 0)
        location = index;
    T *pt = new T;
    *pt = item;
    reprarray[location] = pt;   // store item in the hashtable
    ++ numitems;
    int load = 100 * numitems / maxsize;
    if (load >= 75)             // max load factor is exceeded; double the size
    {
        int newsize = 2 * numitems;
        rehash(newsize);
    }
    return;
}

template<class T> void hashset<T>::remove(T item)
{
    hash<T> hashfunction;  // use again the predefined hashfunction
    int index;
    index = hashfunction(item) % maxsize;
    while (reprarray[index] != 0)  // same as for add we search for item in the hashtable; the search starts at the designated hash value, and stops when we find a null pointer
    {
        if (reprarray[index] != pt_nil && *reprarray[index] == item)
                    // item found
        {
            int nextindex = (index + 1) % maxsize;
            /* check the next entry, if it is a null pointer; if yes, we can overwrite item by a null pointer; otherwise we use a placeholder, i.e. the pointer pt_nil */
            if (reprarray[nextindex] == 0)
                reprarray[index] = 0;
            else
                reprarray[index] = pt_nil;
            --numitems;
            int load = 100 * numitems / maxsize;
            if (load <= 25)
                // if the min load factor is undershot, we shrink the hashtable, but the size shall always be >= 20
            {
                int newsize = numitems;
                if (newsize < 20)
                    newsize = 20;
                rehash(newsize);
            }
            return;
        }
        index = (index + 1) % maxsize;
    }
    cout << item << " is not in the hashtable.\n";
    return;
}

template<class T> bool hashset<T>::member(T item)
{
    hash<T> hashfunction;  // use the "key" function for the type T (if defined)
    int index;
    index = hashfunction(item) % maxsize;
    while (reprarray[index] != 0) // again we search for item starting from the index position until we find a null pointer
    {
        if (reprarray[index] != pt_nil && *reprarray[index] == item)
            return true;  // item was found
        index = (index + 1) % maxsize;
    }
    return false;  // a null pointer was found, so item is not in the hashtable
}

template<class T> void hashset<T>::rehash(int newsize)
{
    if (newsize < 20)
        newsize = 20;
    int newnum = 0;
    int new_overflowsize = newsize/2;
    T **newarray = new T*[newsize];   // allocate space for a new hashtable of the given new size
    T **newoverflow = new T*[new_overflowsize];

    for (int i = 0; i < newsize; i++)
    {
        if (i < new_overflowsize)   newoverflow[i] = 0;
        newarray[i] = 0;   // initialise the new hashtable with only null pointers
    }
    
    for (int i = 0; i < maxsize + overflow_size; i++)  // we need to copy all existing entries to the new hash table
    {
        // first we rehash the elements in the hashtable
        if (i < maxsize && reprarray[i] != 0 && reprarray[i] != pt_nil) {
            T item = *reprarray[i];
            hash<T> hashfunction;
            int index = hashfunction(item) % newsize;
                // recompute the new hash value
            while (index < newsize && newarray[index] != 0) // find the first free place, where the entry can be stored in the new hashtable
                index = (index + 1);
            
            // if the item needs to be stored in the overflow space
            if (index >= newsize) {
                index = 0;
                while (index < new_overflowsize && newoverflow[index] != 0) {
                    index++;
                } newoverflow[index] = reprarray[i];
            } else {
                newarray[index] = reprarray[i];  // do the actual copying
            } ++newnum;
        // then we rehash the elements in the original overflow space
        } else if (i >= maxsize && overflow[i-maxsize] != 0 && overflow[i-maxsize] != pt_nil) {
            int o_id = i-maxsize;
            T temp = *overflow[o_id];
            hash<T> hashfunc;
            int index = hashfunc(temp) % newsize;

            while (index < newsize && newarray[index] != 0) 
                index++;
            if (index >= newsize) {
                index = 0;
                while (index < new_overflowsize && newoverflow[index] != 0) {
                    index++;
                } newoverflow[index] = overflow[o_id];
            } else {
                newarray[index] = overflow[o_id];
            } ++newnum;
        }
    }

    numitems = newnum;   // change the number of stored elements
    reprarray = newarray;   // make the new hashtable the one of the hashset object
    maxsize = newsize;   // update the size
    overflow_size = new_overflowsize;
    overflow = newoverflow;

    // Overflow space rehash
}

template<class T> void hashset<T>::display(void) // only for test purposes
{
    cout << "The size of the hashtable is: " << maxsize << "\n";
    cout << "The size of the overflow space is: " << overflow_size << "\n";
    cout << "The number of elements in the hashtable is: " << numitems << "\n";
    cout << "[ ";
    for (int i = 0; i < maxsize; ++i) {
        
        if (reprarray[i] == 0)
            cout << "N ";
        else if (reprarray[i] == pt_nil)
            cout << "P ";
        else
            cout << *reprarray[i] << " ";
    } cout << "] <:::> ";

    cout << "[ ";
    for (int i = 0; i < overflow_size; ++i) {
        
        if (overflow[i] == 0)
            cout << "N ";
        else if (overflow[i] == pt_nil)
            cout << "P ";
        else
            cout << *overflow[i] << " ";
    } cout << "] \n";
    
    return;
}





//**************************************************************************
// Below are the modified function for Ex1.ii



template<class T> void hashset<T>::add_modified(T item)
{
    hash<T> hashfunction; // use the predefined hashfunction to get "key" values
    int index;
    index = hashfunction(item) % maxsize; // First determine the position index in the hash table, where the new value is stored, if free.
    int location = -1;  // used to distinguish between undefined entries (null pointer) and placeholders
    int extend_space = 0, extend = maxsize/2;

    while (reprarray[index] != 0) // We first check, if the item is already in the hashtable
    {
        if (reprarray[index] != pt_nil && *reprarray[index] == item)
            return;   // item found; no insertion
        if (location < 0 && reprarray[index] == pt_nil) // a placeholder object is found; i.e. if the item is not in the hashtable, this will be the place for the insertion
            location = index;
        index = index + 1;
        if (index >= maxsize) {
            extend_space = 1;
            break;
        }
    }
    // after leaving the while loop we either have location < 1, i.e. we store the item at the last examined index (which contains a null pointer),
    // otherwise, if location >= 0 holds, we found a placeholder, so the item will be stored at the location of this placeholder
    if (location < 0 && extend_space == 0)
        location = index;
    if (location < 0 && extend_space == 1) {
        index = 0;
        while (index < overflow_size && overflow[index] != 0) {
            if (overflow[index] != pt_nil && *overflow[index] == item)
                return;
            if (location < 0 && overflow[index] == pt_nil)
                location = index;
            index = index + 1;
        }
        if (location < 0)   location = index;
        if (location >= overflow_size) {
            cout << "Item: " << item << " inserts fail as Overflow space is FULL\n";
            return;
        }
    }

    
    T *pt = new T;
    *pt = item;
    if (extend_space == 0)
        reprarray[location] = pt;   // store item in the hashtable
    else if (extend_space == 1) {
        overflow[location] = pt;
        over_num++;
    }

    ++ numitems;
    int load = 100 * numitems / (maxsize+overflow_size);
    if (load >= 75)             // max load factor is exceeded; double the size
    {
        int newsize = 2 * maxsize;
        rehash_modified(newsize);
    }
    return;
}


template<class T> void hashset<T>::remove_modified(T item)
{
    hash<T> hashfunction;  // use again the predefined hashfunction
    int index, deleted = 0;
    index = hashfunction(item) % maxsize;
    while (index < maxsize && reprarray[index] != 0)  // same as for add we search for item in the hashtable; the search starts at the designated hash value, and stops when we find a null pointer
    {
        if (reprarray[index] != pt_nil && *reprarray[index] == item)
                    // item found
        {
            int nextindex = (index + 1) % maxsize;
            /* check the next entry, if it is a null pointer; if yes, we can overwrite item by a null pointer; otherwise we use a placeholder, i.e. the pointer pt_nil */
            if (reprarray[nextindex] == 0)
                reprarray[index] = 0;
            else
                reprarray[index] = pt_nil;
            --numitems;
            deleted = 1;
        }
        index = index + 1;
    }
    // search the overflow space for the element
    index = 0;
    while (index < overflow_size && overflow[index] != 0) {
        if (overflow[index] != pt_nil && *overflow[index] == item) {
            int nextid = index + 1;
            if (nextid >= overflow_size || overflow[nextid] == 0)
                overflow[index] = 0;
            else if (nextid < overflow_size && overflow[nextid] != 0)
                overflow[index] = pt_nil;
            numitems--;
            over_num--;
            deleted = 1;
        } index++;
    }

    int load = 100 * numitems / (maxsize+overflow_size);
    if (load <= 25) {// if the min load factor is undershot, we shrink the hashtable, but the size shall always be >= 20
        int newsize = numitems;
        if (newsize < 20)
            newsize = 20;
        rehash_modified(newsize);
    }
    if (!deleted)    cout << item << " is not in the hashtable.\n";
    return;
}


template<class T> bool hashset<T>::member_modified(T item)
{
    hash<T> hashfunction;  // use the "key" function for the type T (if defined)
    int index;
    index = hashfunction(item) % maxsize;

    // first search the hashtable
    while (index < maxsize && reprarray[index] != 0) // again we search for item starting from the index position until we find a null pointer
    {
        if (reprarray[index] != pt_nil && *reprarray[index] == item)
            return true;  // item was found
        index = index + 1;
    }
    // then search for the overflow space 
    index = 0;
    while (index < overflow_size && overflow[index] != 0) {
        if (overflow[index] != pt_nil && *overflow[index] == item)
            return true;
        index++;
    }
    return false;  // a null pointer was found, so item is not in the hashtable

}

template<class T> void hashset<T>::rehash_modified(int newsize)
{
    if (newsize < 20)
        newsize = 20;
    int newnum = 0;
    int new_overflowsize = newsize/2;
    T **newarray = new T*[newsize];   // allocate space for a new hashtable of the given new size
    T **newoverflow = new T*[new_overflowsize];

    for (int i = 0; i < newsize; i++)
    {
        if (i < new_overflowsize)   newoverflow[i] = 0;
        newarray[i] = 0;   // initialise the new hashtable with only null pointers
    }
    
    for (int i = 0; i < maxsize + overflow_size; i++)  // we need to copy all existing entries to the new hash table
    {
        // first we rehash the elements in the hashtable
        if (i < maxsize && reprarray[i] != 0 && reprarray[i] != pt_nil) {
            T item = *reprarray[i];
            hash<T> hashfunction;
            int index = hashfunction(item) % newsize;
                // recompute the new hash value
            while (index < newsize && newarray[index] != 0) // find the first free place, where the entry can be stored in the new hashtable
                index = (index + 1);
            
            // if the item needs to be stored in the overflow space
            if (index >= newsize) {
                index = 0;
                while (index < new_overflowsize && newoverflow[index] != 0) {
                    index++;
                } newoverflow[index] = reprarray[i];
            } else {
                newarray[index] = reprarray[i];  // do the actual copying
            } ++newnum;
        // then we rehash the elements in the original overflow space
        } else if (i >= maxsize && overflow[i-maxsize] != 0 && overflow[i-maxsize] != pt_nil) {
            int o_id = i-maxsize;   // calculate the index in overflow space
            T temp = *overflow[o_id];
            hash<T> hashfunc;
            int index = hashfunc(temp) % newsize;

            while (index < newsize && newarray[index] != 0) 
                index++;    // search for the NULL space in the new hashtable
            // if new hashtable cannot fit in the item, seach for the new overflow space
            if (index >= newsize) {
                index = 0;
                while (index < new_overflowsize && newoverflow[index] != 0) {
                    index++;
                } newoverflow[index] = overflow[o_id];  // copy to new  overflow space
            } else {
                newarray[index] = overflow[o_id];   // copy to new hash table otherwise
            } ++newnum;
        }
    }

    numitems = newnum;   // change the number of stored elements
    reprarray = newarray;   // make the new hashtable the one of the hashset object
    maxsize = newsize;   // update the size
    overflow_size = new_overflowsize;   // update the overflow space info
    overflow = newoverflow;

    // Overflow space rehash
}