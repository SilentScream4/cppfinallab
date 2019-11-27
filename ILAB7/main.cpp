#include <iostream>
#include <fstream>
#include <cctype>

#include "LinkedList.h"
#include "Book.h"
#include "ResizableArray.h"
#include "String.h"
#include "Exception.h"


/* Returns reference to the book with most available copies in a resizable array */
Book& findBestAvailability(ResizableArray<Book>&);

/* Returns reference to the book with most available copies in an array			 */
Book& findBestAvailability(Book*, int);

/* Sorts a vector sent by a reference in non-descending order				     */
template<class T>
void sort(ResizableArray<T>&);

/* Sorts a linked list sent by a pointer in non-descending order                 */
template<class T>
void sort(LinkedList<T>& linkedList);

/* Sorts an array sent by a pointer in non-descending order					     */
template<class T>
void sort(T*, int);

/* Outputs a table to the stream &out from the books in vector &books			 */
void outputBooksTable(std::ostream& out, ResizableArray<Book>&);

/* Returns a reference to Resizable Array of unique spheres in @books 			 */
LinkedList<String>& extractSpheres(ResizableArray<Book>&);

/* Outputs &spheres to the stream &out											 */
void outputSpheresList(std::ostream&, LinkedList<String>&);

int main(int argc, char** argv) {

	std::fstream fin;
	char* fn = new char[255];
	while (!fin.is_open())
	{
		do {
			std::cout << "Enter text file name to read book database from (with .txt): ";
			std::cin.clear();
			std::cin >> fn;
		} while (std::cin.fail());

		fin.open(fn);
		if (!fin.is_open())
			std::cerr << "Can't open file " << fn << std::endl;
	}
	delete[] fn;

	char yn, delim = '\n';
	do {
		std::cout << "Use a delimiter (symbol separating books in input file? (y\n): ";
		std::cin.clear();
		std::cin >> yn;
	} while (std::cin.fail() || yn != 'y' && yn != 'n');
	if (yn == 'y') {
		do {
			std::cout << "Enter delimiting character (it shouldn't be in the actual text, every book will start with it, but it will be ignored when reading): ";
			std::cin.clear();
			std::cin >> delim;
		} while (std::cin.fail() || isalnum(delim));
	}

	ResizableArray<Book> books = ResizableArray<Book>();
	while (!fin.eof() && fin.good()) {

		if (delim != '\n') fin.ignore(INT_MAX, delim);
		else while (!fin.eof() && !std::isalnum(fin.peek()))
			fin.ignore();

		if (fin.eof()) break;

		Book book = Book();
		try {
			fin >> book;
			books.add(book);
		}

		catch (Exception& e) {
			std::cerr << e.getMsg() << ": " << e.getInfo() << std::endl;
			char yn;
			do {
				std::cout << "Continue reading file? (more exceptions may pop up if delimiter is not set) (y\n): ";
				std::cin.clear();
				std::cin >> yn;
			} while (std::cin.fail() || yn != 'y' && yn != 'n');
			if (yn == 'y') fin.clear();
		}

	}

	std::ofstream fout("bestAvailability.txt");
	if (!fout.is_open())
		std::cerr << "Can't create output file bestAvailability.txt" << std::endl;
	else {
		try {
			fout << "Book with most available copies is:\n";
			fout << findBestAvailability(books);
			fout << '\n';
		}
		catch (Exception& e) {
			fout << e.getMsg() << ": " << e.getInfo() << std::endl;
		}

		fout.close();
	}

	fout.open("booksTable.txt");
	if (!fout.is_open())
		std::cerr << "Can't create output file booksTable.txt" << std::endl;
	else {
		sort(books);
		outputBooksTable(fout, books);
		fout.close();
	}

	fout.open("spheresList.txt");
	if (!fout.is_open())
		std::cerr << "Can't create output file spheresList.txt" << std::endl;
	else {
		LinkedList<String> spheres = extractSpheres(books);
		sort(spheres);
		outputSpheresList(fout, spheres);
		fout.close();
	}

	return 0;
}

/* Returns reference to the book with most available copies in a resizable array
   Throws Invalid Argument exception if recieved array is empty */
Book& findBestAvailability(ResizableArray<Book>& books) {
	if (books.isEmpty())
		throw Exception("Invalid argument exception!", 139, "main.cpp", "Books array must not be empty");
	Book* bestAvailable = &books[0];
	for (int i = 1; i < books.getSize(); ++i) {
		if (books[i] > *bestAvailable)
			bestAvailable = &books[i];
	}
	return *bestAvailable;
}

/* Returns reference to the book with most available copies in an array
   Throws Invalid Argument exception if recieved array is empty */
Book& findBestAvailability(Book* books, int n) {
	if (books == nullptr)
		throw Exception("Invalid argument exception!", 152, "main.cpp", "Books array must not be empty");
	Book* bestAvailable = nullptr;
	for (int i = 0; i < n; i++)
		if (bestAvailable == nullptr || books[i] > *bestAvailable)
			bestAvailable = &books[i];
	return *bestAvailable;
}

/* Sorts a resizable array sent by a reference in non-descending order*/
template<class T>
void sort(ResizableArray<T>& arr) {
	for (int i = 1; i < arr.getSize(); i++) {
		T key = arr[i];
		int j = i - 1;
		for (; j >= 0 && arr[j] > key; j--)
			arr[j + 1] = arr[j];
		arr[j + 1] = key;
	}
}

/* Sorts a linked list sent by a pointer in non-descending order*/
template<typename T>
void sort(LinkedList<T>& linkedList) {
	if (linkedList.getSize() != 0)
		for (typename LinkedList<T>::LinkedListIterator itr = linkedList.begin(); itr < linkedList.getSize(); ++itr) {
			T key = itr.getItem();
			typename LinkedList<T>::LinkedListIterator j = itr - 1;
			for (; j >= 0 && j.getItem() > key; --j)
				(j + 1).setItem(j.getItem());
			(j < 0 ? linkedList.begin() : j + 1).setItem(key);
		}
}

/* Sorts an array sent by a pointer in non-descending order*/
template<class T>
void sort(T* arr, int n) {
	for (int i = 1; i < n; i++) {
		T key = arr[i];
		int j = i - 1;
		for (; j >= 0 && arr[j] > key; j--)
			arr[j + 1] = arr[j];
		arr[j + 1] = key;
	}
}

/* Outputs a table to the stream &out from the books in vector &books*/
void outputBooksTable(std::ostream& out, ResizableArray<Book>& books) {
	out <<
		std::setw(25) << "Author" <<
		std::setw(50) << "Title" <<
		std::setw(7) << "Year" <<
		std::setw(20) << "Sphere" <<
		std::setw(7) << "Count" <<
		std::endl;
	for (int i = 0; i < books.getSize(); ++i)
		out << books[i];
}

/* Returns a reference to Resizable Array of unique spheres in &books */
LinkedList<String>& extractSpheres(ResizableArray<Book>& books) {
	int c = books.getSize();
	LinkedList<String>* spheres = new LinkedList<String>();
	for (int i = 0; i < c; ++i)
		if (!spheres->contains(books[i].getSphere()))
			spheres->add(books[i].getSphere());
	return *spheres;
}

/* Outputs &spheres to the stream &out */
void outputSpheresList(std::ostream& out, LinkedList<String>& spheres) {
	if (spheres.getSize() == 0)
		return;
	out << std::setw(20) << "Covered spheres:" << '\n';
	for (LinkedList<String>::LinkedListIterator itr = spheres.begin(); itr < spheres.getSize(); ++itr)
		out << std::setw(20) << itr.getItem() << '\n';
}