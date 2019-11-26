#pragma once

template<class T>
class LinkedListNode {

	T* item;
	LinkedListNode* next;
	LinkedListNode* previous;

public:

	LinkedListNode();
	LinkedListNode(LinkedListNode* next, LinkedListNode* previous = nullptr);
	LinkedListNode(const T& item, LinkedListNode* next, LinkedListNode* previous = nullptr);
	//LinkedListNode(const LinkedListNode& linkedListNode);

	void setItem(const T& item);
	T& getItem() ;

	void setNext(LinkedListNode* next);
	LinkedListNode& getNext();

	void setPrevious(LinkedListNode* previous);
	LinkedListNode& getPrevious();

	LinkedListNode& operator=(const T& item);

};