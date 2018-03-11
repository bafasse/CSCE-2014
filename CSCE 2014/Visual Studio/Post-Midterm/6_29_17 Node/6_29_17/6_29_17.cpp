// 6_29_17.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;

//POD
template <class T>
struct Node
{
	int data;
	Node* next;
};

//template <class T>
//void print(const Node<T>* n)
//{
//	int count = 0;
//	for (Node<T>* cur = (Node<T>*) n; cur != NULL; cur->next)
//	{
//		cout << cur->data << " " << cur << " " << cur->next << endl;
//		count += 1;
//	}
//
//	// cur is cursor
//	Node<T>* cur = (Node<T>*) n;
//	while (cur != NULL)
//	{
//		cout << cur->data << " " << cur << " " << cur->next << endl;
//		count += 1;
//		cur = cur->next;
//	}
//
//	cout << "Count = " << count << endl;
//}

template <class T>
int countNodes(Node<T>* n)
{
	int count = 0;
	// cur is cursor
	Node<T>* cur = (Node<T>*) n;
	while (cur != NULL)
	{
		cout << cur->data << " " << cur << " " << cur->next << endl;
		count += 1;
		cur = cur->next;
	}

	return count;
}

int main()
{
	Node<int>* n = new Node<int>();
	Node<int>* n2 = new Node<int>();
	Node<int>* n3 = new Node<int>();
	Node<int>* n4 = new Node<int>();

	
	n->data = 5;
	n2->data = 1;
	n3->data = 9;
	n4->data = 7;

	// Linking process
	// & means address of (in this case)
	n->next = n2;
	n2->next = n3;
	n3->next = n4;
	n4->next = NULL;

	cout << countNodes((Node<int>*) NULL) << endl;

	delete n;
	delete n2;
	delete n3;
	delete n4;
    return 0;
}

