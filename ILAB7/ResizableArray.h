#pragma once

template<class T>
class ResizableArray {

	T* arrptr;
	size_t filled;
	size_t size;
	static const size_t resizeStep = 8;

	/* Resizes the inner array to fit another @resizeStep(8) elements of type T */
	void resize();

public:

	ResizableArray();
	ResizableArray(const size_t size);
	ResizableArray(const T* arr, const size_t size);
	~ResizableArray();

	/* Returns the amount of currently stored elements */
	int getSize();
	/* Returns true if this Resizable Array is empty */
	bool isEmpty();
	/* Return true if this elem is present in this Resizable Array */
	bool contains(const T& elem);

	/* Adds another element of type T at the end of the array,
   extends ResizableArray if necessary */
	void add(const T elem);
	/* Removes last added element if any */
	void removeLast();

	friend bool operator==(const ResizableArray&, const ResizableArray&);

	/* Return element at @index by reference (mutable) */
	T& elementAt(const int index);
	T& operator[](const int index);

};