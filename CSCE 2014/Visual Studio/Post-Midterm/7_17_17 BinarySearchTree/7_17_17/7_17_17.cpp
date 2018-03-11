// 7_17_17.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <algorithm>
#include <iostream>
using namespace std;

template <class T>
struct Node
{
	T data;
	Node<T>* left;
	Node<T>* right;
};

template <class T>
int count(const Node<T>* root)
{
	if (root == NULL) return 0;
	else return 1 + count(root->left) + count(root->right);
}

template <class T>
int height(const Node<T>* root)
{
	if (root == NULL) return 0;
	else return 1 + max(height(root->left), height(root->right));
}

template <class T>
void print(const Node<T>* root)
{
	if (root != NULL)
	{
		print(root->left);
		cout << root->data << " ";
		print(root->right);
	}
}

template <class T>
T maximum(const Node<T>* root)
{
	if (root == NULL) return T();
	else if (root->right == NULL) return root->data;
	else return maximum(root->right);
}

template <class T>
T minimum(const Node<T>* root)
{
	if (root == NULL) return T();
	else if (root->left == NULL) return root->data;
	else return minimum(root->left);
}

int main()
{
	Node<int> n1;
	Node<int> n2;
	Node<int> n3;
	Node<int> n4;
	Node<int> n5;
	Node<int> n6;

	n1.data = 5;
	n2.data = -5;
	n3.data = 3;
	n4.data = 7;
	n5.data = 6;
	n6.data = 10;

	n1.left = &n2;
	n1.right = &n4;

	n2.left = NULL;
	n2.right = &n3;

	n3.left = NULL;
	n3.right = NULL;

	n4.left = &n5;
	n4.right = &n6;

	n5.left = NULL;
	n5.right = NULL;

	n6.left = NULL;
	n6.right = NULL;

	cout << "Count = " << count(&n1) << endl;
	cout << "Height = " << height(&n1) << endl;
	print(&n1);
	cout << endl;
	cout << "Max = " << maximum(&n1) << endl;
	cout << "Min = " << minimum(&n1) << endl;
    return 0;
}

