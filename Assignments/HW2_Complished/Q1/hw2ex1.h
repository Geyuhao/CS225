/*
 * File name: hw2ex1.h
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
 *      mergesort with k sublists, mergesort with thr and self sort.
 *      details have been presented in comments. 
 */
#ifndef ex1
#define ex1

#include <iostream>
#include <stdio.h>
#include <ctime>
#include <vector>
using namespace std;

// You may modify the decleration and definenation by yourself, add help function etc.
template <class T> class Solution {
    public:
        Solution(vector<T> input){
            data = input;
        };

        // functions needed for ex1.1
        vector<T> MergeSort_k(vector<T> lst, int k);
        vector<T> Merge_k(vector< vector<T> > llst, int k);
        // functions needed for ex1.2
        vector<T> MergeSort_t(vector<T> lst, int t, int first, int last);
        vector<T> SelfSort(vector<T> lst);
        vector<T> Merge(vector<T> lst, int first, int last);

        void vec_print(vector<T> vec);

        vector<T> data;
        void test(int k, int t);
    private:
        
};

// Modify the following to finish ex1.1
template <class T> vector<T> Solution<T>::MergeSort_k(vector<T> lst, int k){
    vector< vector<T> > llst;       // list to store lists
    int sub_size, diff;     
    int size[k];        // list to store the size of lists;

    if (1 == lst.size())    return lst;     // if current size of the lst is 1, just return
    if (lst.size() < k)  k = lst.size();    
    sub_size = lst.size()/k;                // calculate the average size of the sublists
    diff = lst.size() - sub_size*k;         // calculate the size difference as the size of all the sublists may not be the same
    for (int i = 0; i < k; i++) {
        size[i] = sub_size;
        if (diff-- > 0) size[i]++;          // loop to calculate the different size of the sublists;
    }

    for (int i = 0, elements_id = 0; i < k; i++) {
        vector<T> temp;
        for (int j = 0; j < size[i]; j++, elements_id++) {
            temp.push_back(lst[elements_id]);
        } llst.push_back(temp);     // store the k sublists into the llst;
    }

    for (int i = 0; i < llst.size(); i++) {
        llst[i] = MergeSort_k(llst[i], k);      // recurse to mergesort all the sublists
    }
    return Merge_k(llst, k);        // call Merge_k for llst to merge all sublists in the llst
}

template<class T> vector<T> Solution<T>::Merge_k(vector< vector<T> > llst, int k) {
    vector<T> lst;      // a list to store the result
    int ptr[llst.size()];     // a list to store the pointers for every sublists;
    int size = 0;    // size stands for the number of all elements in the lst
    T min;

    for (int i = 0; i < llst.size(); i++) {
        size += llst[i].size();
        ptr[i] = 0;     // initialize all the pointers of the sublists to 0;
    }
    for (int i = 0; i < size; i++) {
        vector<int> min_id;     // a list to store the index of the sublists which contain smaller elements then min
        min = 100000000;        // min should be choosen cleverly
        for (int j = 0; j < llst.size(); j++) {
            if ((llst[j][ptr[j]] < min) && (ptr[j] < llst[j].size())) {
                min = llst[j][ptr[j]];
                min_id.push_back(j);
            }
        }
        ptr[min_id[min_id.size()-1]]++;     // the last index is the sublist which contain the smallest element
        lst.push_back(min);     // push min into the lst
    }
    return lst;
}



// Modify the following to finish ex1.2
template<class T> vector<T> Solution<T>::MergeSort_t(vector<T> lst, int t, int first, int last){
    if (lst.size() < t) {
        return SelfSort(lst);
    } else {
        if (first < last){
            int mid = (first + last)/2;
            lst = MergeSort_t(lst, t, first, mid);
            lst = MergeSort_t(lst, t, mid+1, last);
            return Merge(lst, first, last);
        }
    } return lst;
}

template<class T> vector<T> Solution<T>::Merge(vector<T> lst, int first, int last){

    int mid = (first + last)/2;     
    int ptr_1 = first, ptr_2 = mid + 1;     //set the left and right index
    vector<T> temp;     // set temporary vector to store the list to be sorted

    while ((ptr_1 <= mid) && (ptr_2 <= last)){  // check the first and second sublists
        if (lst[ptr_1] < lst[ptr_2]){
            temp.push_back(lst[ptr_1++]);
        } else {
            temp.push_back(lst[ptr_2++]);       // push the sorted number into the temp vector
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

// You could implement either bubble sort, insert sort or selection sort
template<class T> vector<T> Solution<T>::SelfSort(vector<T> lst){
    // insertion sort
    for (int i = 1, j; i < lst.size(); i++) {
        T temp = lst[i];
        for (j = i; j > 0 && temp < lst[j-1]; j--){
            lst[j] = lst[j-1];
        } lst[j] = temp;
    }
    // selection sort
    for (int i = 0; i < lst.size()-1; i++) {
        T minimum = lst[i], min_index = i;
        for (int j = i + 1; j < lst.size(); j++) {
            if (lst[j] < minimum) {
                minimum = lst[j];
                min_index = j;
            } 
        } lst[min_index] = lst[i]; lst[i] = minimum;
    }
    // bubble sort
    for (int i = 0 ; i < lst.size(); i++) {
        for (int j = lst.size()-1; j > i; j--) {
            if (lst[j] < lst[j-1]){
                T temp = lst[j];
                lst[j] = lst[j-1]; lst[j-1] = temp; 
            }
        }
    }
    return lst;
}

// DO NOT modify the following
// This is to view the vector
template<class T> void Solution<T>::vec_print(vector<T> vec){
    for (T i: vec){
        cout << i << "  ";
    }
    cout << endl;
    return ;
}

// This is for testing.
template <class T> void Solution<T>::test(int k, int t){
    vector<T> temp;
    //clock_t start, end;

    cout << "Self-implemented Sort:          ";
    vec_print(SelfSort(data));
    cout << "Merge Sort with K sublist:      ";
    vec_print(MergeSort_k(data, k));

    cout << "Merge Sort with Insertion Sort: ";
    //start = clock();
    temp = MergeSort_t(data, t, 0, data.size()-1);
    //end = clock();
    //double time = (double) (end - start)/CLOCKS_PER_SEC;
    vec_print(temp);
    //cout << "Total time with " << t << " as thr is ";
    //printf("%5f ms\n", time*1000);
}
#endif 

