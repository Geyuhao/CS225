/*
 * File name: hw2ex2.cpp
 * Linked File Name: hw2ex2.h
 * Creat Date: None
 * Assignment: 2
 * Group Members:
 *      Guanshujie Fu   3190110666
 *      Xiaomin Qiu     3190110747
 *      Yuhao Ge        3190110674
 *      Haina Lou       3190110572
 * Description:
 *      This file contains the functions implemented for 
 *      checking bookings and room number, details have been
 *      presented in comments. 
 */

#include "hw2ex2.h"
#include <vector>
#include <iostream>
#include <stdio.h>
#include <cstdlib>

using namespace std;
int main(){
    vector<booking> b1({booking(1,3), booking(2,4), booking(3,5), booking(4,5)});

    // =========== Test 1 ===========
    Bookings test1 = Bookings(b1, 5);
    cout << "Test 1: " << endl;
    test1.test();
    cout << "Gold Result: Success" << endl;

    // =========== Test 2 ===========
    Bookings test2 = Bookings(b1, 1);
    cout << "\nTest 2: " << endl;
    test2.test();
    cout << "Gold Result: Fail" << endl;

    // =========== Hidden Test =========
    // You could addd your own test example
    vector<booking> b2({booking(1,2), booking(2,5), booking(3,4), booking(4,5)});
    Bookings test3 = Bookings(b2, 3);
    cout << "\nTest 3: " << endl;
    test3.test();
    cout << "Gold Result: Success" << endl;

    return 0;
}

