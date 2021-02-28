#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "ex1.h"
using namespace::std;

//-------------member function for HW3 ex1--------------

template<class T> void AList<T>::find_smallest(void)
{
    // The length should be larger than 1
    if (maxsize < 1){
        cout << "invalid length";
        return;
    } 

    // count the comparision times
    int comparison = 0;

    // calculate the length of the new list
    int next_length = numitems/2;
    int remainder = numitems%2;
    int nextsize = next_length+remainder;

    // build a list of pointers to AList, which records the numbers that
    // have been compared with a specific one
    AList<T> *relative[numitems];
    int relative_length =0;
    for (int i=0; i<numitems; i++)
    {
        relative_length++;
        relative[i]=new AList<T>;
    }

    while(nextsize != 1 || next_length == 1 ){
        for (int i=1; i<=nextsize; i++)
        {
            if ((i < nextsize) || (remainder == 0)){
                T left = getitem(i);
                T right = getitem(i+1);
                    
                // For the larger one, it can't be the smallest and 
                // it's list of relative numbers is no longer needed
                if (left<right){
                    relative[i-1]->append(right);       // add right to left's relative number list
                    delete relative[i];                 // delete right's relative number list
                    relative_length--;                  // the list of pointers is shorten
                    for (int j=i;j<relative_length;j++)
                    {
                        relative[j]=relative[j+1];
                    }
                    remove(i+1);
                } else{
                    relative[i]->append(left);
                    delete relative[i-1];
                    relative_length--;
                    for (int j=i-1;j<relative_length;j++)
                    {
                        relative[j]=relative[j+1];
                    }
                    remove(i);
                }
                comparison ++;    // count the needed times;
            }
        }
        next_length = nextsize/2;
        remainder = nextsize%2;
        nextsize = next_length+remainder;
    }
    cout<<"------------After "<< comparison <<" comparisons------------"<<endl;
    cout<<"We find the smallest number "<< getitem(1) <<endl;
    cout<<"Also we get the list of possible second smallest number ";
    cout<<"Which has "<<relative[0]->getlength()<<" numbers"<<endl;
    relative[0]->display();

    int comparison2 = 0;
    T sec_small = relative[0]->getitem(1);
    for (int i=2; i<=relative[0]->getlength(); i++)
    {
        comparison2++;          // count the comparing times
        if (sec_small>relative[0]->getitem(i)){
            sec_small = relative[0]->getitem(i);
        }
    }
    cout<<"---------After another "<< comparison2 <<" comparisons---------"<<endl;
    cout<<"We find the second smallest number "<< sec_small <<endl;    
}


//----------------------end of ex1----------------------

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
    int next = 34;
    for (int i = 1; i <= maxsize; i++)
    {
        //next = (99*i*i+100)%210;
        next = next*16807%2147483647/10000;
        append(next);
    }
    display();
}

template<class T> T &AList<T>::operator[](int index)
{
    return reprarray[index - 1];
}

template<class T> int AList<T>::getlength(void)
{
    return numitems;
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

