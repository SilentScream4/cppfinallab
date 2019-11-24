#include "Book.h"
#include "Util.h"
#include <stdexcept>

/* Instantiates a Book with empty fields/default values */
Book::Book() {
	title = '\0';
	author = '\0';
	sphere = '\0';
	publicationYear = 1970;
	currentlyAvailable = 0;
}

/* Instantiates a Book with recieved arguments */
Book::Book(
	String author = '\0',
	String title = '\0',
	date_y publicationYear = 1970,
	String sphere = '\0',
	unsigned int currentlyAvailable = 0
) {
	this->author = author;
	this->title = title;
	this->publicationYear = publicationYear;
	this->sphere = sphere;
	this->currentlyAvailable = currentlyAvailable;
}

/* Instantiates a copy of the Book @book */
Book::Book(const Book& book) {
	author = book.author;
	title = book.title;
	publicationYear = book.publicationYear;
	sphere = book.sphere;
	currentlyAvailable = book.currentlyAvailable;
}

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
	return Book(b1.author, b1.title, b1.publicationYear, b1.sphere, b1.currentlyAvailable - b2.currentlyAvailable);
}

/* Increments the available amount of the first Book, if the Books are the same.
   Return the first Book otherwise */
Book Book::operator+(const Book& book) {
	if (*this != book) return *this;
	return Book(author, title, publicationYear, sphere, currentlyAvailable + book.currentlyAvailable);
}

/* Returns true if the first Book has less available copies
   (does not check for Book equality) */
bool operator<(const Book& b1, const Book& b2) {
	return b1.currentlyAvailable < b2.currentlyAvailable;
}

/* Return true if the first Book has more available copies
   (does not check for Book equality */
bool Book::operator>(const Book& b) {
	return currentlyAvailable > b.currentlyAvailable;
}

/* Sets the amount of avaialable copies to the value on the right of equals */
Book& Book::operator=(const unsigned int amount) {
	currentlyAvailable = amount;
	return *this;
}

/* Incerements the amount of available copies of this Book by 1 (postfix version) */
Book operator++(Book& b) {
	Book pb = b;
	b.currentlyAvailable++;
	return pb;
}

/* Incerements the amount of available copies of this Book by 1 (prefix version) */
void Book::operator++() {
	currentlyAvailable++;
	return;
}

/* Outputs information about this Book into the stream &out as table row */
std::ostream& operator<<(std::ostream& out, const Book& b) {
	out <<
		std::setw(25) << b.author <<
		std::setw(50) << b.title <<
		std::setw(7) << b.publicationYear <<
		std::setw(20) << b.sphere <<
		std::setw(7) << b.currentlyAvailable << std::endl;
	return out;
}

/* Reads Book object properties from input stream &in consecutively, each on a separate line
   Throws invalid_argument exception if input format is invalid.*/
std::istream& operator>>(std::istream& in, Book& b) {

	getline(in, b.author);
	Util::capitalizeFirstLetters(b.author);

	getline(in, b.title);
	Util::capitalizeFirstLetters(b.title);

	in >> b.publicationYear;
	if (in.fail())
		throw std::invalid_argument("Wrong input stream format (publication year)");
	if (b.publicationYear < 1900 || b.publicationYear > 2020)
		b.publicationYear = 1970;
	in.ignore(INT_MAX, '\n');

	getline(in, b.sphere);

	in >> b.currentlyAvailable;
	if (in.fail())
		throw std::invalid_argument("Wrong input stream format (book count)");
	in.ignore(INT_MAX, '\n');

	return in;
}