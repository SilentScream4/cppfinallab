#pragma once
#include "LinkedList.h"

template<class T>
class LinkedListIterator {

	LinkedList<T>* linkedList;
	LinkedListNode<T>* current;
	int size;
	int currentIndex;

public:

	LinkedListIterator(LinkedList<T>* linkedList, int index = 0);
	LinkedListIterator(const LinkedListIterator& iterator);

	friend LinkedListIterator operator+(const LinkedListIterator&, const int);
	friend LinkedListIterator operator-(const LinkedListIterator&, const int);

	friend bool operator>(const LinkedListIterator&, const int);
	friend bool operator<(const LinkedListIterator&, const int);

	LinkedListIterator operator++();
	LinkedListIterator& operator++(int);

	LinkedListIterator operator--();
	LinkedListIterator& operator--(int);

};