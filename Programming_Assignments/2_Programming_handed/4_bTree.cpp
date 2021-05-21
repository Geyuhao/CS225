/* B-Tree
 * Author:	Caleb Baker
 * Date:	10/8/17
 * Summary:	A B-Tree data structure. Supports lg(n) time search, insert, and delete.
 */


#include <stdlib.h>
#include <utility>
#include <stdio.h>
#include "4_bTree.h"

using namespace std;


#define NEW_ROOT 2
#define MODIFIED_NOT_ROOT 1
#define NOT_MODIFIED 0


// Constructor for b tree.
// t is the minimum degree of the tree.
// compare is the comparison function used for managing elements within the tree.
// printK is a function that prints keys.
template <typename T>
BTree<T>::BTree(unsigned t, bool (*compare)(T, T), bool (*isequal)(T, T), void (*printK)(pair<T, Blocks<T> *>)) {
	minDegree = t;
	lessThan = compare;

	// added
	checkequal = isequal;

	root = (BNode<T>*) malloc(sizeof(BNode<T>));
	initializeNode(root);
	root->leaf = true;
	printKey = printK;
}

// Destructor.
template <typename T>
BTree<T>::~BTree<T>() {
	freeNode(root);
}

// Inserts the key k into the tree.
template <typename T>
void BTree<T>::insert(T k) {

	// Grow upwards if the root is full.
	if (root->size == 2 * minDegree - 1) {
		BNode<T> *newRoot = (BNode<T>*) malloc(sizeof(BNode<T>));
		initializeNode(newRoot);
		newRoot->leaf = false;
		newRoot->child[0] = root;
		root = newRoot;
		splitChild(newRoot, 0);
	}
	// Work down the tree.
	BNode<T> *curr = root;
	
	while (!curr->leaf) {

		int index = curr->size - 1;
		while (index >= 0 && ( lessThan(k, curr->key[index].first) || checkequal(k, curr->key[index].first) ) )
		{
			index--;
		}
		index ++;

		if (curr->key[index].first.people != NULL && checkequal(k,curr->key[index].first))
		{	
			Blocks<T>* the_block = curr->key[index].second;
			the_block->block.push_back(k);
			return;
		}
		
		// Split child if full.
		if (curr->child[index]->size == 2 * minDegree - 1) {
			splitChild(curr, index);
			if (lessThan(curr->key[index].first, k)) {
				index++;
			}
		}
		curr = curr->child[index];
	}


	int index = curr->size - 1;
	while (index >= 0 && ( lessThan(k, curr->key[index].first) || checkequal(k, curr->key[index].first) ) )
	{
		index--;
	}
	index ++;


	if (curr->key[index].first.people != NULL && checkequal(k,curr->key[index].first))
	{	
		Blocks<T>* the_block = curr->key[index].second;
		the_block->block.push_back(k);
		return;
	}

	Blocks<T>* a = new Blocks<T>;
	a->block.push_back(k);
	pair<T, Blocks<T>* > key(k,a);

	nodeInsert(curr, key);
	
}


// Removes k from the tree. Returns the removed key.
// Throws a BTREE_EXCEPTION if key is not found.
template <typename T>
T BTree<T>::remove(T k) {
	BNode<T> *curr = root;
	while (true) {
		unsigned i = findIndex(curr, k);

		// If the item to be deleted has been found.
		if (i < curr->size && !(lessThan(curr->key[i].first, k) || lessThan(k, curr->key[i].first))) {
			T toReturn = curr->key[i].first;

			// If at a leaf, just delete it.
			if (curr->leaf) {
				nodeDelete(curr, i);
			}

			// Otherwise replace with predecessor/successor or merge children.
			else {
				BNode<T> *leftKid = curr->child[i];
				BNode<T> *rightKid = curr->child[i + 1];

				// Replace with predecessor.
				if (leftKid->size >= minDegree) {
					while (!(leftKid->leaf)) {
						fixChildSize(leftKid, leftKid->size);
						leftKid = leftKid->child[leftKid->size];
					}
					curr->key[i].first = nodeDelete(leftKid, leftKid->size - 1);
				}

				// Replace with successor
				else if (rightKid->size >= minDegree) {
					while (!(rightKid->leaf)) {
						fixChildSize(rightKid, 0);
						rightKid = rightKid->child[0];
					}
					curr->key[i].first = nodeDelete(rightKid, 0);
				}

				// Merge children and move down the tree.
				else {
					mergeChildren(curr, i);
					curr = leftKid;
					continue;
				}
			}
			return toReturn;
		}

		// If the item has not been found, move down the tree.
		else {

			// If at a leaf, then the item isn't present.
			if (curr->leaf) {
				throw (BTREE_EXCEPTION) REMOVE_KEY_NOT_FOUND;
			}

			// Adjust curr and move down the tree.
			char result = fixChildSize(curr, i);
			if (result == NEW_ROOT) {
				curr = root;
			}
			else {
				curr = curr->child[findIndex(curr, k)];
			}
		}
	}
}


// Function to find a key in the tree.
// returnValue.first is the node the item is in.
// returnValue.second is the correct index in that node's key array
template <typename T>
pair<BNode<T>*, unsigned> BTree<T>::search(T k) {

	// Start at root.
	BNode<T> *x = root;

	// Work down the tree.
	while (true) {

		// Find the proper index in the current node's array.
		unsigned i = findIndex(x, k);

		// Found it!
		if (i < x->size && !(lessThan(k, x->key[i].first) || lessThan(x->key[i].first, k))) {
			return pair<BNode<T>*, unsigned>(x, i);
		}

		// Hit the bottom of the tree.
		else if (x->leaf) {
			return pair<BNode<T>*, unsigned>(NULL, 0);
		}

		// Keep going.
		else {
			x = x->child[i];
		}
	}
}


// Function to find a key in the tree.
// Returns the key.
// If the item was not found an exception is thrown.
template <typename T>
T BTree<T>::searchKey(T k) {
	pair<BNode<T>*, unsigned> node = search(k);
	if (node.first == NULL) {
		throw (BTREE_EXCEPTION) SEARCH_KEY_NOT_FOUND;
	}
	return node.first->key[node.second].first;
}


// Function for printing a tree.
template <typename T>
void BTree<T>::print() {
	if (printKey != NULL && root != NULL) {
		printf("\n");
		printNode(root, 0);
		printf("\n");
	}
}


// Initialize a b tree node.
// x is a pointer to the node
// t is the minimum degree of the tree.
template <typename T>
void BTree<T>::initializeNode(BNode<T> *x) {
	x->size = 0;
	x->key = (pair<T, Blocks<T>* >*) malloc((2 * minDegree - 1) * sizeof(pair<T, Blocks<T>* >));
	x->key->second = new Blocks<T>;
	x->child = (BNode<T>**) malloc(2 * minDegree * sizeof(BNode<T>*));
}


// Recursively deletes the subtree rooted at x.
// Does the dirty work for the destructor.
template <typename T>
void BTree<T>::freeNode(BNode<T> *x) {
	if (!x->leaf) {
		for (unsigned i = 0; i <= x->size; i++) {
			freeNode(x->child[i]);
		}
	}
	free(x->child);
	free(x->key);
	free(x);
}


// Finds the index of k in x->key.
// If k is not present, returns the index of the subtree
// that could contain k in x->child.
template <typename T>
unsigned BTree<T>::findIndex(BNode<T> *x, T k) {
	unsigned i = 0;
	while (i < x->size && lessThan(x->key[i].first, k)) {
		i++;
	}
	return i;
}


// Inserts k into x.
// Returns the index of k in x->key.
template <typename T>
unsigned BTree<T>::nodeInsert(BNode<T> *x, std::pair<T, Blocks<T>* > k) {
	int index;

	// Make room for k.
	for (index = x->size; index > 0 && lessThan(k.first, x->key[index - 1].first); index--) {
		x->key[index] = x->key[index - 1];
		x->child[index + 1] = x->child[index];
	}

	// Insert k.
	x->child[index + 1] = x->child[index];
	x->key[index] = k;
	x->size++;
	

	return index;
}


// Deletes the indexth element from x->key.
// Returns deleted key.
template <typename T>
std::pair<T, Blocks<T>* > BTree<T>::nodeDelete(BNode<T> *x, unsigned index) {

	T toReturn = x->key[index];

	x->size--;
	while (index < x->size) {
		x->key[index] = x->key[index + 1];
		x->child[index + 1] = x->child[index + 2];
		index++;
	}
	return toReturn;
}


// Function for splitting nodes that are too full.
// x points to the parent of the node to splits.
// i is the index in x's child array of the node to split.
template <typename T>
void BTree<T>::splitChild(BNode<T> *x, int i) {

	// newNode is the new node and toSplit is the node to split.
	BNode<T> *toSplit = x->child[i];
	BNode<T>* newNode = (BNode<T>*) malloc(sizeof(BNode<T>));
	initializeNode(newNode);
	newNode->leaf = toSplit->leaf;
	newNode->size = minDegree - 1;

	// Copy the second half of y's keys and children into z.
	for (unsigned j = 0; j < minDegree - 1; j++) {
		newNode->key[j] = toSplit->key[j + minDegree];
	}
	if (!toSplit->leaf) {
		for (unsigned j = 0; j < minDegree; j++) {
			newNode->child[j] = toSplit->child[j + minDegree];
		}
	}
	toSplit->size = minDegree - 1;

	nodeInsert(x, toSplit->key[minDegree - 1]);
	x->child[i + 1] = newNode;
}


// Merges the (i + 1)th child of parent with the ith child of parent.
// Returns an indicator of whether the change affected the root.
template <typename T>
char BTree<T>::mergeChildren(BNode<T> *parent, unsigned i) {

	BNode<T> *leftKid = parent->child[i];
	BNode<T> *rightKid = parent->child[i + 1];

	// Move item from parent to left child.
	leftKid->key[leftKid->size] = nodeDelete(parent, i);
	unsigned j = ++(leftKid->size);

	// Move everything from rightKid into leftKid
	for (unsigned k = 0; k < rightKid->size; k++) {
		leftKid->key[j + k] = rightKid->key[k];
		leftKid->child[j + k] = rightKid->child[k];
	}
	leftKid->size += rightKid->size;
	leftKid->child[leftKid->size] = rightKid->child[rightKid->size];

	// Free the memory used by rightChild
	free(rightKid->child);
	free(rightKid->key);
	free(rightKid);

	// If parent is empty, than it must have been the root.
	if (parent->size == 0) {
		root = leftKid;
		free(parent->child);
		free(parent->key);
		free(parent);
		return NEW_ROOT;
	}

	return MODIFIED_NOT_ROOT;
}


// Makes sure parent->child[index] has at least minDegree items.
// If it doesn't, then things are changed to make sure it does.
// Returns a code indicating what action was taken.
template <typename T>
char BTree<T>::fixChildSize(BNode<T> *parent, unsigned index) {
	BNode<T> *kid = parent->child[index];

	// If things need fixed.
	if (kid->size < minDegree) {

		// Borrow from left sibling if possible.
		if (index != 0 && parent->child[index - 1]->size >= minDegree) {
			BNode<T> *leftKid = parent->child[index - 1];

			// When there are numerous equivalent keys,
			// nodeInsert can insert into an index other than 0.
			// The for loop fixed child pointers if that happens.
			for (unsigned i = nodeInsert(kid, parent->key[index - 1]); i != 0; i--) {
				kid->child[i] = kid->child[i - 1];
			}
			kid->child[0] = leftKid->child[leftKid->size];
			parent->key[index - 1] = nodeDelete(leftKid, leftKid->size - 1);
		}

		// Borrow from right sibling if possible
		else if (index != parent->size && parent->child[index + 1]->size >= minDegree) {
			BNode<T> *rightKid = parent->child[index + 1];
			// Move curr->key[i] into kid->key
			nodeInsert(kid, parent->key[index]);
			kid->child[kid->size] = rightKid->child[0];
			rightKid->child[0] = rightKid->child[1];
			// Move rightKid->key[0] into curr->key
			parent->key[index] = nodeDelete(rightKid, 0);
		}

		// If borrowing is not possible, then merge.
		else if (index != 0) {
			return mergeChildren(parent, index - 1);
		}
		else {
			return mergeChildren(parent, index);
		}
		return MODIFIED_NOT_ROOT;
	}

	// If things don't need fixed.
	return NOT_MODIFIED;
}


// Recursize function for printing a tree or subtree.
// node is the root of the subtree to be printed.
// tab is how far to indent the subtree.
template <typename T>
void BTree<T>::printNode(BNode<T> *node, unsigned tab) {

	// Indent
	for (unsigned i = 0; i < tab; i++) {
		printf("\t");
	}

	// Print the current node.
	for (unsigned i = 0; i < node->size; i++) {
		printKey(node->key[i]);
	}

	// Print all child nodes.
	if (!node->leaf) {
		//tab++;
		for (unsigned i = 0; i <= node->size; i++) {
			printNode(node->child[i], tab);
		}
	}
}

// added for PA2, compare functions on People's register date
bool smaller(Person_BP a,Person_BP b)
{
	pair<int,int> a_date = a.people->register_date;
	pair<int,int> b_date = b.people->register_date;

	int daya = a_date.first*100 + a_date.second;
	int dayb = b_date.first*100 + b_date.second;

    if (daya < dayb) return true;
    else return false;
}

bool equalkey(Person_BP a, Person_BP b)
{
	pair<int,int> a_date = a.people->register_date;
	pair<int,int> b_date = b.people->register_date;

	int daya = a_date.first*100 + a_date.second;
	int dayb = b_date.first*100 + b_date.second;

	//cout <<"a is "<< daya << " b is " << dayb <<endl;
    if (daya == dayb) return true;
    else return false;
}

// display node information
void printkey(pair<Person_BP, Blocks<Person_BP>* > one_person)
{
	if (one_person.first.people == NULL)
	{
		cout << "The input is NULL pt"<<endl;
		return;
	}
	pair<int,int> date = one_person.first.people->register_date;
    printf("(%d,%d)",date.first,date.second);
	one_person.second->print_block();
}

template <typename T>
Blocks<T>*  BTree<T>::search_block(int month, int day)
{
	People* c = new People;
	Person_BP haha = Person_BP(c);
	haha.people->register_date.first = month;
	haha.people->register_date.second = day;
	std::pair<BNode<Person_BP>*, unsigned int> find = search(haha);

	if (find.first == NULL)
	{
		cout << "\n\033[33mNo one is registered on "<<month<<","<<day<<"\033[0m"<<endl;
		return NULL;
	}

	Blocks<Person_BP>* pblock = find.first->key[find.second].second;
	pblock->print_block();
	return pblock;
}

template <typename T>
void BTree<T>::register2btree(People* person)
{
	Person_BP* biga = new Person_BP(person);
	insert(*biga);
}


/*int main()
{
    BTree<Person_BP> mybtree(4,smaller,equalkey,printkey);
    

	for (int i = 0; i<20; i++)
	{
		People* a = new People;
		a->register_date.first = i;
		a->register_date.second = i;
		a->id_number = i+5;
		Person_BP* biga = new Person_BP(a);
		mybtree.insert(*biga);
	}

	for (int i = 0; i<10; i++)
	{
		People* a = new People;
		a->register_date.first = i;
		a->register_date.second = i;
		a->id_number = i+5;
		Person_BP* biga = new Person_BP(a);
		mybtree.insert(*biga);
	}


	mybtree.print();

	int month;
	int day;
	cout << "You can find all the people that registered in one day"<<endl;
	cout << "Which day do you want to search (which mounth?): ";
	cin >> month;

	cout << "Which day do you want to search (which day?): ";
	cin >> day;

	mybtree.search_block(month,day);
}*/