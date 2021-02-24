//
//  alist.cpp
//  
//
//  Created by KD on 14.01.21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "alist.h"
using std::cout;
using std::cin;

// Function implementation for HW1 Q1.2
/*
 * delete_last
 * INPUT: num
 * OUTPUT: numitem>0
 * Description: member function which used to delete the 
 *              elements at the last of the AList
 */
template<class T> int AList<T>::delete_last(int num) 
{
    if ((numitems - num == maxsize/4) && (maxsize > minsize)) {
        deallocate();
    }
    if (num <= numitems && num >=1) {
        numitems -= num;
        cout << "current numitems are " << numitems << "\n";
    } 
    return (numitems>0);
}

// Function implementation for HW1 Q2.4
/*
 * strstructural_recursion
 * INPUT: AList<T> list
 * OUTPUT: sum of the list
 * Description: member function of class SRC which use recursion to 
 *              calculate the sum of AList
 */

template<class T> T SRC<T>::strcutural_recursion(AList<T> list)
{
    AList<T> sub_list1 = list.getlength()/2;    
    AList<T> sub_list2 = list.getlength() - list.getlength()/2;
    T val1, val2;   // the target value
    if (list.getlength() == 0)  {return e;}     // if current list is empty, return e
    if (list.getlength() == 1)  {return func_f(list);}  // if current list is singleton, excute function f
    else {  // else, excute function g
        for (int i = 1; i <= list.getlength(); i++) {// divide into two sublists
            if (i <= list.getlength()/2)    sub_list1.append(list.getitem(i));
            else    sub_list2.append(list.getitem(i));
        }
        // excute the recursion for two individual sublists
        val1 = strcutural_recursion(sub_list1);
        val2 = strcutural_recursion(sub_list2);
        return func_g(val1, val2);
    }
}


template<class T> 
T SRC<T>::func_f(AList<T> list)
{
    if (list.getlength() == 1)  return list.getitem(1);
    return 0;
}

template<class T> 
T SRC<T>::func_g(T val1, T val2)
{
    return val1 + val2;
}

template<class T> void AList<T>::gen_rand(int length)
{
    numitems = 0;
    for (int i = 0; i < length; i++)
    {
        T val = i;
        append((val*val*21+1000)/(length+val));
    }
}
//*************HW1 Q2.4 end******************

//************* HW1 Q3 **********************
template<class T> void AList<T>::pushback(T value)
{
    //check if the queue is full
    if ((rear+1) % maxsize == front){
        allocate();
    }
    reprarray[rear]=value;
    rear = (rear+1) % maxsize;      //the rear should move to next position  
    ++numitems;
    return;
}

template<class T> void AList<T>::pushfront(T value)
{
    if ((rear+1) % maxsize == front){
        allocate();
    }
    front = (front+maxsize-1) % maxsize;    //front moveforward while using mod in case of 0
    reprarray[front]=value;
    ++numitems;
    return;
}

template<class T> T AList<T>::popback(void)
{
    if ((numitems == maxsize / 4) && (maxsize > minsize))       //if too few elements
        deallocate();
    if (rear==front){
        cout << "The list is empty\n";
        exit(EXIT_FAILURE);
    }
    rear = (rear+maxsize-1) % maxsize;      //pointer rear move back to pop
    T value = reprarray[rear];
    --numitems;
    return value;       //return value of pop element

}

template<class T> T AList<T>::popfront(void)
{
    if ((numitems == maxsize / 4) && (maxsize > minsize))
        deallocate();
    if (rear==front){
        cout << "The list is empty\n";      //when list is empty
        exit(EXIT_FAILURE);
    }
    T value = reprarray[front];
    front = (front+1) % maxsize;        //increment front
    --numitems;
    return value;

}

template<class T> void AList<T>::display_q3(void)
{
    int counter = 1;
    for (int i = front; i < front+numitems; ++i)
    {
        T doubleitem = reprarray[i%maxsize];  //display the element in correct order of list
        cout << "List element " << counter << " is " << doubleitem <<".\n";
        counter++;
    }
    return;
}
//****************** HW1 Q3.2 END ********************


//****************** HW1 Q4 **************************
template<class T> void AList<T>::insertionsort(void)
{
    int length = numitems;
    int temparray[length];

    for (int j = 0; j<length; j++)
    {
        // copy each item from the array and remove it
        temparray[j] = reprarray[0];
        remove(1);
    }

    for (int i = 0; i<length; i++)
    {
        int find = temparray[i];
        int start = 0;
        int mid = 0;
        int end = numitems-1;
        int index = 0;

        if (end == -1){
            insert(1,find);
        }
        while(start <= end)
        {
            if (start >= end-1){
                if (find>reprarray[start] && find<reprarray[end]){
                    insert(end,find);
                    break;
                } else if(find<=reprarray[start]){
                    insert(start,find);
                    break;
                } else{
                    insert(end+1,find);
                    break;
                }
            }
            mid = (start+end)/2;
            if (find < reprarray[mid]){
                end = mid;
            } else if (find > reprarray[mid]){
                start = mid;
            } else{
                insert(mid+1,find);
                break;
            }
        }
    }
    display_q4();
} 



template<class T> void AList<T>::selectionsort(void)
{
    int length = numitems;
    // find the minimum number
    for (int j = 0; j<length; j++)
    {
        //cout << "selet the " << j << "th \n";
        int min = 100000;
        int min_index = -1;
        for (int i = 1; i <= length-j; i++)
        {
            int newitem = reprarray[i-1];
            if (newitem < min){
                min = newitem;
                min_index = i;
            }
        }
        //cout << "The min index is " << min_index << "\n";
        remove(min_index);
        append(min);
    }
    display_q4();
}

template<class T> void AList<T>::bubblesort(void)
{
    int length = numitems;
    bool sorted = false;
    while (sorted != true)
    {
        int count=0;
        for (int i = 0; i<length-1;i++)
        {
            int temp;
            if (reprarray[i] > reprarray[i+1]){
                temp = reprarray[i];
                reprarray[i] = reprarray[i+1];
                reprarray[i+1] = temp;
                count++;
            }
        }
        if (count == 0){
            sorted = true;
        }
    }
    display_q4();
}

template<class T> void AList<T>::display_q4(void)
{
    if (numitems == 0)
    {
        cout << "The list is empty\n";
        return;
    }
    cout << "The list is: ";
    for (int i = 1; i <= numitems;i++)
    {
        cout << getitem(i) << " ";
    }
    cout << "\n";
}

template<class T> void AList<T>::gen_rand(void)
{
    for (int i = 1; i <= maxsize; i++)
    {
        append((i*i*21+1000)%99);
    }
    display_q4();
}
// **************** HW1 Q4 END ********************



template<class T> T &AList<T>::operator[](int index)
{
    return reprarray[index - 1];
}

template<class T> int AList<T>::getlength(void)
{
    return numitems;
}

template<class T> void AList<T>::setitem(int index, T value)
{
    if ((index > 0) && (index <= numitems))
    {
        reprarray[index - 1] = value;
        return;
    }
    else
        cout << "Index error: index out or range\n";
}

template<class T> T AList<T>::getitem(int index)
{
    if ((index > 0) && (index <= numitems))
    {
        return reprarray[index - 1];
    }
    else
    {
        cout << "Index error: index out or range\n";
        exit(EXIT_FAILURE);
    }
}

template<class T> void AList<T>::append(T value)
{
    if (numitems == maxsize)
        allocate();
    reprarray[numitems] = value;
    ++numitems;
    return;
}

template<class T> void AList<T>::insert(int index, T value)
{
    if (numitems == maxsize)
        allocate();
    if (index < numitems)
    {
        for (int j = numitems - 1; j >= index; --j)
        {
            reprarray[j+1] = reprarray[j];
        }
        reprarray[index] = value;
        ++numitems;
        return;
    }
    else
    {
        append(value);
        return;
    }
}

template<class T> void AList<T>::allocate(void)
{
    int newsize = 2 * maxsize;
    T *newarray = new T[newsize];
    for (int i = 0; i < numitems; ++i)
    {
        newarray[i] = reprarray[i];
    }
    delete[] reprarray;
    reprarray = newarray;
    maxsize = newsize;
    return;
}

template<class T> void AList<T>::remove(int index)
{
    if ((numitems == maxsize / 4) && (maxsize > minsize))
        deallocate();
    if (index <= numitems)
    {
        for (int j = index; j < numitems; ++j)
        {
            reprarray[j-1] = reprarray[j];
        }
        --numitems;
        return;
    }
    else
        cout << "Index error: list index out of range\n";
}

template<class T> void AList<T>::deallocate(void)
{
    int newsize = maxsize / 2;
    T *newarray = new T[newsize];
    for (int i = 0; i < numitems; ++i)
    {
        newarray[i] = reprarray[i];
    }
    delete[] reprarray;
    reprarray = newarray;
    maxsize = newsize;
    return;
}

template<class T> void AList<T>::concat(AList<T> &list)
{
    int length = list.getlength();
    for (int i = 1; i <= length; ++i)
    {
        append(list[i]);
    }
    return;
}

template<class T> bool AList<T>::member(T value)
{
    bool result = false;
    for (int i = 0; i < numitems; ++i)
    {
        if (reprarray[i] == value)
        {
            result = true;
            break;
        }
    }
    return result;
}

template<class T> bool AList<T>::equal(AList<T> &list)
{
    bool result = true;
    if (numitems == list.getlength())
    {
        for (int i = 0; i < numitems; ++i)
        {
            if (reprarray[i] == list[i + 1])
                continue;
            else
            {
                result = false;
                break;
            }
        }
    }
    else
        result = false;
    return result;
}

template<class T> bool AList<T>::sublist(AList<T> &list)
{
    int length = list.getlength();
    bool result = true;
    for (int i = 1, j = 0; (i <= length) && (j < numitems); ++i, ++j)
    {
        if (list[i] == reprarray[j])
        {
            if ((j == numitems - 1) && (i < length))
            {
                result = false;
                break;
            }
        }
        else
            if (j == numitems - 1)
            {
                result = false;
                break;
            }
            else
                --i;
    }
    return result;
}

