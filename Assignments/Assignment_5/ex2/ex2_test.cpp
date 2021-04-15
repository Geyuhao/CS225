#include "multiset_f.h"


int main(){
    /******************* Put your own test here *******************/
    /* Your are expected to give adequate test to show the correctness of your implementation */
    /* Otherwise you may be deducted points */

    MultiSet<int> test1 = MultiSet<int>(20);
    MultiSet<int> test4 = MultiSet<int>(20);
    MultiSet<int> temp;

    MultiSet_Chaining <int> test2 = MultiSet_Chaining<int>(20);
    MultiSet_Chaining<int> test3 = MultiSet_Chaining<int>(20);
    

    cout << "------------------------ Part 1 ------------------------" << endl;
    cout << "################### Insertion test ############################" << endl;
    for(int i = 0; i < 15; i++){
        for (int j = 0; j < i; j++) {
            test1.insertion(j);
            test4.insertion(2*j);
        }
    }
    cout << "Multiset_1:" << endl;
    test1.display();
    cout << "\n\n\n";
    cout << "Multiset_2:" << endl;
    test4.display();

    cout << "\n\n################ Union test #####################" << endl;
    cout << "Union of the Multiset1 and Multiset2:\n";
    test1.setunion(test4);
    test1.display();


    cout << "\n\n################ Intersection test #####################" << endl;
    cout << "The intersected elements are:\n";
    test1.intersection(test4);
    

    cout << "\n\n################ Difference test #####################" << endl;
    //cout << "The elements with different number are:" << endl;
    temp = test1.difference(test4);
    temp.display();

    
    cout<<endl<<endl<<endl;

    cout << "------------------------ Part 2 ------------------------" << endl;
    cout << "################### Insertion test ############################" << endl;

    int input1[] = {1,1,1,21,21,21,3,3,7,6,6};
    int input2[] = {41,41,21,21,3,3,3,7,7,21,21};

    for (auto i: input1){
        test3.insertion(i);
    }
    cout << "Multiset_1:" << endl;
    test3.display_chaining();
    cout<<endl<<endl;


    for (auto i: input2){
        test2.insertion(i);
    }
    cout << "Multiset_2:" << endl;
    test2.display_chaining();
    cout<<endl;


    cout << "\n\n################ set union test #####################" << endl;
    cout << "After set union: " << endl;
    test3.setunion(test2);
    test3.display_chaining();


    cout << "\n\n################ Intersection test #####################" << endl;

    MultiSet_Chaining <int> test5 = MultiSet_Chaining<int>(20);
    MultiSet_Chaining<int> test6 = MultiSet_Chaining<int>(20);

    for (auto i: input1){
        test5.insertion(i);
    }
    cout << "Multiset_1:" << endl;
    test5.display_chaining();
    cout<<endl<<endl;


    for (auto i: input2){
        test6.insertion(i);
    }
    cout << "Multiset_2:" << endl;
    test6.display_chaining();
    cout<<endl<<endl;

    cout << "After intersection: " << endl;
    test5.intersection(test6);
    test5.display_chaining();



    cout << "\n\n################ difference test #####################" << endl;

    MultiSet_Chaining <int> test7 = MultiSet_Chaining<int>(20);
    MultiSet_Chaining<int> test8 = MultiSet_Chaining<int>(20);

    for (auto i: input1){
        test7.insertion(i);
    }
    cout << "Multiset_1:" << endl;
    test7.display_chaining();
    cout<<endl<<endl;


    for (auto i: input2){
        test8.insertion(i);
    }

    cout << "Multiset_2:" << endl;
    test8.display_chaining();
    cout<<endl<<endl;

    cout << "After difference: " << endl;
    test7.difference(test8);
    test7.display_chaining();

    /* Test for part(ii) */
    return 0;
}