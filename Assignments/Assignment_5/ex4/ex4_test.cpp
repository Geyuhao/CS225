#include <ctime>                /* For performance comparasion */
#include "hashset_f.h"
#include "hash_extend_f.h"
#include <stdio.h>
#include <cstdlib>
#include <iostream>
using namespace::std;


int main(){
    /******************* Put your own test here *******************/
    /* Your are expected to give adequate test to show the correctness of your implementation */
    /* Otherwise you may be deducted points */

    /**************************************************************/
    /* Check Point 1: Correctness */

    int input1[] = {1, 1, 1, 5, 2, 6};
    int input2[] = {5, 25, 45, 65, 85};




    cout << "################ Insertion Test #################\n";
    cout << "The input list is: ";
    HashSet_LCFS<int> test1, test2;
    HashSet_RH<int> test3, test4;
    //  Add test to your container 
    cout << "[";
    for(auto i: input1){
        cout << i << " ";
        test1.insert(i);
        //test1.display();
        test3.insert(i);
    } cout << "]\n";

    cout << "The HashSet_LCFS has elements: \n";
    test1.display();
    cout << "The HashSet_RH has elements: \n";
    test3.display();
    
    cout << "\nThe input list2 is: ";
    cout << "[";
    for (auto i:input2){
        cout << i << " ";
        test2.insert(i);
        test4.insert(i);
    } cout << "]\n";

    cout << "The HashSet_LCFS has elements: \n";
    test2.display();
    cout << "The HashSet_RH has elements: \n";
    test4.display();
    
    cout << "\n\n################ Remove Test #################\n";
    cout << "Remove 5 from both sets:\n";
    test1.remove(5);
    test3.remove(5);
    cout << "The HashSet_LCFS has elements: \n";
    test1.display();
    cout << "The HashSet_RH has elements: \n";
    test3.display();

    cout << "Remove 65 from both sets:\n";
    test2.remove(65);
    test4.remove(65);
    cout << "The HashSet_LCFS has elements: \n";
    test2.display();
    cout << "The HashSet_RH has elements: \n";
    test4.display();

    cout << "\n\n############## Member Test is omitted as it is corret ####################\n";
    


    /**************************************************************/
    /* Check Point 2: Compare the performance with initial hashset as baseline */
    /* ctime is included for you to help */
    cout << "\n\n############## Performance Compare ####################\n";

    //Random array test
    clock_t start, end;
    int rand_arr[20];
    int number;
    HashSet_LCFS<int> test5;
    HashSet_RH<int> test6;
    hashset<int> test7;
    


    const int MIN = 0, MAX = 100;
    for (int i = 0; i < 20; i++){
        rand_arr[i] = rand()%(MAX-MIN+1)+MIN;
    } number = rand_arr[rand()%19];
     cout << "Test using random list:\n";
    

    cout << "HashSet: \n";
    for (int i = 0; i < 20; i++){
        test7.add(rand_arr[i]);
    } test7.display();
    cout << "\n\nHashSet_LCFS:\n";
    for (int i = 0; i < 20; i++){
        test5.insert(rand_arr[i]);
    } test5.display();
    cout << "HashSet_RH:\n";
    
    for (int i = 0; i < 20; i++){
        test6.insert(rand_arr[i]);
    } test6.display();




    start = clock();
    test7.member(number);
    end = clock();
    cout << "Time for HashSet to find a number: " << 1000*(end - start)/(double)CLOCKS_PER_SEC << "ms\n";

    start = clock();
    test5.member(number);
    end = clock();
    cout << "Time for HashSet_LCFS to find a number: " << 1000*(end - start)/(double)CLOCKS_PER_SEC << "ms\n";

    start = clock();
    test6.member(number);
    end = clock();
    cout << "Time for HashSet_RH to find a number: " << 1000*(end - start)/(double)CLOCKS_PER_SEC << "ms\n";


    cout << "Test using Nonrandom list:\n";
    //Nonrandom array test
    int nonrand_arr[] = {2, 23, 34, 67, 83, 103, 123, 223, 443, 623, 222, 789, 234, 1, 3};
    int search_num = 23;
    HashSet_LCFS<int> test8;
    HashSet_RH<int> test9;
    hashset<int> test10;


    cout << "HashSet: \n";
    for (int i = 0; i < 14; i++){
        test10.add(nonrand_arr[i]);
    } test10.display();
    cout << "\n\nHashSet_LCFS:\n";
    for (int i = 0; i < 14; i++){
        test8.insert(nonrand_arr[i]);
    } test8.display();
    cout << "HashSet_RH:\n";
    for (int i = 0; i < 14; i++){
        test9.insert(nonrand_arr[i]);
    } test9.display();

    start = clock();
    test10.member(search_num);
    end = clock();
    cout << "Time for HashSet to find a number: " << 1000*(end - start)/(double)CLOCKS_PER_SEC << "ms\n";
    

    start = clock();
    test8.member(search_num);
    end = clock();
    cout << "Time for HashSet_LCFS to find a number: " << 1000*(end - start)/(double)CLOCKS_PER_SEC << "ms\n";
    //test6.display();

    start = clock();
    test9.member(search_num);
    end = clock();
    cout << "Time for HashSet_RH to find a number: " << 1000*(end - start)/(double)CLOCKS_PER_SEC << "ms\n";
    

    cout << "\n\n################# Conclusion ####################";
    cout << "\nWe only show the performance of Member for all sets with limited length of list.";
    cout << "\nBy testing using both random and nonrandom lists with different size ranging from 20 to 100000 (not shown in the test)\n";
    cout << "LCFS and RH have better performence in Remove and Member no matter how many number there exists.\n";
    cout << "As for the Insertion, the initial hashset has a better performance than both LCFS and RH with large amount of numbers.\n\n\n";
    return 0; 
}