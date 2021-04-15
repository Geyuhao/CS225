//
//  test.cpp
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include "solution.h"
#include "trie.h"
#include "trie.cpp"
using namespace std;

void Str2CharList(AList<char> &list, string s);
vector<string> split(string str,string separator);

int main() {
    /* You may change to smaller test text for debugging */
    string text = "I am happy to join with you today in what will go down in history as the greatest demonstration for freedom in the history of our nation. Five score years ago, a great American, in whose symbolic shadow we stand today, signed the Emancipation Proclamation. This momentous decree came as a great beacon light of hope to millions of Negro slaves who had been seared in the flames of withering injustice. It came as a joyous daybreak to end the long night of their captivity. But one hundred years later, the Negro still is not free. One hundred years later, the life of the Negro is still sadly crippled by the manacles of segregation and the chains of discrimination. One hundred years later, the Negro lives on a lonely island of poverty in the midst of a vast ocean of material prosperity. One hundred years later, the Negro is still languished in the corners of American society and finds himself an exile in his own land. And so we've come here today to dramatize a shameful condition. In a sense we've come to our nation's capital to cash a check. When the architects of our republic wrote the magnificent words of the Constitution and the Declaration of Independence, they were signing a promissory note to which every American was to fall heir. This note was a promise that all men, yes, black men as well as white men, would be guaranteed the unalienable Rights of Life, Liberty and the pursuit of Happiness. It is obvious today that America has defaulted on this promissory note, insofar as her citizens of color are concerned. Instead of honoring this sacred obligation, America has given the Negro people a bad check, a check which has come back marked insufficient funds.";
    string temp;
    trie<char> MyDict;

    /* Remove the punctuations and transfer all letters to lowercase */
    for (string::size_type i = 0; i < text.size(); i++) {
        if (!ispunct(text[i])){
            temp += tolower(text[i]);
        }
    }
    vector<string> words = split(temp, " ");

    /* Build the dictionary */
    AList<char> curr;
    for (int i = 0; i < words.size(); ++i) {
        while (curr.getlength())
            curr.remove(1);
        for (int j = 0; j < words[i].size(); ++j)
            curr.append(words[i][j]);
        MyDict.insert(curr);
    }
    cout<<"===================Our dictionary===================="<<endl;

    /* Displaying the dictionary */
    MyDict.display();

    // my own test
    AList<char> in_str;
    string inputword;
    AList<string> result;

    int a;
    cout << "Type 1 if you want to try original test, type 0 if you want to try freely with your input: ";
    cin >> a;
    cout<<"\n";
    switch (a)
    {
    case 0:
    // new test


        int op;
        cout<<"please enter your word to find: ";
        cin>>inputword;
        do
        {
            cout<<"choose which operation you want to use"<<endl;
            cout<<"0: quit\n";
            cout<<"1: find the extend of word\n";
            cout<<"2: find the prefix of word\n";
            cout<<"3: find the word with one symbol difference\n";
            cout<<"4: enter a new word\n";
            cin>>op;
            switch (op)
            {
            case 0: return 0;
                break;
            case 1:
            {
                Str2CharList(in_str, inputword);
                while (result.getlength())
                    result.remove(1);
                MyDict.return_extend(in_str, result);
                if (result[1]==inputword)
                {
                    cout<<"\n";
                    break;
                }
                for (int i = 0; i < result.getlength(); ++i)
                {
                    if (i==0)
                    {
                        cout<<"Your input is: "<<inputword<<" \nThe extend of your word in the dictionary is: ";
                    }
                
                    cout << result[i+1] << ' ';
                }
                cout<<"\n\n";
                break;

            }
            case 2:
            {
                Str2CharList(in_str, inputword);
                while (result.getlength())
                    result.remove(1);
                MyDict.return_prefix(in_str, result);
                if (result[1]==inputword)
                {
                    cout<<"\n";
                    break;
                }
                for (int i = 0; i < result.getlength(); ++i)
                {
                    if (i==0)
                    {
                        cout<<"Your input is: "<<inputword<<" \nThe prefix of your word in the dictionary is: ";
                    }
                    cout << result[i+1] << ' ';
                }
                cout<<"\n\n";
                break;

            }

            case 3:
            {
                Str2CharList(in_str, inputword);
                while (result.getlength())
                    result.remove(1);
                MyDict.return_diff(in_str, result);
                if (result[1]==inputword)
                {
                    cout<<"\n";
                    break;
                }
                for (int i = 0; i < result.getlength(); ++i)
                {
                    if (i==0)
                    {
                        cout<<"Your input is: "<<inputword<<" \nThe correct word in the dictionary is: ";
                    }
                
                    cout << result[i+1] << ' ';
                }
                cout<<"\n\n";
                break;

            }
            case 4:
            {
                cout<<"please enter your new word: ";
                cin>>inputword;
            }
            default:
                break;
            }

        }
        while(op!=0);



        break;
    
    case 1:
    // original test


        /* Comment or uncomment different cases to sea if outputs are correct */
    //      Given test 1:       associate
    //      Expected output:    associated
    //    Str2CharList(in_str, "associate");

    //      Given test 2:       fo
    //      Expected output:    for
        Str2CharList(in_str, "fo");

        cout << "Test for part (i)" << endl;
        // Clear result list
        while (result.getlength())
            result.remove(1);
        MyDict.return_extend(in_str, result);
        for (int i = 0; i < result.getlength(); ++i)
            cout << result[i+1] << ' ';
        cout<<"\nthe golden output should be for"<<endl;
        /* ========== Tests for part (ii) ========== */
    //      Given test 1:       storeas
    //      Expected output:    store
        Str2CharList(in_str, "withy");

    //      Given test 2:       inn
    //      Expected output:    in
    //    Str2CharList(in_str, "ina");

        cout << "\nTest for part (ii)" << endl;
        // Clear result list
        while (result.getlength())
            result.remove(1);
        MyDict.return_prefix(in_str, result);
        for (int i = 0; i < result.getlength(); ++i)
            cout << result[i+1] << ' ';
        cout<<"\nthe golden output should be with"<<endl;

        /* ========== Tests for part (iii) ========== */
    //      Given test 1:       strong
    //      Expected output:    string
    //    Str2CharList(in_str, "strong");

    //      Given test 2:       than
    //      Expected output:    that
        Str2CharList(in_str, "than");

        cout << "\nTest for part (iii)" << endl;
        // Clear result list
        while (result.getlength())
            result.remove(1);
        MyDict.return_diff(in_str, result);
        for (int i = 0; i < result.getlength(); ++i)
            cout << result[i+1] << ' ';
        cout<<"\nthe golden output should be that"<<endl;

        return 0;

            break;
        }
}





/* ========== You do not need to modify anything below ==========  */
// Helper function, convert string to AList
void Str2CharList(AList<char> &list, string s) {
    while (list.getlength())
        list.remove(1);
    for (int i = 0; i < s.size(); ++i) {
        list.append(tolower(s[i]));
    }
}

// Helper function, split string by separator
vector<string> split(string str,string separator) {
    vector<string> result;
    int cutAt;
    while((cutAt = str.find_first_of(separator))!=str.npos){
        if(cutAt>0){
            result.push_back(str.substr(0,cutAt));
        }
        str=str.substr(cutAt+1);
    }
    if(str.length()>0){
        result.push_back(str);
    }
    return result;
}