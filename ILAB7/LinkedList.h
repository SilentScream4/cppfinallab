#pragma once
#include "LinkedListNode.h"
#include "LinkedListIterator.h"

template<class T>
class LinkedList {

	LinkedListNode<T>* first;
	LinkedListNode<T>* last;
	int size;

public:

	LinkedList();
	LinkedList(const T& item);

	void add(const T& item);
	void removeLast();

	T& operator[](int index);

	LinkedListIterator begin();
	LinkedListIterator end();

};