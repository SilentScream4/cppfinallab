#pragma once

template<class T>
class ResizableArray {

	T* arrptr;
	size_t filled;
	size_t size;
	static const size_t resizeStep = 8;

	void resize();

public:

	ResizableArray();
	ResizableArray(const size_t size);
	ResizableArray(const T* arr, const size_t size);

	int getSize();
	bool isEmpty();

	void add(const T& elem);
	void removeLast();

	friend bool operator==(const ResizableArray&, const ResizableArray&);

	T elementAt(const int index);
	T operator[](const int index);

};