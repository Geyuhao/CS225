//
//  bst.cpp
//  
//
//  Created by KD on 14.03.21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "bst.h"
using std::cout;
using std::cin;

/* the constructor creates a node with the given value and left and right pointers */

template<class T> node<T>::node(T item, node<T> *left, node<T> *right)
{
    data = item;
    pt_left = left;
    pt_right = right;
}

/* the get and set operations are obvious */
template<class T> T node<T>::getdata(void)
{
    return data;
}

template<class T> node<T> *node<T>::getleft(void)
{
    return pt_left;
}

template<class T> node<T> *node<T>::getright(void)
{
    return pt_right;
}

template<class T> void node<T>::setdata(T item)
{
    data = item;
    return;
}

template<class T> void node<T>::setleft(node<T> *pt)
{
    pt_left = pt;
    return;
}

template<class T> void node<T>::setright(node<T> *pt)
{
    pt_right = pt;
    return;
}

/* the constructor contains a trivial BST containing just a null pointer at the root */
template<class T> BST<T>::BST(void)
{
    root = 0;
}

/* the insert, delete and find functions are realised recursively starting from the root using the corresponding auxiliary functions */
template<class T> void BST<T>::insert(T item)
{
    root = _insert(root, item);
    return;
}

template<class T> void BST<T>::remove(T item)
{
    root = _delete(root, item);
    return;
}

template<class T> bool BST<T>::find(T item)
{
    return _find(root, item);
}

template<class T> node<T> *BST<T>::_insert(node<T> *pt, T val)
{
    if (pt == 0)
    /*  First check, if the root of the tree (given by the pointer pt) into which the value val is to be inserted is empty.
        In this case create and return a new node with the given value val and nullpointers for left and right successors. */
    {
        node<T> *newnode = new node<T>;
        (*newnode).setdata(val);
        return newnode;
    }
    /* Otherwise, we either have to insert into the left or right successor tree. In both cases the returned pointer pt_new will become the new value of the left or right successor pointer, resp. */
    if (val < (*pt).getdata())
    {
        node<T> *pt_new;
        pt_new = _insert((*pt).getleft(), val);
        (*pt).setleft(pt_new);
    }
    else if (val > (*pt).getdata())
    {
        node<T> *pt_new;
        pt_new = _insert((*pt).getright(), val);
        (*pt).setright(pt_new);
    }
    return pt;
}

template<class T> node<T> *BST<T>::_delete(node<T> *pt, T val)
{
    /* _delete searches recursively for the node with the given value val. If a nullpointer is reached, val does not appear in the BST, so no change is made.  */
    if (pt == 0)
        return pt;
    node<T> *pt_new;
    /* If the value val is found, the left and right successor trees must be merged. The auxiliary merge function returns a pointer to the root of the merge tree. This must be returned and stored in the position (left or right) that issued the call. */
    if ((*pt).getdata() == val)
    {
        pt_new = merge((*pt).getleft(), (*pt).getright());
        return pt_new;
    }
    /* The recursive descent follows the left subtree or the right subtree. The call of _delete returns a pointer to the root of the modified tree. This must be returned and stored in the position (left or right) that issued the call.*/
    if (val < (*pt).getdata())
    {
        pt_new = _delete((*pt).getleft(), val);
        (*pt).setleft(pt_new);
    }
    else
    {
        pt_new = _delete((*pt).getright(), val);
        (*pt).setright(pt_new);
    }
    return pt;
}

/* _find works in the same way as _delete, but only a truth value is returned. */
template<class T> bool BST<T>::_find(node<T> *pt, T val)
{
    if (pt == 0)
        return false;
    if ((*pt).getdata() == val)
        return true;
    if (val < (*pt).getdata())
        return _find((*pt).getleft(), val);
    return _find((*pt).getright(), val);
}

template<class T> node<T> *BST<T>::merge(node<T> *pt1, node<T> *pt2)
{
    /* if there is no right successor tree, the left successor tree is automatically the result of the merge */
    if (pt2 == 0)
        return pt1;
    /* Otherwise, if the right successor tree has no left successor, make the given tree (pointed to by pt1) the new left successor instead of null. */
    if ((*pt2).getleft() == 0)
    {
        (*pt2).setleft(pt1);
        return pt2;
    }
    /* If the right successor (given by pointer pt2) has a non-empty left successor tree, insert the given tree (pointed to by pt1) into this left successor. */
    (*pt2).setleft(merge(pt1, (*pt2).getleft()));
    return pt2;
}

template<class T> void BST<T>::display(void)
{
    _display(root);
}

/* Iterate through the tree in order of the order < on T, i.e. first the left subtree, then the root, then the right subtree. */
template<class T> void BST<T>::_display(node<T> * pt)
{
    if (pt != 0)
    {
        _display((*pt).getleft());
        cout << (*pt).getdata() << " ; ";
        _display((*pt).getright());
    }
    return;
}



/* ASSIGNMENT 6 - EXERCISE 2 
 * The delete operation on binary search trees presented in the lectures merges the two successor trees, 
 * when an element labelling a non-leaf vertex is deleted. One might as well re-insert all the elements.
 * (i) Implement this alternative for the implementation of delete. 
 * 
 * The input and output here are the same as _delete. 
 * You may follow the structure of _delete but re-inserting all the elements instead of merging. */
template<class T> node<T> *BST<T>::_delete_with_reinsert(node<T> *pt, T val)
{
    node<T> *origin = root;

    // node is the node to be deleted
    node<T> *node =findhandle(root,val,origin);
    //cout<<" (Origin,Node) is ("<<origin->getdata()<<","<<node->getdata()<<")\n";

    if (origin->getleft() == NULL || origin->getleft()->getdata() != val)
    {
        //cout<<"delete "<<val <<"\n";
        origin->setright(NULL);
    } else if (origin->getright() == NULL || origin->getright()->getdata() != val)
    {
        //cout<<"delete "<<val<<"\n";
        origin->setleft(NULL);
    } else
    {
        if (root->getdata() == val)
        {
            //cout<<"delete "<<val<<"\n";
            root = NULL;
        } else
        {
            //cout <<"\nERROR when find the node\n";
            return NULL;
        }
    }

    if (node->getleft() != NULL)
    {
        insert_subtree(node->getleft());
    }    
    
    if (node->getright() != NULL)
    {
        insert_subtree(node->getright());
    }

    return root;
}

/* analogous to BST<T>::remove */
template<class T> void BST<T>::remove_with_reinsert(T item)
{
    root = _delete_with_reinsert(root,item);
    return;
}

// insert all the nodes or a subtree into the tree
template<class T> void BST<T>::insert_subtree(node<T> *pt)
{
    if (pt == NULL)
    {
        return;
    }
    int length = 100;
    T subtree[length];
    int num_item = 0;

    _insert_subtree(subtree,pt,num_item);
    for (int i = 0; i<num_item; i++)
    {
        //cout<<subtree[i]<<" is inserted\n";
        insert(subtree[i]);
    }
}

// find all the nodes after one subtree root
template<class T> void BST<T>::_insert_subtree(T* subtree, node<T> *pt, int &num_item)
{
    if(pt->getleft() == NULL && pt->getright() == NULL)
    {
        T data = pt->getdata();
        subtree[num_item] = data;
        num_item++;
    } else if (pt->getleft() == NULL && pt->getright() != NULL)
    {
        T data = pt->getdata();
        subtree[num_item] = data;
        num_item++;
        _insert_subtree(subtree,pt->getright(),num_item);
    } else if (pt->getright() == NULL && pt->getleft() != NULL)
    {
        T data = pt->getdata();
        subtree[num_item] = data;
        num_item++;
        _insert_subtree(subtree,pt->getleft(),num_item);
    } else
    {
        T data = pt->getdata();
        subtree[num_item] = data;
        num_item++;
        _insert_subtree(subtree,pt->getright(),num_item);
        _insert_subtree(subtree,pt->getleft(),num_item);
    }
}

// find the pointer of a node, and note the parennt of it
template<class T> node<T>* BST<T>::findhandle(node<T> *pt, T val, node<T>* &origin)
{
    if (pt == 0)
        return NULL;

    if ((*pt).getdata() == val)
        return pt;

    if (val < (*pt).getdata())
    {
        origin = pt;
        cout<<origin->getdata();
        return findhandle((*pt).getleft(), val,origin);
    }

    //cout<<origin->getdata();
    origin = pt;
    return findhandle((*pt).getright(), val,origin);
}
