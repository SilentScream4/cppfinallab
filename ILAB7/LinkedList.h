#pragma once

template<class T>
class LinkedList {

	class LinkedListNode {

		T* item;
		LinkedListNode* next;
		LinkedListNode* previous;

	public:

		friend class LinkedList;
		friend class LinkedList::LinkedListIterator;

#pragma region Constructors

		LinkedListNode() {
			item = nullptr;
			next = nullptr;
			previous = nullptr;
		}

		LinkedListNode(LinkedListNode* next, LinkedListNode* previous) {
			item = nullptr;
			this->next = next;
			this->previous = previous;
		}

		LinkedListNode(const T& item, LinkedListNode* next, LinkedListNode* previous) {
			this->item = new T(item);
			this->next = next;
			this->previous = previous;
		}

#pragma endregion

#pragma region Setters and getters

		void setItem(const T& item) {
			if (this->item != nullptr)
				delete this->item;
			this->item = new T(item);
		}

		T& getItem() {
			return *item;
		}

		void setNext(LinkedListNode* next) {
			this->next = next;
		}

		LinkedListNode& getNext() {
			return *next;
		}

		void setPrevious(LinkedListNode* previous) {
			this->previous = previous;
		}

		LinkedListNode& getPrevious() {
			return *previous;
		}

#pragma endregion

		LinkedListNode& operator=(const T& item) {
			if (this->item != nullptr)
				delete item;
			this->item = new T(item);
			return *this;
		}

	};

	LinkedListNode* first;
	LinkedListNode* last;
	int size;

public:

	class LinkedListIterator;

	LinkedList() {
		first = new LinkedListNode();
		last = first;
		size = 0;
	}

	LinkedList(const T& item) {
		first = new LinkedListNode(item, nullptr);
		last = first;
		size = 1;
	}

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

	void removeLast() {
		if (size > 1) {
			size--;
			last = last->previous;
		}
		else if (size == 0) size--;
	}

	T& operator[](int index) {
		if (index < 0 || index >= size)
			throw std::out_of_range("Index out of range in linked list!");
		LinkedListNode* atIndex = first;
		for (int i = 0; i < index; ++i)
			atIndex = atIndex->next;
		return atIndex->getItem();
	}

	LinkedListIterator begin() {
		return LinkedListIterator(this);
	}

	LinkedListIterator end() {
		return LinkedListIterator(this, size - 1);
	}

	bool contains(const T& item) {
		LinkedListNode* current = first;
		for (int i = 0; i < size; ++i) {
			if (current->getItem() == item)
				return true;
			current = &current->getNext();
		}
		return false;
	}

	int getSize() {
		return size;
	}

	class LinkedListIterator {

		LinkedList *linkedList;
		LinkedListNode* current;
		int size;
		int currentIndex;

	public:

		LinkedListIterator(LinkedList* linkedList, int index = 0) {
			this->linkedList = linkedList;
			size = linkedList->size;
			if (index >= size || index < 0)
				throw std::out_of_range("Iterator index out of linked list range");
			currentIndex = index;
			current = linkedList->first;
			for (int i = 0; i < index; ++i)
				current = &current->getNext();
		}

		LinkedListIterator(const LinkedListIterator& iterator) {
			this->linkedList = iterator.linkedList;
			this->current = iterator.current;
			this->size = iterator.size;
			this->currentIndex = iterator.currentIndex;
		}

		LinkedListIterator operator++() {
			LinkedListIterator temp = LinkedListIterator(*this);
			if (current != nullptr)
				current = &current->getNext();
			currentIndex++;
			return temp;
		}

		LinkedListIterator& operator++(int) {
			if (current != nullptr)
				current = &current->getNext();
			currentIndex++;
			return *this;
		}

		LinkedListIterator operator--() {
			LinkedListIterator temp = LinkedListIterator(*this);
			if (current != nullptr)
				current = &current->getPrevious();
			currentIndex--;
			return temp;
		}

		LinkedListIterator& operator--(int) {
			if (current != nullptr)
				current = &current->getPrevious();
			currentIndex--;
			return *this;
		}

		void setItem(const T& item) {
			current->setItem(item);
		}

		T& getItem() {
			return current->getItem();
		}

		LinkedListIterator operator+(const int num) {
			LinkedListIterator newitr = LinkedListIterator(*this);
			for (int i = 0; i < num; ++i)
				newitr++;
			return newitr;
		}
		LinkedListIterator operator-(const int num) {
			LinkedListIterator newitr = LinkedListIterator(*this);
			for (int i = 0; i < num; ++i)
				newitr--;
			return newitr;
		}

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


		bool operator==(const LinkedListIterator& itr) {
			return linkedList == itr.linkedList && currentIndex == itr.currentIndex;
		}

		bool operator!=(const LinkedListIterator& itr) {
			return linkedList != itr.linkedList || currentIndex != itr.currentIndex;
		}

	};

};


/*
template <typename T>
typename LinkedList<T>::LinkedListIterator operator+(const typename LinkedList<T>::LinkedListIterator& itr, const int num) {
	typename LinkedList<T>::LinkedListIterator newitr = typename LinkedList<T>::LinkedListIterator(itr);
	for (int i = 0; i < num && newitr.currentIndex < newitr.size - 1; ++i)
		newitr++;
	return newitr;
}

template<typename T>
typename LinkedList<T>::LinkedListIterator operator- (const typename LinkedList<T>::LinkedListIterator& itr, const int num) {
	typename LinkedList<T>::LinkedListIterator newitr = typename LinkedList<T>::LinkedListIterator(itr);
	for (int i = 0; i < num && newitr.currentIndex > 0; ++i)
		newitr--;
	return newitr;
}

template<class T>
bool operator>(const class LinkedList<T>::LinkedListIterator& itr, const int index) {
	return itr.currentIndex > index;
}

template<class T>
bool operator<(const class LinkedList<T>::LinkedListIterator& itr, const int index) {
	return itr.currentIndex < index;
}

template<class T>
bool operator>=(const class LinkedList<T>::LinkedListIterator& itr, const int index) {
	return itr.currentIndex >= index;
}

template<class T>
bool operator<=(const class LinkedList<T>::LinkedListIterator& itr, const int index) {
	return itr.currentIndex <= index;
}

template<class T>
bool operator==(const class LinkedList<T>::LinkedListIterator& itr, const int index) {
	return itr.currentIndex == index;
}

template<class T>
bool operator!=(const class LinkedList<T>::LinkedListIterator& itr, const int index) {
	return itr.currentIndex != index;
}

template<class T>
bool operator!=(const class LinkedList<T>::LinkedListIterator& itr1, const class LinkedList<T>::LinkedListIterator& itr2) {
	return itr1.linkedList == itr2.linkedList && itr1.currentIndex != itr2.currentIndex;
}
*/