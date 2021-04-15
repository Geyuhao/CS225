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

}