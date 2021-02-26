#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "ex1.h"
using namespace::std;

//-------------member function for HW3 ex1--------------

template<class T> void AList<T>::find_smallest(void)
{
    if (maxsize < 1){
        cout << "invalid length";
        return;
    } 

    int comparison = 0;
    int next_length = numitems/2;
    int remainder = numitems%2;
    int nextsize = next_length+remainder;

    while(nextsize != 1 || next_length == 1 ){
        for (int i=1; i<=nextsize; i++)
        {
            if ((i < nextsize) || (remainder == 0)){
                T left = getitem(i);
                T right = getitem(i+1);
                if (left<right){
                    remove(i+1);
                } else{
                    remove(i);
                }
                comparison ++;    // count the needed times;
            }
        }
        next_length = nextsize/2;
        remainder = nextsize%2;
        nextsize = next_length+remainder;
    }
    cout<<"The smallest number is "<< getitem(1) <<endl;
    cout<<"Need to compare "<< comparison <<" times"<<endl;
}

template<class T> void AList<T>::find_smallest2(void)
{
    if (numitems<2){
        cout << "invalid length"<<endl;
        return ;
    }


    T smallest = getitem(1);
    AList<T> nextlist = 0;  //recode numbers relavant to the possible smallest number
    int comparison = 0;



}

//----------------------end of ex1----------------------

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
    int next = 34;
    for (int i = 1; i <= maxsize; i++)
    {
        next = (99*i*i+100)%210;
        //next = next*16807%2147483647/10000;
        append(next);
    }
    display_q4();
}

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
        cout << "Index error: index out of range\n";
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

