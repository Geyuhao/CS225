#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "alist.cpp"
using namespace::std;

int main()
{
    cout<<"----------------Test concat--------------\n";
    AList<int> mylist = AList<int>(10);
    AList<int> mylist1 = AList<int>(10);
    mylist1.append(1);
    mylist1.append(2);
    mylist.append(3);
    mylist.append(4);
    mylist.concat(mylist1);
    int n = mylist.getlength();
    int item;
    if(! mylist.equal(mylist1))
    {
    for (int i = 1; i <= n; ++i)
    {
        item = mylist[i];
        cout << "element " << i << ":" << item << endl;
    }
    }
    
    return 0;
}