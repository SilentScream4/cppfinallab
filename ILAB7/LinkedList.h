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

		LinkedListNode(const LinkedListNode&); // Copy constructor disabled

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
		LinkedListNode(LinkedListNode* previous) {
			item = nullptr;
			next = nullptr;
			this->previous = previous;
		}

#pragma endregion

		~LinkedListNode() {
			if (item != nullptr)
				delete item;
		}

#pragma region Setters and getters

		/* Deletes current item if any was contained and saves a copy of @item */
		void setItem(const T& item) {
			if (this->item != nullptr && this->item!=&item)
				delete this->item;
			this->item = new T(item);
		}

		/* Return a reference to the item (mutable) */
		T& getItem() {
			return *item;
		}

#pragma endregion

		bool hasNext() {
			return next != nullptr;
		}

		bool hasPrevious() {
			return previous != nullptr;
		}

		/* Deletes current item if any was contained and saves a copy of @item */
		LinkedListNode& operator=(const T& item) {
			setItem(item);
			return *this;
		}

	};

	LinkedListNode* head;  // Linked list's first node
	LinkedListNode* tail;	// Linked list's last node
	int size;				// Amount of used linked nodes

public:

	class LinkedListIterator;

	/* Instantiates an empty linked list with a single empty node */
	LinkedList() {
		head = tail = new LinkedListNode();
		size = 0;
	}

	/* Instantiates a linked list with a single node containing a copy of @item */
	LinkedList(const T& item) {
		head = new LinkedListNode(item, nullptr);
		tail = new LinkedListNode(head);
		size = 1;
	}

	/* Cleans up memory (deletes every created node). Doesn't delete nodes, that were disconnected */
	~LinkedList() {
		LinkedListNode* current = head;
		LinkedListNode* previous = head;
		for (int i = 0; i < size; ++i) {
			current = current->next;
			delete previous;
			previous = current;
		}
		delete current;
	}

	/* Adds an item to the linked list. Uses avaialable unused node or creates a new one */
	void add(const T& item) {
		tail->setItem(item);
		if (tail->next == nullptr)
			tail->next = new LinkedListNode(tail);
		tail = tail->next;
		++size;
	}

	/* Removes last added item from the list. Doesn't clean up memory (leaves it to be reused) */
	void removeLast() {
		if (size > 1) {
			--size;
			tail = tail->previous;
		}
	}

	/* Return item contained in node at @index */
	T& operator[](int index) {
		if (index < 0 || index >= size)
			throw Exception("Index out of range in linked list!", 158, "LinkedList.h");
		LinkedListNode* atIndex = head;
		for (int i = 0; i < index; ++i)
			atIndex = atIndex->next;
		return atIndex->getItem();
	}

	/* Returns an iterator to the first node in the list */
	LinkedListIterator begin() {
		return LinkedListIterator(head);
	}

	/* Return an iterator to the last used node in the list */
	LinkedListIterator end() {
		return LinkedListIterator(tail);
	}

	/* Return true if @item is present in the list */
	bool contains(const T& item) const {
		LinkedListNode* current = head;
		for (int i = 0; i < size; ++i) {
			if (current->item == item)
				return true;
			current = current->next;
		}
		return false;
	}

	/* Returns iterator of @item in the list if it is present in this list. Returns end otherwise */
	LinkedListIterator find(const T& item) const {
		LinkedListNode* current = head;
		for (int i = 0; i < size; ++i) {
			if (current->item == item)
				return LinkedListIterator(current);
			current = current->next;
		}
		return end();
	}

	/* Returns index of @item in the list if it is present in this list. Returns size otherwise */
	int findIndex(const T& item) const {
		LinkedListNode* current = head;
		for (int i = 0; i < size; ++i) {
			if (current->getItem() == item)
				return i;
			current = current->next;
		}
		return size;
	}

	/* Returns the amount of currently used nodes (stored items) */
	int getSize() const {
		return size;
	}

	/* Iterates over a Linked List. Changing the size of the Linked List or links in the Linked List
	   being iterated over will lead to unexpected behaviour */
	class LinkedListIterator {

		LinkedListNode* current;

	public:

		/* Creates an iterator pointing at node */
		LinkedListIterator(LinkedListNode* current) {
			this->current = current;
		}

		/* Creates a copy of @iterator */
		LinkedListIterator(const LinkedListIterator& iterator) {
			current = iterator.current;
		}

		/* Postfix increment - iterates to the next node if any are left. Is out of range unsafe,
		   going out of range will lead to an exception if any changes to the pointed node are to be made */
		LinkedListIterator operator++(int) {
			LinkedListIterator temp = LinkedListIterator(*this);
			if (current->hasNext())
				current = current->next;
			return temp;
		}

		/* Prefix increment - iterates to the next node if any are left. Is out of range unsafe,
		   going out of range will lead to an exception if any changes to the pointed node are to be made */
		LinkedListIterator& operator++() {
			if (current->hasNext())
				current = current->next;
			return *this;
		}

		/* Postfix decrement - iterates to the previous node if any are left. Is out of range unsafe,
		   going out of range will lead to an exception if any changes to the pointed node are to be made */
		LinkedListIterator operator--(int) {
			LinkedListIterator temp = LinkedListIterator(*this);
			if (current->hasPrevious())
				current = current->previous;
			return temp;
		}

		/* Prefix decrement - iterates to the previous node if any are left. Is out of range safe,
		   going out of range will lead to an exception if any changes to the pointed node are to be made */
		LinkedListIterator& operator--() {
			if (current->hasPrevious())
				current = current->previous;
			return *this;
		}

		/* Iterates over num nodes. Is out of range unsafe */
		LinkedListIterator operator+(const int num) const {
			LinkedListIterator newitr = LinkedListIterator(*this);
			for (int i = 0; i < num; ++i)
				++newitr;
			return newitr;
		}

		/* Iterates over num nodes back. Is out of range unsafe */
		LinkedListIterator operator-(const int num) const {
			LinkedListIterator newitr = LinkedListIterator(*this);
			for (int i = 0; i < num; ++i)
				--newitr;
			return newitr;
		}

		T& getItem() const {
			return current->getItem();
		}

		void setItem(const T& item) const {
			current->setItem(item);
		}

		/* Return a reference to the item contained in pointed node. Throws an exception if iterator is out of list range */
		T& operator*() const {
			return current->getItem();
		}

		bool operator==(const LinkedListIterator& itr) {
			return current == itr.current;
		}

		bool operator!=(const LinkedListIterator& itr) {
			return current != itr.current;
		}

	};

};