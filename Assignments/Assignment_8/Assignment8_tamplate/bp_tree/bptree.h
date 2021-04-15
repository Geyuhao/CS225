//Author: Shashikant Kadam
//Roll number 16CSE1026
/*****B+ Tree*****/
#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<climits>
using namespace std;
int MAX; //size of each node
class BPTree; //self explanatory classes
class Node
{
	bool IS_LEAF;
	int *key, size;
	Node** ptr;
	friend class BPTree;
public:
	Node();
};
class BPTree
{
	Node *root;
	void insertInternal(int,Node*,Node*);
	void removeInternal(int,Node*,Node*);
	Node* findParent(Node*,Node*);
public:
	BPTree();
	void search(int);
	void insert(int);
	void remove(int);
	void display(Node*);
	Node* getRoot();
	void cleanUp(Node*);

	// function declaration for Assignment_8 Ex2;
	int find_min();
	int find_max();
	int findSucc(int id);
	int findPrec(int id);
	
	~BPTree();
};