#include "alist.cpp"
#include <stdio.h>
#include <iostream>
#include <cstdlib>
using namespace::std;

int main()
{
    int type;
    AList<int> testlist = 20;
    AList<double> testlist2 = 20;
    SRC<int> src_int;
    SRC<double> src_double;
    cout << "-------------Structural Recursion TEST-----------------" << endl;
    for (int i = 0; i <= 12; i++) {
        testlist.append(i);
        testlist2.append((double) i/4);
    }
    cout << "Choose type: 0.int   1.double" << endl;
    cin >> type;
    switch(type){
    case 0:
        cout << "[";
        for (int i = 1; i <= testlist.getlength() - 1; i++) {
            cout << testlist.getitem(i) << ", ";
        } cout << testlist.getitem(testlist.getlength()) << "]\n";
        cout << "The sum of the array is " << src_int.strcutural_recursion (testlist) << endl;
        break;
    case 1:
        cout << "[";
        for (int i = 1; i <= testlist2.getlength() - 1; i++) {
            cout << testlist2.getitem(i) << ", ";
        } cout << testlist2.getitem(testlist2.getlength()) << "]\n";
        cout << "The sum of the array is " << src_double.strcutural_recursion (testlist2) << endl;
    default:
        break;
    }

    cout << "-------------Structural Recursion TEST End-----------------" << endl;
}