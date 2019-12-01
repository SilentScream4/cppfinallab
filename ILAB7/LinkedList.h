#pragma once
#include "Exception.h"

/* Linked List class - consists of linked nodes containing items of type T.
   Only consecutive iteration using iteratior is allowed. Changing connections between links is possible
   but is unsafe - will lead to memory leaking. Can be iterated both backward and forward */
template<class T>
class LinkedList {

	/* Nested Linked List Node class - Linked List node containing links to previous and/or next nodes
	   and an item. Is unaccessable out of Linked List class */
	class LinkedListNode {

		T* item;
		LinkedListNode* next;
		LinkedListNode* previous;

	public:

		friend class LinkedList;
		friend class LinkedList::LinkedListIterator;

#pragma region Constructors

		/* Instantiates an empty node with no connections */
		LinkedListNode() {
			item = nullptr;
			next = nullptr;
			previous = nullptr;
		}

		/* Instantiates a node with specified connections (connections may be null) */
		LinkedListNode(LinkedListNode* next, LinkedListNode* previous) {
			item = nullptr;
			this->next = next;
			this->previous = previous;
		}

		/* Instantiates a node containing a copy of @item with specified connections (connections may be null) */
		LinkedListNode(const T& item, LinkedListNode* next, LinkedListNode* previous) {
			this->item = new T(item);
			this->next = next;
			this->previous = previous;
		}

#pragma endregion

		/* Cleans up memory (deletes contained item if any was added) */
		~LinkedListNode() {
			if (item != nullptr)
				delete item;
		}

#pragma region Setters and getters

		/* Deletes current item if any was contained and saves a copy of @item */
		void setItem(const T& item) {
			if (this->item != nullptr)
				delete this->item;
			this->item = new T(item);
		}

		/* Return a reference to the item (mutable) */
		T& getItem() {
			return *item;
		}

		/* Sets (links) node @next as this node's next node (not vice versa) */
		void setNext(LinkedListNode* next) {
			this->next = next;
		}

		/* Returns this node's next node as a reference */
		LinkedListNode& getNext() {
			return *next;
		}

		/* Sets (links) node @previous as this node's previous node (not vice versa) */
		void setPrevious(LinkedListNode* previous) {
			this->previous = previous;
		}

		/* Returns this node's previous node as a reference */
		LinkedListNode& getPrevious() {
			return *previous;
		}

#pragma endregion

		/* Deletes current item if any was contained and saves a copy of @item */
		LinkedListNode& operator=(const T& item) {
			setItem(item);
			return *this;
		}

	};

	LinkedListNode* first;  // Linked list's first node
	LinkedListNode* last;	// Linked list's last node
	int size;				// Amount of used linked nodes

public:

	class LinkedListIterator;

	/* Instantiates an empty linked list with a single empty node */
	LinkedList() {
		first = new LinkedListNode();
		last = first;
		size = 0;
	}

	/* Instantiates a linked list with a single node containing a copy of @item */
	LinkedList(const T& item) {
		first = new LinkedListNode(item, nullptr);
		last = first;
		size = 1;
	}

	/* Cleans up memory (deletes every created node). Doesn't delete nodes, that were disconnected */
	~LinkedList() {
		LinkedListNode* current = first;
		LinkedListNode* previous = first;
		for (int i = 0; i < size; ++i) {
			current = current->next;
			delete previous;
			previous = current;
		}
		delete current;
	}

	/* Adds an item to the linked list. Uses avaialable unused node or creates a new one */
	void add(const T& item) {
		if (size == 0) {
			first->setItem(item);
			size++;
			return;
		}
		if (last->next == nullptr)
			last->next = new LinkedListNode(item, nullptr, last);
		else last->next->setItem(item);
		last = last->next;
		size++;
	}

	/* Removes last added item from the list. Doesn't clean up memory (leaves it to be reused) */
	void removeLast() {
		if (size > 1) {
			size--;
			last = last->previous;
		}
		else if (size == 0) size--;
	}

	/* Return item contained in node at @index */
	T& operator[](int index) {
		if (index < 0 || index >= size)
			throw Exception("Index out of range in linked list!", 158, "LinkedList.h");
		LinkedListNode* atIndex = first;
		for (int i = 0; i < index; ++i)
			atIndex = atIndex->next;
		return atIndex->getItem();
	}

	/* Returns an iterator to the first node in the list */
	LinkedListIterator begin() {
		return LinkedListIterator(this);
	}

	/* Return an iterator to the last used node in the list */
	LinkedListIterator end() {
		return LinkedListIterator(this, size - 1);
	}

	/* Return true if @item is present in the list */
	bool contains(const T& item) {
		LinkedListNode* current = first;
		for (int i = 0; i < size; ++i) {
			if (current->getItem() == item)
				return true;
			current = &current->getNext();
		}
		return false;
	}

	/* Returns the amount of currently used nodes (stored items) */
	int getSize() {
		return size;
	}

	/* Iterates over a Linked List. Changing the size of the Linked List or links in the Linked List
	   being iterated over will lead to unexpected behaviour */
	class LinkedListIterator {

		LinkedList *linkedList;
		LinkedListNode* current;
		int size;
		int currentIndex;

	public:

		/* Creates an iterator over @linkedList at @index. By default points at the first element.
		   Throws exception if the specified index is out of used node range in specified list */
		LinkedListIterator(LinkedList* linkedList, int index = 0) {
			this->linkedList = linkedList;
			size = linkedList->size;
			if (index >= size || index < 0)
				throw Exception("Index out of range in linked list!", 208, "LinkedList.h");
			currentIndex = index;
			current = linkedList->first;
			for (int i = 0; i < index; ++i)
				current = &current->getNext();
		}

		/* Creates a copy of @iterator */
		LinkedListIterator(const LinkedListIterator& iterator) {
			this->linkedList = iterator.linkedList;
			this->current = iterator.current;
			this->size = iterator.size;
			this->currentIndex = iterator.currentIndex;
		}

		/* Postfix increment - iterates to the next node if any are left. Is out of range unsafe,
		   going out of range will lead to an exception if any changes to the pointed node are to be made */
		LinkedListIterator operator++() {
			LinkedListIterator temp = LinkedListIterator(*this);
			if (currentIndex >= 0 && &current->getNext() != nullptr)
				current = &current->getNext();
			currentIndex++;
			return temp;
		}

		/* Prefix increment - iterates to the next node if any are left. Is out of range unsafe,
		   going out of range will lead to an exception if any changes to the pointed node are to be made */
		LinkedListIterator& operator++(int) {
			if (currentIndex >= 0 && &current->getNext() != nullptr)
				current = &current->getNext();
			currentIndex++;
			return *this;
		}

		/* Postfix decrement - iterates to the previous node if any are left. Is out of range unsafe,
		   going out of range will lead to an exception if any changes to the pointed node are to be made */
		LinkedListIterator operator--() {
			LinkedListIterator temp = LinkedListIterator(*this);
			if (currentIndex < size && &current->getPrevious() != nullptr)
				current = &current->getPrevious();
			currentIndex--;
			return temp;
		}

		/* Prefix decrement - iterates to the previous node if any are left. Is out of range unsafe,
		   going out of range will lead to an exception if any changes to the pointed node are to be made */
		LinkedListIterator& operator--(int) {
			if (currentIndex < size && &current->getPrevious() != nullptr)
				current = &current->getPrevious();
			currentIndex--;
			return *this;
		}

		/* Sets the item of the pointed node to @item. Throws an exception if iterator is out of list range */
		void setItem(const T& item) {
			if (currentIndex < 0 && currentIndex >= size)
				throw Exception("Index out of list range!", 264, "LinkedList.h");
			current->setItem(item);
		}

		/* Returns a reference to the item contained in pointed node. Throws an exception if iterator is out of list range */
		T& getItem() {
			if (currentIndex < 0 && currentIndex >= size)
				throw Exception("Index out of list range!", 271, "LinkedList.h");
			return current->getItem();
		}

		/* Iterates over num nodes. Is out of range unsafe */
		LinkedListIterator operator+(const int num) {
			LinkedListIterator newitr = LinkedListIterator(*this);
			for (int i = 0; i < num; ++i)
				newitr++;
			return newitr;
		}

		/* Iterates over num nodes back. Is out of range unsafe */
		LinkedListIterator operator-(const int num) {
			LinkedListIterator newitr = LinkedListIterator(*this);
			for (int i = 0; i < num; ++i)
				newitr--;
			return newitr;
		}

#pragma region Comparison operators

		// Comparison of pointers index to an integer

		bool operator>(const int num) {
			return currentIndex > num;
		}

		bool operator<(const int num) {
			return currentIndex < num;
		}

		bool operator>=(const int num) {
			return currentIndex >= num;
		}
		bool operator<=(const int num) {
			return currentIndex <= num;
		}

		bool operator==(const int num) {
			return currentIndex == num;
		}
		bool operator!=(const int num) {
			return currentIndex != num;
		}

		// Comparison to another iterator

		bool operator>(const LinkedListIterator& itr) {
			return currentIndex > itr.currentIndex;
		}

		bool operator<(const LinkedListIterator& itr) {
			return currentIndex < itr.currentIndex;
		}

		bool operator>=(const LinkedListIterator& itr) {
			return currentIndex >= itr.currentIndex;
		}
		bool operator<=(const LinkedListIterator& itr) {
			return currentIndex <= itr.currentIndex;
		}

		bool operator==(const LinkedListIterator& itr) {
			return linkedList == itr.linkedList && currentIndex == itr.currentIndex;
		}

		bool operator!=(const LinkedListIterator& itr) {
			return linkedList != itr.linkedList || currentIndex != itr.currentIndex;
		}

#pragma endregion

	};

};