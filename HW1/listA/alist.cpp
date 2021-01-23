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
    display();
}

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
    display();
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
    display();
}

template<class T> void AList<T>::display(void)
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
    display();
}

//-------------above is the new function--------------


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