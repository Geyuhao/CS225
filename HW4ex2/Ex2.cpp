#include<iostream>	
#include<math.h>
#include <cstdlib>
#include <map>
#include <vector>
#include "Ex2.h"
using namespace std;

template<class T> int NumSet<T>::Check_Relation(vector<pair<int,int> > R){
    /*
    Input:
        R: The relation to be checked. Each element in R is a pair(int,int)
    Output:
        0: The binary relation R is not symmetric
        1: The binary relation R is symmetric
    */
   
    // Set up a list, the index is hash value (0~10)..
    int vec_len = R.size();
    vector< vector< pair<int,int> > > hash_set(10);

    // loop through every pair
    for (int i=0; i<vec_len; i++)
    {
        if (R[i].first == R[i].second){
            continue;
        }
        // Use XOR as hash function to get the hash value
        int hash_value = (R[i].first ^ R[i].second)%10;
        // add it into the list if it is empty
        if (hash_set[hash_value].empty() == true) {
            hash_set[hash_value].push_back(R[i]);
        } else{
            // check if the original list contains a symmetrc one
            bool find = false;
            for (int j=0; j<hash_set[hash_value].size(); j++)
            {
                int left = hash_set[hash_value][j].first;
                int right = hash_set[hash_value][j].second;
                // When find one, replace the original one with placeholder
                if (left == R[i].second && right == R[i].first){
                    // As (0,0) won't show in the pair, it can be used as place holder
                    hash_set[hash_value][j].first = 0;
                    hash_set[hash_value][j].second = 0;
                    find = true;
                    break;
                }
            }
            // if can't find one, add it into the list
            if (find == false){
                hash_set[hash_value].push_back(R[i]);
            }
        }
    }

    // check if there is only placeholder remains
    int check = 1;
    for (int i=0; i<10;i++){
        for (int j=0; j<hash_set[i].size(); j++){
            if (hash_set[i][j].first != 0 || hash_set[i][j].second != 0){
                check ++;
            }
        }
    }

   return (check == 1) ? 1:0 ;

};


int main(){
    int Set_A[10]={1,2,3,4,5,6,7,8,9,10};
    NumSet<int> S(Set_A,10);
    //Here is for Test 1
    vector<pair<int,int> > Relation_R1;
    for (int i=0; i<10; i++){
        Relation_R1.push_back(make_pair(Set_A[i],Set_A[i]));
        for (int j=0; j<10; j++){
            if (i != j)
                Relation_R1.push_back(make_pair(Set_A[i],Set_A[j]));
        }
    }
    
    cout << "For Test 1:"<<endl;
    cout << "The correct answer should be Yes"<<endl;
    cout << "Your answer is:" << ((S.Check_Relation(Relation_R1) == 1)?"Yes":"No")<< endl;
    
    //Here is for Test 2
    vector<pair<int,int> > Relation_R2;
    for (int i=0; i<10; i++){
        Relation_R2.push_back(make_pair(Set_A[i],Set_A[i]));
        for (int j=0; j<10; j++){
            if ((i != j) && (j%2 != 1))
                Relation_R2.push_back(make_pair(Set_A[i],Set_A[j]));
        }
    }
    cout << "For Test 2:"<<endl;
    cout << "The correct answer should be No"<<endl;
    cout << "Your answer is:" << ((S.Check_Relation(Relation_R2)== 1)?"Yes":"No")<< endl;
    
    return 0;
    
}