#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <stdexcept>

#include "Book.h"
#include "ResizableArray.h"
#include "ResizableArray.cpp"

/* Returns reference to the book with most available copies in a resizable array */
Book& findBestAvailability(ResizableArray<Book>&);

/* Returns reference to the book with most available copies in an array			 */
Book& findBestAvailability(Book*, int);

/* Sorts a vector sent by a reference in non-descending order				     */
template<class T>
void sort(ResizableArray<T>&);

/* Sorts an array sent by a pointer in non-descending order					     */
template<class T>
void sort(T*, int);

/* Outputs a table to the stream &out from the books in vector &books			 */
void outputTable(std::ostream& out, ResizableArray<Book>&);



int main(int argc, char** argv) {

	std::cout << "Enter text file name to read book database from (without .txt): ";
	std::string fileName;
	std::cin >> fileName;
	fileName += ".txt";

	std::fstream fin(fileName);
	if (!fin.is_open()) {
		std::cerr << "Can't open file " << fileName << std::endl;
		return -1;
	}

	std::cout << "Use a delimiter (symbol separating books in input file? (y\n): ";
	char yn, delim = '\n';
	do {
		std::cin >> yn;
	} while (yn != 'y' && yn != 'n');
	if (yn == 'y') {
		std::cout << "Enter delimiting character (it shouldn't be in the actual text, every book will start with it, but it will be ignored when reading): ";
		std::cin >> delim;
	}

	//std::vector<Book> books;
	ResizableArray<Book> books = ResizableArray<Book>();
	while (!fin.eof()) {
		if (delim != '\n') fin.ignore(INT_MAX, delim);
		else while (!std::isalpha(fin.peek()))
			fin.ignore();
		Book book = Book();
		try {
			fin >> book;
			books.add(book);
		}
		catch (std::exception exc) {
			std::cerr << exc.what() << std::endl;
			std::cout << "Continue reading file? (many more exceptions are likely to pop up) (y\n): ";
			char yn;
			do {
				std::cin >> yn;
			} while (yn != 'y' && yn != 'n');
			if (yn == 'y') fin.ignore(INT_MAX, delim);
			else return -2;
		}
	}

	std::ofstream fout("booksTable.txt");
	if (!fout.is_open()) {
		std::cerr << "Can't create output file" << std::endl;
		return -3;
	}

	try {
		fout << "Book with most available copies is:\n";
		fout << findBestAvailability(books);
	}
	catch (std::invalid_argument exc) {
		std::cerr << exc.what() << std::endl;
	}

	sort(books);
	outputTable(fout, books);

	return 0;
}


/* Returns reference to the book with most available copies in a resizable array*/
Book& findBestAvailability(ResizableArray<Book>& books) {
	if (books.isEmpty())
		throw std::invalid_argument("Books list must not be empty");
	Book* bestAvailable = new Book(books[0]);
	for (int i = 1; i < books.getSize(); i++) {
		if (books[i] > *bestAvailable)
			bestAvailable = &books[i];
	}
	return *bestAvailable;
}

/* Returns reference to the book with most available copies in an array*/
Book& findBestAvailability(Book* books, int n) {
	if (books == nullptr)
		throw std::invalid_argument("Books list must not be empty");
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
		for (; j >= 0; j--)
			arr[j + 1] = arr[j];
		arr[j + 1] = key;
	}
	return;
}

/* Sorts an array sent by a pointer in non-descending order*/
template<class T>
void sort(T* arr, int n) {
	for (int i = 1; i < n; i++) {
		T key = arr[i];
		int j = i - 1;
		for (; j >= 0; j--)
			arr[j + 1] = arr[j];
		arr[j + 1] = key;
	}
	return;
}

/* Outputs a table to the stream &out from the books in vector &books*/
void outputTable(std::ostream& out, ResizableArray<Book>& books) {
	out <<
		std::setw(25) << "Author" <<
		std::setw(50) << "Title" <<
		std::setw(7) << "Year" <<
		std::setw(20) << "Sphere" <<
		std::setw(7) << "Count" <<
		std::endl;
	for (int i = 0; i < books.getSize(); ++i)
		out << books[i];
	return;
}