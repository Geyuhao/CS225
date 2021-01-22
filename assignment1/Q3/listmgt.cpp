//
//  listmgt.cpp
//  
//
//  Created by KD on 14.01.21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "alist.cpp"
using std::cout;
using std::cin;

int main()
{
    int type, size, op;
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
            case 0: return(0);
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
                    value = mylist1.popback();
                    cout << "The element removed from back is " << value << ".\n";
                }else{
                    int value = mylist2.popback();
                    cout << "The element removed from back is " << value << ".\n";
                }
                break;
            }
            case 4:                             //test case for popfront, after this method, it will print which element is popped out
            {                                   //displaying also can be used to show that the first element in the list has been poped out
                 if (type == 0){
                    int value = mylist1.popfront();
                    cout << "The element removed from front is " << value << ".\n";
                 }else{
                    int value = mylist2.popfront();
                    cout << "The element removed from front is " << value << ".\n";
                 }
                break;
            }
            case 5:                         //this test case is used to check what elements are remained in the list
            {
                if (type == 0)
                {
                    mylist1.display();
                }
                else
                {
                    mylist2.display();
                }
                break;
            }
            default: return(0);
        }
    }
    while (op != 0);
    return(0);
}
