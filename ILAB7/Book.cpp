#include "Book.h"
#include "Util.h"
#include "Exception.h"

void memcpy(String* dest, const String* source, const unsigned int size) {
	for (int i = 0; i < size; ++i)
		dest[i] = source[i];
}


#pragma region Constructors

/* Instantiates a Book with empty fields/default values */
Book::Book() {
	title = '\0';
	author = '\0';
	sphereCount = 0;
	spheres = nullptr;
	publicationYear = 1970;
	currentlyAvailable = 0;
}

/* Instantiates a Book with recieved arguments */
Book::Book(
	String author = '\0',
	String title = '\0',
	date_y publicationYear = 1970,
	unsigned int sphereCount = 0,
	String* spheres = nullptr,
	unsigned int currentlyAvailable = 0
) {
	this->author = author;
	this->title = title;
	this->publicationYear = publicationYear;
	if (sphereCount > MAX_SPHERE_COUNT || sphereCount == 0)
		throw Exception("Sphere count exceeds limit or must be at least 1!", 30, "Book.cpp");
	if (this->sphereCount < sphereCount) {
		delete[] spheres;
		spheres = new String[sphereCount];
	}
	memcpy(this->spheres, spheres, sphereCount);
	this->sphereCount = sphereCount;
	this->currentlyAvailable = currentlyAvailable;
}

/* Instantiates a copy of the Book @book */
Book::Book(const Book& book) {
	if (this == &book)
		return;
	author = book.author;
	title = book.title;
	publicationYear = book.publicationYear;
	if (sphereCount < book.sphereCount) {
		delete[] spheres;
		spheres = new String[book.sphereCount];
	}
	memcpy(spheres, book.spheres, book.sphereCount);
	sphereCount = book.sphereCount;
	currentlyAvailable = book.currentlyAvailable;
}

#pragma endregion

Book::~Book() {
	if (spheres != nullptr)
		delete[] spheres;
}

#pragma region Getters

/* Returns this Book's author as a String copy */
String Book::getAuthor() const {
	return author;
}

/* Returns this Book's title as a String copy */
String Book::getTitle() const {
	return title;
}

/* Returns this Book's publication year as an integer */
int Book::getPublicationYear() const {
	return publicationYear;
}

int Book::getSpheresCount() const {
	return sphereCount;
}

/* Returns this Book's sphere as a String copy */
const String* Book::getSpheres() const {
	return spheres;
}

/* Returns this Book's copy amount as an integer */
int Book::getCurrentAmount() const {
	return currentlyAvailable;
}

#pragma endregion

#pragma region Setters

/* Sets this Book's author */
void Book::setAuthor(const String& author) {
	this->author = author;
}

/* Sets this Book's title */
void Book::setTitle(const String& title) {
	this->title = title;
}

/* Sets this Book's publication year */
void Book::setPublicationYear(const int year) {
	publicationYear = year;
}

/* Sets this Book's spehre*/
void Book::setSpheres(const String* spheres, const int sphereCount) {
	if (sphereCount > MAX_SPHERE_COUNT || sphereCount <= 0)
		throw Exception("Sphere count exceeds limit!", 30, "Book.cpp");
	this->sphereCount = sphereCount;
	memcpy(this->spheres, spheres, sphereCount);
}

/* Sets this Book's current copy amount */
void Book::setCurrentAmount(const int amount) {
	currentlyAvailable = amount;
}

#pragma endregion

/* Returns true if Books share the same author, title and publication year
   (not sphere though) */
bool operator==(const Book& b1, const Book& b2) {
	return b1.author == b2.author
		&& b1.title == b2.title
		&& b1.publicationYear == b2.publicationYear;
}

/* Returns true if Books have different authors or titles or publication years
   (not spheres though) */
bool operator!=(const Book& b1, const Book& b2) {
	return b1.author != b2.author
		|| b1.title != b2.title
		|| b1.publicationYear != b2.publicationYear;
}

/* Decrements the available amount of the first Book, if the Books are the same.
   Return the first Book otherwise */
Book operator-(const Book& b1, const Book& b2) {
	if (b1 != b2) return b1;
	return Book(b1.author, b1.title, b1.publicationYear, b1.sphereCount, b1.spheres, b1.currentlyAvailable - b2.currentlyAvailable);
}

/* Increments the available amount of the first Book, if the Books are the same.
   Return the first Book otherwise */
Book Book::operator+(const Book& book) const {
	if (*this != book) return *this;
	return Book(author, title, publicationYear, sphereCount, spheres, currentlyAvailable + book.currentlyAvailable);
}

/* Returns true if the first Book has less available copies
   (does not check for Book equality) */
bool operator<(const Book& b1, const Book& b2) {
	return b1.currentlyAvailable < b2.currentlyAvailable;
}

/* Return true if the first Book has more available copies
   (does not check for Book equality */
bool Book::operator>(const Book& b) const {
	return currentlyAvailable > b.currentlyAvailable;
}

/* Copies values from parameter to this Book */
Book& Book::operator=(const Book& book) {
	if (this == &book)
		return *this;
	author = book.author;
	title = book.title;
	publicationYear = book.publicationYear;
	if (sphereCount < book.sphereCount) {
		delete[] spheres;
		spheres = new String[book.sphereCount];
	}
	memcpy(spheres, book.spheres, book.sphereCount);
	sphereCount = book.sphereCount;
	currentlyAvailable = book.currentlyAvailable;
	return *this;
}

/* Sets the amount of avaialable copies to the value on the right of equals */
Book& Book::operator=(const unsigned int amount) {
	currentlyAvailable = amount;
	return *this;
}

/* Incerements the amount of available copies of this Book by 1 (postfix version) */
const Book operator++(Book& b, int) {
	Book pb = b;
	b.currentlyAvailable++;
	return pb;
}

/* Incerements the amount of available copies of this Book by 1 (prefix version) */
const Book& Book::operator++() {
	currentlyAvailable++;
	return *this;
}

/* Decrements the amount of available copies of this Book by 1 (postfix version) */
const Book operator--(Book& b, int) {
	Book pb = b;
	b.currentlyAvailable--;
	return pb;
}

/* Incerements the amount of available copies of this Book by 1 (prefix version) */
const Book& Book::operator--() {
	currentlyAvailable--;
	return *this;
}

/* Outputs information about this Book into the stream &out as table row */
std::ostream& operator<<(std::ostream& out, const Book& b) {
	out <<
		std::setw(25) << b.author <<
		std::setw(50) << b.title <<
		std::setw(7) << b.publicationYear <<
		std::setw(20) << b.spheres[0] <<
		std::setw(7) << b.currentlyAvailable << std::endl;
	return out;
}

/* Reads Book object properties from input stream &in consecutively, each on a separate line
   Throws invalid_argument exception if input format is invalid.*/
std::istream& operator>>(std::istream& in, Book& b) {

	try {
		getline(in, b.author);
	}
	catch (Exception& e) {
		e.setInfo("Wrong author name format");
		throw e;
	}
	Util::capitalizeFirstLetters(b.author);

	try {
		getline(in, b.title);
	}
	catch (Exception& e) {
		e.setInfo("Wrong title format");
		throw e;
	}
	Util::capitalizeFirstLetters(b.title);

	int num;
	in >> num;
	if (in.fail() || num < 0 || num > 2020)
		throw Exception("Wrong input stream format!", 258, "Book.cpp", "Wrong publication year format");
	b.publicationYear = num;
	in.ignore(INT_MAX, '\n');

	in >> num;
	if (in.fail() || num <= 0 || num > MAX_SPHERE_COUNT)
		throw Exception("Wrong input stream format!", 258, "Book.cpp", "Wrong sphere count format");
	if (b.sphereCount < num) {
		delete[] b.spheres;
		b.spheres = new String[num];
	}
	b.sphereCount = num;
	in.ignore(INT_MAX, '\n');

	for (int i = 0; i < b.sphereCount; ++i) {
		try {
			getline(in, b.spheres[i]);
		}
		catch (Exception& e) {
			e.setInfo("Wrong sphere format");
			throw e;
		}
		Util::capitalizeFirstLetters(b.spheres[i]);
	}

	in >> b.currentlyAvailable;
	if (in.fail())
		throw Exception("Wrong input stream format!", 237, "Book.cpp", "Wrong book amount format");
	in.ignore(INT_MAX, '\n');

	return in;
}