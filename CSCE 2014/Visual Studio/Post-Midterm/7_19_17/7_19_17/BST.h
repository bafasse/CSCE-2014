#pragma once
#ifndef BST_H
#define BST_H

// Necessary for print()
#include <algorithm>
#include <iostream>
using namespace std;

// Represents a single Node in the BST.
template <class T>
struct Node
{
	T data;
	int count;
	Node<T>* left;
	Node<T>* right;
};

// This is an implementation of a simple Binary Search Tree (BST).
// The tree is composed of nodes, each of which has data and a
// left and right child. No guarantees are made that the tree will
// remain balanced, but most operations should be O(lg N) with random
// data.
template <class T>
class BST
{
public:
	// Constructors / Destructors
	BST();
	BST(const BST<T>& orig);
	~BST();

	// Tree modification
	void insert(const T& value);

	// Tree statistics
	bool search(const T& value) const;
	bool select(const int k, T& value) const;
	void print() const;
	int count() const;
	int height() const;

private:
	Node<T>* mRoot;

	// Private helper functions. These do all the real work
	// for the recursive algorithms, but we expose a simpler
	// API to the user so they don't have to worry about the
	// implementation details.
	void copyHelper(Node<T>* src, Node<T>*& dest);
	void destroyHelper(Node<T>* root);
	void insertHelper(const T& value, Node<T>*& root);

	bool searchHelper(const T& value, const Node<T>* root) const;
	bool selectHelper(const int k, T& value, const Node<T>* root) const;
	void printHelper(const Node<T>* root) const;
	int countHelper(const Node<T>* root)  const;
	int heightHelper(const Node<T>* root) const;
};

// ----------------------------------------------------//

template <class T>
BST<T>::BST()
{
	mRoot = NULL;
}

// ----------------------------------------------------//

template <class T>
BST<T>::BST(const BST<T>& orig)
{
	mRoot = NULL;
	copyHelper(orig.mRoot, mRoot);
}

template <class T>
void BST<T>::copyHelper(Node<T>* src, Node<T>*& dest)
{
	// 'src' was empty - nothing to clone
	if (src == NULL)
		dest = NULL;

	else
	{
		// Turn 'dest' into a clone of 'src'
		dest = new Node<T>();
		dest->data = src->data;
		dest->count = src->count; // CHANGE HERE
		dest->left = NULL;
		dest->right = NULL;

		// Recursively clone the left and right children
		copyHelper(src->left, dest->left);
		copyHelper(src->right, dest->right);
	}
}

// ----------------------------------------------------//

template <class T>
BST<T>::~BST()
{
	destroyHelper(mRoot);
	mRoot = NULL;
}

template <class T>
void BST<T>::destroyHelper(Node<T>* root)
{
	// Use a postorder traversal for deletion. Delete both
	// the left and right children before we delete ourselves.
	if (root != NULL)
	{
		destroyHelper(root->left);
		destroyHelper(root->right);
		delete root;
	}
}

// ----------------------------------------------------//

template <class T>
void BST<T>::insert(const T& value)
{
	insertHelper(value, mRoot);
}

template <class T>
void BST<T>::insertHelper(const T& value, Node<T>*& root)
{
	// When 'root' is NULL, we've found where to insert the value
	if (root == NULL)
	{
		root = new Node<T>();
		root->data = value;
		root->count = 1; // CHANGE HERE
		root->left = NULL;
		root->right = NULL;
	}

	// Recurse either to the left or to the right to determine
	// where 'value' should be placed.
	else if (root->data > value)
	{
		insertHelper(value, root->left);
		++root->count; // CHANGE HERE
	}
	else
	{
		insertHelper(value, root->right);
		++root->count; // CHANGE HERE
	}
}


// ----------------------------------------------------//

template <class T>
bool BST<T>::search(const T& value) const
{
	return searchHelper(value, mRoot);
}

template <class T>
bool BST<T>::searchHelper(const T& value, const Node<T>* root) const
{
	// If the subtree is empty, we didn't find 'value'
	if (root == NULL) return false;

	// We found 'value'!
	else if (root->data == value) return true;

	// We have to search either the left or the right
	// subtree using binary search.
	else if (root->data > value)
		return searchHelper(value, root->left);
	else return searchHelper(value, root->right);
}

// ----------------------------------------------------//

template <class T>
bool BST<T>::select(const int k, T& value) const
{
	return selectHelper(k, value, mRoot);
}

template <class T>
bool BST<T>::selectHelper(const int k, T& value, const Node<T>* root) const
{
	// k is not a valid index.
	if (root == NULL) return false;

	// Figure out how many nodes are in root->left's subtree
	int leftCount = countHelper(root->left);

	// We found the 'kth' node. Save the data and return.
	if (leftCount == k)
	{
		value = root->data;
		return true;
	}

	// If there are more nodes in the left tree than we need,
	// we'll have to look inside the left tree to find the kth
	// element.
	else if (leftCount > k) return selectHelper(k, value, root->left);

	// We can rule out everything in the left subtree as well as
	// 'root'. We need to find the 'k - leftCount - 1' element
	// in the right subtree.
	else return selectHelper(k - leftCount - 1, value, root->right);
}

// ----------------------------------------------------//

template <class T>
void BST<T>::print() const
{
	printHelper(mRoot);
	cout << endl;
}

template <class T>
void BST<T>::printHelper(const Node<T>* root) const
{
	// If the tree is empty, there is nothing to print
	if (root == NULL)
		return;

	// Use an in-order traversal to print the tree's contents.
	// An in-order traversal will print the data in sorted order.
	printHelper(root->left);
	cout << root->data << " ";
	printHelper(root->right);
}

// ----------------------------------------------------//

template <class T>
int BST<T>::count() const
{
	return countHelper(mRoot);
}

template <class T>
int BST<T>::countHelper(const Node<T>* root) const
{
	if (root == NULL) return 0;
	else return root->count; // CHANGE HERE 
}

// ----------------------------------------------------//

template <class T>
int BST<T>::height() const
{
	return heightHelper(mRoot);
}

template <class T>
int BST<T>::heightHelper(const Node<T>* root) const
{
	if (root == NULL) return 0;
	else return 1 + max(heightHelper(root->left), heightHelper(root->right));
}

#endif