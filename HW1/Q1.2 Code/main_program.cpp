#include "alist.cpp"
#include <stdio.h>
#include <iostream>
#include <cstdlib>
using namespace::std;

int main(void) {

    //demo for delete_last
    cout << "---------------TEST delete_last---------------" << endl;
    int del;
    // creat an AList for test
    AList<int> testlist1 = 20;
    // append 20 elements into testlist1
    for (int i = 0; i < 20; i++){
        testlist1.append(i*i);
    }

    // display elements in testlist1 initially
    cout << "Elements in list1 is:\n";
    for (int i = 1; i <= testlist1.getlength(); i++){
        cout << "List element " << i << " is " << testlist1[i] << "\n";
    }

    // excute delete_last function to delete some elements at last of testlist1
    while (testlist1.getlength() > 0){
        cout << "Enter delete number:\n";
        cin >> del;
        if (del > testlist1.getlength()) {
            cout << "Please enter correct number.\n" << endl;
            continue;
        }
        testlist1.delete_last(del);
        for (int i = 1; i <= testlist1.getlength(); i++){
            cout << "List element " << i << " is " << testlist1[i] << "\n";
        } cout << del << " elements have been deleted.\n";
    }
    cout << "---------------TEST delete_last End---------------" << endl;
}
