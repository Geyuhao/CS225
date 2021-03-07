/*
 * File name: hw2ex2.h
 * Linked File Name: None
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

#include <vector>
#include <iostream>
using namespace std;

class booking{
    public:
        booking(int a, int d){
            arrival = a;
            departure = d;
        };
        int arrival; 
        int departure; 
};


class Bookings{
    public:
        Bookings(vector<booking> bookings, int K){
            bks = bookings;
            k = K;
        };
        vector <booking> bks;
        int k;
        void bookings_print();
        void test();
        
        // Modify the following to solve the exercise
        // You may also add your own help function
        bool checkdemands();
        vector < vector<int> > Mergesort_b (vector < vector<int> > tags, int first, int last);
        vector < vector<int> > Merge(vector < vector<int> > tags, int first, int last);

    private:

};

// You should right the following to finish the exercise
// You may also add your own help function
bool Bookings::checkdemands(){
    vector< vector<int> > tags;     // tags is a list to store the dates with a tag, 
    int check = 0;                  // arrival date with tag 1 and departure date with tag -1

    if (k > bks.size())    return 1;    // if room number is bigger than the booking number, then it must satisfy
    for (booking i: this->bks) {
        vector<int> temp_1, temp_2;
        temp_1.push_back(i.arrival); temp_1.push_back(1);   // add tag to arrival date and push into "tags"
        temp_2.push_back(i.departure); temp_2.push_back(-1);    // add tag to departure date
        tags.push_back(temp_1);
        tags.push_back(temp_2);
    }
    tags = Mergesort_b(tags, 0, tags.size()-1);     // sort the dates depends on the date
    for (int i = 0; i < tags.size(); i++){
        //cout << "[" << tags[i][0] << tags[i][1] << "]";
        check += tags[i][1];
        if (check > k)  return 0;
    }
    return 1;
}


// below is the mergesort algorithm used to sort the date
vector < vector<int> > Bookings::Mergesort_b(vector < vector<int> > tags, int first, int last) {

    if (first < last){
        int mid = (first + last)/2;
        tags = Mergesort_b(tags, first, mid);
        tags = Mergesort_b(tags, mid+1, last);
        return Merge(tags, first, last);
    }
    return tags;
}

vector < vector<int> > Bookings::Merge(vector < vector<int> > lst, int first, int last) {
    int mid = (first + last)/2;     
    int ptr_1 = first, ptr_2 = mid + 1;     //set the left and right index
    vector<vector <int> > temp;     // set temporary vector to store the list to be sorted

    while ((ptr_1 <= mid) && (ptr_2 <= last)){  // check the first and second sublists
        if (lst[ptr_1][0] < lst[ptr_2][0]){
            temp.push_back(lst[ptr_1++]);
        } else if (lst[ptr_1][0] > lst[ptr_2][0]){
            temp.push_back(lst[ptr_2++]);       // push the sorted number into the temp vector
        } else {
            if (lst[ptr_1][1] < lst[ptr_2][1]){
                temp.push_back(lst[ptr_1++]);
            } else {
                temp.push_back(lst[ptr_2++]);
            }
        }
    }
    while (ptr_1 <= mid){
        temp.push_back(lst[ptr_1++]);       // push the rest numbers into the temp vector
    }
    while (ptr_2 <= last) {
        temp.push_back(lst[ptr_2++]);
    }
    for (int i = 0; i < last-first+1; i++){ // copy the temp vector into the lst vector
        lst[first+i] = temp[i];
    }
    return lst;
}

// DO NOT modify the following 
void Bookings::bookings_print(){
    cout << "Bookings as follow:" << endl;
    for(booking i: this->bks){
        cout << "A: " << i.arrival << "  | D: " << i.departure << endl;
    }
    cout << "Max available room:" << this->k << endl;
    return ;
}

void Bookings::test(){
    bookings_print();
    cout << "Check whether satisfy the demands: " << (checkdemands()? "Success":"Fail") << endl;
}