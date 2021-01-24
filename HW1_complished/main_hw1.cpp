
/*
 * File name: main_hw1
 * Linked File Name: alist.h alist.cpp dlist.h dlist.cpp
 * Creat Date:  1.17.2021
 * Assignment: 1
 * Group Members:
 *      Guanshujie Fu   3190110666
 *      Xiaomin Qiu     3190110747
 *      Yuhao Ge        3190110674
 *      Haina Lou       3190110572
 * Description:
 *      This file contains the main function which 
 *      call functions implemented based on the 
 *      requirement of Assignment1. Details have been
 *      presented in comments.
 */

#include "alist.cpp"
#include "dlist.cpp"
#include <stdio.h>
#include <iostream>
#include <cstdlib>
using namespace::std;

int main()
{
    //*********************** HW1 Q1.2 ************************************
    //demo for delete_last
    cout << "--------------- HW1 Q1.2: delete_last ---------------" << endl;
    int del, length1;
    cout << "Please enter the size of your testlist: ";
    cin >> length1;
    // creat an AList for test
    AList<int> testlist1 = length1;
    // generate random testlist
    testlist1.gen_rand(length1);
    // display elements in testlist1 initially
    cout << "Elements in list is:\n";
    cout << "[";
    for (int i = 1; i < testlist1.getlength(); i++){
        cout << testlist1.getitem(i) << ", ";
    } cout << testlist1.getitem(testlist1.getlength()) << "]\n";

    // excute delete_last function to delete some elements at last of testlist1
    while (testlist1.getlength() > 0){
        cout << "Enter delete number:\n";
        cin >> del;
        if (del > testlist1.getlength() || del < 0) {   // display the elements
            cout << "Please enter correct number.\n" << endl;
            continue;
        } testlist1.delete_last(del);   // excute the delete_last
        if (0 == testlist1.getlength()) break;
        cout << "[";
        for (int i = 1; i < testlist1.getlength(); i++){
            cout << testlist1.getitem(i) << ", ";
        } cout << testlist1.getitem(testlist1.getlength()) << "]\n";
        cout << del << " elements have been deleted.\n";
    }
    cout << "Elements have been all deleted\n";
    cout << "---------------TEST delete_last END---------------" << endl;





    //************************** HW1 Q2.4 ********************************
    cout << "\n\n------------- HW1 Q2.4: Structural Recursion -----------------" << endl;
    
    int type, length2;
    AList<int> testlist0 = 20;
    AList<double> testlist2 = 20;
    SRC<int> src_int;       // operation for int list
    SRC<double> src_double; // operation for double list
    
    // description of our implementation
    cout << "The operation of strcutural recursion we implemented is " << endl;
    cout << "calculating the sum of AList." << endl;
    // type choose
    cout << "Choose type: 0.int   1.double    2.quit" << endl;
    cin >> type;
    while (type < 0 || type > 2) { cout << "Please choose between 0 and 2: ";cin >> type;}

    // loop for the implementation
    while (type != 2) {
        cout << "Please enter the size of your testlist: ";
        cin >> length2;
        testlist0.gen_rand(length2);
        testlist2.gen_rand(length2);
        switch(type){
        case 0:
            cout << "[";
            for (int i = 1; i < testlist0.getlength(); i++) {
                cout << testlist0.getitem(i) << ", ";    // display elements in list
            } cout << testlist0.getitem(testlist0.getlength()) << "]\n";
            cout << "The sum of the array is " << src_int.strcutural_recursion (testlist0) << endl;  // excute the structural recursion for int lists
            break;
        case 1:
            cout << "[";
            for (int i = 1; i < testlist2.getlength(); i++) {
                cout << testlist2.getitem(i) << ", ";   // dispaly elements
            } cout << testlist2.getitem(testlist2.getlength()) << "]\n";
            cout << "The sum of the array is " << src_double.strcutural_recursion (testlist2) << endl; // excute the structural recursion
        default:
            break;
        }
        cout << "Choose type: 0.int   1.double    2.quit" << endl;
        cin >> type;
        while (type < 0 || type > 2) { cout << "Please choose between 0 and 2: ";cin >> type;}
    }
    cout << "-------------Structural Recursion END-----------------" << endl;




    //*********************** HW1 Q3.2 *******************************
    cout << "\n\n------------- HW1 Q3.2: Push and Pop -----------------" << endl;
    int size, op;
    int intitem;
    AList<int> mylist1;
    AList<double> mylist2;
    double doubleitem;

    do
    {
        cout << "Choose your element type:\n";
        cout << "0: int  1: double\n";
        cin >> type ;
        if ((type != 0) && (type != 1))
            cout << "You must choose 0 or 1\n\n";
    }
    while ((type != 0) && (type != 1));
    cout << "Enter a positive integer for the size of your list:\n";
    cin >> size;
    if (size <= 0)
        size = 20;
    switch(type)
    {
        case 0:
        {
            AList<int> mylist1 = AList<int>(size);
            break;
        }
        case 1:
        {
            AList<double> mylist2 = AList<double>(size);
            break;
        }
    }
    do
    {
        do
        {
            cout << "Choose an operation:\n";
            cout << "O: quit\n";
            cout << "1: pushback\n";
            cout << "2: pushfront\n";
            cout << "3: popback\n";
            cout << "4: popfront\n";
            cout << "5: display\n";
            cin >> op ;
        }
        while ((op < 0) && (op > 5));
        switch(op)
        {
            case 0: break;
            case 1:                              //test case for push back. after displaying, new element can be seen to add to
            {                                    //the end of the list. Can input double or integer type.
                cout << "Enter a value:\n";
                if (type == 0)
                {
                    cin >> intitem;
                    mylist1.pushback(intitem);
                }
                else
                {
                    cin >> doubleitem;
                    mylist2.pushback(doubleitem);
                }
                break;
            }
            case 2:                               //test case for pushfront. after displaying, new element can be seen to add to
            {                                    //the front of the list. Can input double or integer type.                           
                cout << "Enter a value:\n";
                if (type == 0)
                {
                    cin >> intitem;
                    mylist1.pushfront(intitem);
                }
                else
                {
                    cin >> doubleitem;
                    mylist2.pushfront(doubleitem);
                }
                break;
            }
            case 3:                             //test case for popback, after this method, it will print which element is popped out
            {                                   //displaying also can be used to show that the last element has been poped out
                if (type == 0){
                    int value ;
                    if (mylist1.getlength() == 0) {
                        cout << "The list is empty\n";
                        break;
                    }
                    value = mylist1.popback();
                    cout << "The element removed from back is " << value << ".\n";
                }else{
                    if (mylist2.getlength() == 0) {
                        cout << "The list is empty\n";
                        break;
                    }
                    int value = mylist2.popback();
                    cout << "The element removed from back is " << value << ".\n";
                }
                break;
            }
            case 4:                             //test case for popfront, after this method, it will print which element is popped out
            {                                   //displaying also can be used to show that the first element in the list has been poped out
                 if (type == 0){
                     if (mylist1.getlength() == 0) {
                        cout << "The list is empty\n";
                        break;
                    }
                    int value = mylist1.popfront();
                    cout << "The element removed from front is " << value << ".\n";
                 }else{
                     if (mylist2.getlength() == 0) {
                        cout << "The list is empty\n";
                        break;
                    }
                    int value = mylist2.popfront();
                    cout << "The element removed from front is " << value << ".\n";
                 }
                break;
            }
            case 5:                         //this test case is used to check what elements are remained in the list
            {
                if (type == 0)
                {
                    if (mylist1.getlength() == 0) {
                        cout << "The list is empty\n";
                    } mylist1.display_q3();
                }
                else
                {
                    if (mylist2.getlength() == 0) {
                        cout << "The list is empty\n";
                    } mylist2.display_q3();
                }
                break;
            }
            default: break;
        }
    }
    while (op != 0);
    cout << "------------- Push and Pop functions END -----------------" << endl;




    cout << "\n\n------------- HW1 Q4: Sort functions for AList ---------------" << endl;
    int length;
    do {
        // exam function selectionsort and insertion sort
        cout << "This is for the Exercise 4.1 of AList\n";
        cout << "Choose which function do you want to exam:\n";
        cout << "0: Selection Sort  1: Insertion Sort   2: Bubble Sort\n";
        cin >> type ;
        if ((type != 0) && (type != 1) && (type != 2))
            cout << "You must choose 0 or 1 or 2\n\n";
    } while ((type != 0) && (type != 1) && (type != 2));


    cout << "Now it will generate a random list for you to test\n";
    cout << "How long you wish it will be:";
    cin >> length;
    AList<int> mylist_alist = AList<int>(length);
    mylist_alist.gen_rand();
    if (type == 0){
        cout << "let's use selection sort!\n";
        mylist_alist.selectionsort();
    } else if (type == 1) {
        cout << "let's use insertion sort!\n";
        mylist_alist.insertionsort();
    } else if (type == 2) {
        cout << "let's use bubble sort!\n";
        mylist_alist.bubblesort();
    }
    cout << "-------------- Sort functions for AList END ------------------" << endl;





    cout << "\n\n-------------- HW1 Q4: Sort functions for DList ------------------" << endl;
    int length4;
    do {
        // exam function selectionsort and insertion sort
        cout << "This is for the Exercise 4.1 of DList\n";
        cout << "Choose which function do you want to exam:\n";
        cout << "0: Selection Sort  1: Insertion Sort  2: Bubble Sort\n";
        cin >> type ;
        if ((type != 0) && (type != 1) && (type != 2))
            cout << "You must choose 0 or 1 or 2\n\n";
    } while ((type != 0) && (type != 1) && (type != 2));


    cout << "Now it will generate a random list for you to test\n";
    cout << "How long you wish it will be: ";
    cin >> length4;
    DList<int> mylist_dlist = DList<int>();
    mylist_dlist.gen_rand(length4);
    if (type == 0){
        cout << "let's use selection sort!\n";
        mylist_dlist.selectionsort();
    } else if (type == 1){
        cout << "let's use insertion sort!\n";
        mylist_dlist.insertionsort();
    } else if (type == 2){
        cout << "let's use bubble sort!\n";
        mylist_dlist.bubblesort();
    }
    cout << "-------------- Sort functions for DList END ------------------" << endl;
    return(0);
}