//
//  solution.h
//

#ifndef TRIE_SOLUTION_H
#define TRIE_SOLUTION_H

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "trie.h"
using std::cout;
using std::cin;

// Helper function you may or may not use, convert AList<char> into string
string CharList2Str(AList<char> list) {
    string s;
    for (int i = 0; i < list.getlength(); ++i) {
        s += list[i+1];
    }
    return s;
}
/* ========== Function headers for Ex.2 (i) ========== */
template<class T> AList<string> trie<T>::return_extend(AList<T> list, AList<string> &result) {
    /* TODO */
    int num = 0;    //number of words match the requirements
    if (intrie(list))
        cout << "The word is already in the dictionary" << endl;

    for (char character = 97; character <= 122; character++)
    {
        list.append(character); //extend the given word by one symbol
        if(intrie(list))
        {
            result.append(CharList2Str(list));
            num++;
        }
        list.remove(list.getlength());
    }
    if (num == 0)
        cout << "No words match the requirements" << endl;
    return result;
}

/* ========== Function headers for Ex.2 (ii) ========== */
template<class T> AList<string> trie<T>::return_prefix(AList<T> list, AList<string> &result) {
    int num = 0;

    if (intrie(list))
        cout << "The word is already in the dictionary" << endl;

    for (int i = 1; i <= 2; i++)
    {
        list.remove(list.getlength());  //prefixes of the given word with one or two symbols less
        if(intrie(list))
        {
            result.append(CharList2Str(list));
            num++;
        }
    }
    if (num == 0)
        cout << "No words match the requirements" << endl;
    return result;
}

/* ========== Function headers for Ex.2 (iii) ========== */
template<class T> AList<string> trie<T>::return_diff(AList<T> list, AList<string> &result) {
    int num = 0;

    if (intrie(list))
        cout << "The word is already in the dictionary" << endl;

    for(int i = 0; i < list.getlength(); ++i)
    {
        for (char character = 97; character <= 122; character++)
        {
            char temp_char = list.getitem(i+1); //differ from the given word by exactly one symbol
            list.setitem(i+1, character);
            if(intrie(list))
            {
                result.append(CharList2Str(list));
                num++;
            }
            list.setitem(i+1, temp_char);
        }
    }
    if (num == 0)
        cout << "No words match the requirements" << endl;
    return result;
}

// Helper function you may or may not use
template<class T> bool trie<T>::contains_extend(trienode<T> *pt, AList<T> list, AList<T> path, AList<string> &result) {
    return 0;
}

// Helper function you may or may not use
template<class T> bool trie<T>::contains_diff(trienode<T> *pt, AList<T> list, AList<T> path, AList<string> &result, int diff) {
    return 0;
}

#endif //TRIE_SOLUTION_H
