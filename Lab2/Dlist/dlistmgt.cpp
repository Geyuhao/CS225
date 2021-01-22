//
//  listmgt.cpp
//  
//
//  Created by KD on 14.01.21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "dlist.cpp"
using std::cout;
using std::cin;

int main()
{
    int type,length;
    do {
        // exam function selectionsort and insertion sort
        cout << "This is for the Exercise 4\n";
        cout << "Choose which function do you want to exam:\n";
        cout << "0: Selection Sort  1: Insertion Sort\n";
        cin >> type ;
        if ((type != 0) && (type != 1))
            cout << "You must choose 0 or 1\n\n";
    } while ((type != 0) && (type != 1));


    cout << "Now it will generate a random list for you to test\n";
    cout << "How long you wish it will be: ";
    cin >> length;
    DList<int> mylist = DList<int>();
    mylist.gen_rand(length);
    if (type == 0){
        cout << "let's use selection sort!\n";
        mylist.selectionsort();
    } else{
        cout << "let's use insertion sort!\n";
        mylist.insertionsort();
    }



/*
    switch(type)
    {
        case 0:
        // This is for selection sort
        {
            AList<int> mylist1 = AList<int>(size);
            break;
        }
        // This is for insertion sort
        case 1:
        {
            AList<double> mylist2 = AList<double>(size);
            break;
        }
    }*/
    return(0);
}