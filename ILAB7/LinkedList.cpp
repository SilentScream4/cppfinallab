#include "LinkedList.h"
#include <stdexcept>

template<class T>
LinkedList<T>::LinkedList() {
	first = new LinkedListNode<T>();
	last = first;
	size = 0;
}

template<class T>
LinkedList<T>::LinkedList(const T& item) {
	first = new LinkedListNode<T>(item);
	last = first;
	size = 1;
}

template<class T>
void LinkedList<T>::add(const T& item) {
	if (size == 0) {
		first->setItem(item);
		size++;
		return;
	}
	if (last->next != nullptr)
		last->next = new LinkedListNode<T>(item);
	else last->next->setItem(item);
	last = last->next;
	size++;
}

template<class T>
void LinkedList<T>::removeLast() {
	if (size > 0)
		size--;
}

template<class T>
T& LinkedList<T>::operator[](int index) {
	if (index < 0 || index >= size)
		throw std::out_of_range("Index out of range in linked list!");
	LinkedListNode<T>* atIndex = first;
	for (int i = 0; i < index; ++i)
		atIndex = atIndex->next;
	return atIndex->getItem();
}

template<class T>
LinkedListIterator<T> LinkedList<T>::begin() {
	return LinkedListIterator(this);
}

template<class T>
LinkedListIterator<T> LinkedList<T>::end() {
	return LinkedLastIterator(this, size - 1);
}