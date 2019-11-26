#pragma once

template<class T>
class ResizableArray {

	T* arrptr;
	size_t filled;
	size_t size;
	static const size_t resizeStep = 8;

	/* Resizes the inner array to fit another @resizeStep(8) elements of type T */
	void resize() {
		T* newarrptr = new T[size + resizeStep];
		for (int i = 0; i < filled; ++i)
			newarrptr[i] = arrptr[i];
		size += resizeStep;
		delete[] arrptr;
		arrptr = newarrptr;
	}

public:

#pragma region Constructors

	/* Instantiates a Resizable Array of size @resizeStep(8) */
	ResizableArray() {
		size = filled = 0;
		resize();
	}

	/* Instantiates a Resizable Array able to hold @size elements of type T */
	ResizableArray(const size_t size) {
		this->size = size / resizeStep;
		filled = 0;
		resize();
	}

	/* Instantiates a Resizable Array able to hold @size elements of type T
	   filled with @size elements from *arr */
		ResizableArray(const T* arr, const size_t size) {
		this->size = size / resizeStep + 1;
		filled = size;
		resize();
		for (int i = 0; i < size; ++i)
			arrptr[i] = arr[i];
	}

#pragma endregion

	/* Destructor returns allocated memory */
		~ResizableArray() {
		delete[] arrptr;
	}

	/* Returns the amount of currently stored elements */
	int getSize() {
		return filled;
	}

	/* Returns true if this Resizable Array is empty */
	bool isEmpty() {
		return !filled;
	}

	/* Return true if this elem is present in this Resizable Array */
	bool contains(const T& elem) {
		for (int i = 0; i < filled; ++i)
			if (arrptr[i] == elem)
				return true;
		return false;
	}

	/* Adds another element of type T at the end of the array,
	   extends ResizableArray if necessary */
	void add(const T& elem) {
		if (filled >= size)
			resize();
		arrptr[filled++] = elem;
	}

	/* Removes last added element if any */
	void removeLast() {
		if (filled > 0)
			--filled;
	}

	/* Return element at @index by reference (mutable) */
	T& elementAt(const int index) {
		if (index < 0 || index >= filled)
			throw std::out_of_range("Resizable array index out of range");
		return arrptr[index];
	}

	/* Return element at @index by reference (mutable) */
	T& operator[](const int index) {
		return elementAt(index);
	}

	friend bool operator==(const ResizableArray&, const ResizableArray&);

};

/* Returns true if both Resizable Arrays hold the same amount of elements
   and the same elements in the same oreder */
template<class T>
bool operator==(const ResizableArray<T>& ra1, const ResizableArray<T>& ra2) {
	if (ra1.filled != ra2.filled)
		return false;
	for (int i = 0; i < ra1.filled; ++i)
		if (ra1.arrptr[i] != ra2.arrptr[i])
			return false;
	return true;
}