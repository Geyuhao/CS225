#ifndef B_TREE
#define B_TREE


#include <iostream>
#include <stdio.h>

using namespace std;
/* In BtreeNode class 
   We just store the key and we do not store value 
   if you want, you can modify the class definition of Btree Node.
*/
class BtreeNode
{
	int *a;		// list to store the keyvalues
	BtreeNode **C;		// list to store the pointers
	int n;		// number of keys;
	int t;		// id num?
	bool leaf;	// indicates whether it is leaf node
public:
    BtreeNode(int t, bool leaf);
	int findId(int k);
	void remove(int k);
	void removeFromLeaf(int id);
	void removeFromNonLeaf(int id);
	void borrowFromPrev(int id);
	void borrowFromSucc(int id);
	int findSucc(int id);
	int findPrec(int id);
	void merge(int id);
	void fill(int id);
	void traverse();
	BtreeNode *search(int k);
	void insertNonFull(int k);
	void splitChild(int i,BtreeNode *y);

friend class Btree;
};

// Constructor for class BtreeNode
BtreeNode::BtreeNode(int t,bool leaf)
{
	this->t = t;
	this->leaf = leaf;
	a = new int[2*t-1];		// key value
	C = new BtreeNode*[2*t];	// child pointers
    n = 0;
}



class Btree
{
	BtreeNode* root;
	int t;
public:
	Btree(int t);
	void insert(int k);
	void remove(int k);
	void traverse()
	{
		if(root == NULL) return;
		else
			root->traverse();
	}
	BtreeNode *search(int k)
	{
		return (root==NULL) ? NULL : root->search(k);
	}

	// function decalaration for Assignment_8 Ex1
    int find_max();
    int find_min();
	int findSucc(int id);
	int findPrec(int id);
};
// Constructor for Btree
Btree::Btree(int t)
{
	root = new BtreeNode(t, true);
	this->t = t;
}
#endif