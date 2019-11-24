#include "ResizableArray.h"
#include <stdexcept>

template<class T>
void ResizableArray<T>::resize() {
	T* newarrptr = new T[size + resizeStep];
	for (int i = 0; i < filled; ++i)
		newarrptr[i] = arrptr[i];
	size += resizeStep;
	delete[] arrptr;
	arrptr = newarrptr;
}

template<class T>
ResizableArray<T>::ResizableArray() {
	size = filled = 0;
	resize();
}

template<class T>
ResizableArray<T>::ResizableArray(const size_t size) {
	this.size = size;
	filled = 0;
	resize();
}

template<class T>
ResizableArray<T>::ResizableArray(const T* arr, const size_t size) {
	this.size = size / resizeStep + 1;
	filled = size;
	resize();
	for (int i = 0; i < size; ++i)
		arrptr[i] = arr[i];
}

template<class T>
int ResizableArray<T>::getSize() {
	return filled;
}

template<class T>
bool ResizableArray<T>::isEmpty() {
	return !filled;
}

template<class T>
void ResizableArray<T>::add(const T& elem) {
	if (filled >= size)
		resize();
	arrptr[filled++] = elem;
}

template<class T>
void ResizableArray<T>::removeLast() {
	--filled;
}

template<class T>
T ResizableArray<T>::elementAt(const int index) {
	if (index < 0 || index >= filled)
		throw std::out_of_range("Resizable array index out of range");
	return arrptr[index];
}

template<class T>
T ResizableArray<T>::operator[](const int index) {
	return elementAt(index);
}

template<class T>
bool operator==(const ResizableArray<T>& ra1, const ResizableArray<T>& ra2) {
	if (ra1.filled != ra2.filled)
		return false;
	for (int i = 0; i < ra1.filled; ++i)
		if (ra1.arrptr[i] != ra2.arrptr[i])
			return false;
	return true;
}


