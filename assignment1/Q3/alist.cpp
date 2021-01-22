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

template<class T> T &AList<T>::operator[](int index)
{
    return arr[index - 1];
}

template<class T> void AList<T>::pushback(T value)
{
    //check if the queue is full
    if ((rear+1) % maxsize == front){
        allocate();
    }
    arr[rear]=value;
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
    arr[front]=value;
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
    T value = arr[rear];
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
    T value = arr[front];
    front = (front+1) % maxsize;        //increment front
    --numitems;
    return value;

}

template<class T> void AList<T>::allocate(void)
{
    int newsize = 2 * maxsize;
    T *newarray = new T[newsize];
    int count=0;
    for (int i = front; i < front+numitems; ++i)
    {
        newarray[count] = arr[i%maxsize];
        count++;
    }
    front=0;
    rear=count;
    delete[] arr;       //allocate and the pointer should be arranged again
    arr = newarray;
    maxsize = newsize;
    return;
}
template<class T> void AList<T>::display(void)
{
    int counter = 1;
    for (int i = front; i < front+numitems; ++i)
    {
        T doubleitem = arr[i%maxsize];  //display the element in correct order of list
        cout << "List element " << counter << " is " << doubleitem <<".\n";
        counter++;
    }
    return;
}



template<class T> void AList<T>::deallocate(void)
{
    int newsize = maxsize / 2;
    T *newarray = new T[newsize];
    int count=0;
    for (int i = front; i < front+numitems; ++i)
    {
        newarray[count] = arr[i%maxsize];
        count++;
    }
    front=0;        //deallocate and the pointer should be arranged again
    rear=count;
    delete[] arr;
    arr = newarray;
    maxsize = newsize;
    return;
}


