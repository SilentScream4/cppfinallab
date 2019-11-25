#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <stdexcept>

#include "Book.h"
#include "ResizableArray.h"
#include "String.h"
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
void outputBooksTable(std::ostream& out, ResizableArray<Book>&);

/* Returns a reference to Resizable Array of unique spheres in @books 			 */
ResizableArray<String>& extractSpheres(ResizableArray<Book>&);

/* Outputs &spheres to the stream &out											 */
void outputSpheresList(std::ostream&, ResizableArray<String>&);

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
		else while (!std::isalnum(fin.peek()))
			fin.ignore();

		Book book = Book();
		try {
			fin >> book;
			books.add(book);
		}

		catch (std::exception exc) {
			std::cerr << exc.what() << std::endl;
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

	try {
		fout << "Book with most available copies is:\n";
		fout << findBestAvailability(books);
		fout << '\n';
	}
	catch (std::invalid_argument exc) {
		fout << exc.what() << std::endl;
	}

	fout.close();
	fout.open("booksTable.txt");
	if (!fout.is_open())
		std::cerr << "Can't create output file booksTable.txt" << std::endl;

	sort(books);
	outputBooksTable(fout, books);

	fout.close();
	fout.open("spheresList.txt");
	if (!fout.is_open())
		std::cerr << "Can't create output file spheresList.txt" << std::endl;

	auto spheres = extractSpheres(books);
	sort(spheres);
	outputSpheresList(fout, spheres);

	fout.close();
	return 0;
}


/* Returns reference to the book with most available copies in a resizable array
   Throws Invalid Argument exception if recieved array is empty */
Book& findBestAvailability(ResizableArray<Book>& books) {
	if (books.isEmpty())
		throw std::invalid_argument("Books list must not be empty");
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
		for (; j >= 0 && arr[j] > key; j--)
			arr[j + 1] = arr[j];
		arr[j + 1] = key;
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
ResizableArray<String>& extractSpheres(ResizableArray<Book>& books) {
	int c = books.getSize();
	ResizableArray<String>* spheres = new ResizableArray<String>(c);
	for (int i = 0; i < c; ++i)
		if (!spheres->contains(books[i].getSphere()))
			spheres->add(books[i].getSphere());
	return *spheres;
}

/* Outputs &spheres to the stream &out */
void outputSpheresList(std::ostream& out, ResizableArray<String>& spheres) {
	out << std::setw(20) << "Covered spheres:" << '\n';
	for (int i = 0; i < spheres.getSize(); ++i)
		out << std::setw(20) << spheres[i] << '\n';
}