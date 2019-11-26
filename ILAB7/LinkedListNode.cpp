#include "LinkedListNode.h"

#pragma region Constructors

template<class T>
LinkedListNode<T>::LinkedListNode() {
	item = nullptr;
	next = nullptr;
	previous = nullptr;
}

template<class T>
LinkedListNode<T>::LinkedListNode(LinkedListNode* next, LinkedListNode* previous) {
	item = nullptr;
	this->next = next;
	this->previous = previous;
}

template<class T>
LinkedListNode<T>::LinkedListNode(const T& item, LinkedListNode* next, LinkedListNode* previous) {
	this->item = new T(item);
	this->next = next;
	this->previous = previous;
}

#pragma endregion

#pragma region Setters and getters

template<class T>
void LinkedListNode<T>::setItem(const T& item) {
	this->item = new T(item);
}

template<class T>
T& LinkedListNode<T>::getItem() {
	return item;
}

template<class T>
void LinkedListNode<T>::setNext(LinkedListNode* next) {
	this->next = next;
}

template<class T>
LinkedListNode<T>& LinkedListNode<T>::getNext() {
	return *next;
}

template<class T>
void LinkedListNode<T>::setPrevious(LinkedListNode* previous) {
	this->previous = previous;
}

template<class T>
LinkedListNode<T>& LinkedListNode<T>::getPrevious() {
	return *previous;
}

#pragma endregion

template<class T>
LinkedListNode<T>& LinkedListNode<T>::operator=(const T& item) {
	if (this->item != nullptr)
		delete item;
	this->item = new T(item);
	return *this;
}