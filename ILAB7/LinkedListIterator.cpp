#include "LinkedListIterator.h"

/*
LinkedList* linkedList;
LinkedListNode* current;
int size;
int currentIndex;
*/

template<class T>
LinkedListIterator<T>::LinkedListIterator(LinkedList<T>* linkedList, int index) {
	this->linkedList = linkedList;
	currentIndex = index;
	current = linkedList[index];
	size = linkedList->size;
}

template<class T>
LinkedListIterator<T>::LinkedListIterator(const LinkedListIterator& iterator) {
	this->linkedList = iterator.linkedList;
	this->current = iterator.current;
	this->size = iterator.size;
	this->currentIndex = iterator.currentIndex;
}

template<class T>
LinkedListIterator<T> operator+(const LinkedListIterator<T>& itr, const int num) {
	LinkedListIterator<T> newitr = LinkedListIterator<T>(itr);
	for (int i = 0; i < num && newitr.currentIndex < newitr.size - 1; ++i)
		newitr++;
	return newitr;
}

template<class T>
LinkedListIterator<T> operator-(const LinkedListIterator<T>& itr, const int num) {
	LinkedListIterator<T> newitr = LinkedListIterator<T>(itr);
	for (int i = 0; i < num && newitr.currentIndex > 0; ++i)
		newitr--;
	return newitr;
}

template<class T>
bool operator>(const LinkedListIterator<T>& itr, const int index) {
	return itr.currentIndex > index;
}

template<class T>
bool operator<(const LinkedListIterator<T>& itr, const int index) {
	return itr.currentIndex < index;
}

template<class T>
LinkedListIterator<T> LinkedListIterator<T>::operator++() {
	if (currentIndex >= size - 1)
		return *this;
	LinkedListIterator<T> temp = LinkedListIterator<T>(*this);
	current = current->next;
	currentIndex++;
	return temp;
}

template<class T>
LinkedListIterator<T>& LinkedListIterator<T>::operator++(int) {
	if (currentIndex >= size - 1)
		return *this;
	current = current->next;
	currentIndex++;
	return *this;
}

template<class T>
LinkedListIterator<T> LinkedListIterator<T>::operator--() {
	if (currentIndex == 0)
		return *this;
	LinkedListIterator<T> temp = LinkedListIterator<T>(*this);
	current = current->previous;
	currentIndex--;
	return temp;
}

template<class T>
LinkedListIterator<T>& LinkedListIterator<T>::operator--(int) {
	if (currentIndex == 0)
		return *this;
	current = current->previous;
	currentIndex--;
	return *this;
}
