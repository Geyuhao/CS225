#include "ex1.cpp"
#include <stdio.h>
#include <iostream>
#include <cstdlib>
using namespace::std;


int main()
{
    // This is for HW3 ex1
    cout << "----------HW3 ex1: Find two smallest numbers---------" << endl;
    int length;
    do{
        cout << "Please enter the size of your testlist (length > 1): ";
        cin >> length;
    } while(length<2);

    // creat an AList for test
    AList<int> testlist1 = length;
    // generate a random testlist
    testlist1.gen_rand();
    testlist1.find_smallest();

    /*
    cout<<"-------test-------"<<endl;
    int a = testlist1.getitem(1);
    int b = testlist1.getitem(2);

    int comparison = testlist1.smallest(1,length,a,b);
    cout<<"The smallest number is "<<a<<" The second smallest number is "<<b<<endl;
    cout<<"we need "<<comparison<<" comparisons"<<endl;
    */
}