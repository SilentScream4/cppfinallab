#include "Book.h"
#include "Util.h"
#include <stdexcept>

Book::Book() {
	title = author = sphere = "";
	publicationYear = 1970;
	currentlyAvailable = 0;
}

Book::Book(
	std::string author = "",
	std::string title = "",
	date_yr publicationYear = 1970,
	std::string sphere = "",
	unsigned int currentlyAvailable = 0
) {
	this->author = author;
	this->title = title;
	this->publicationYear = publicationYear;
	this->sphere = sphere;
	this->currentlyAvailable = currentlyAvailable;
}

Book::Book(const Book& book) {
	author = book.author;
	title = book.title;
	publicationYear = book.publicationYear;
	sphere = book.sphere;
	currentlyAvailable = book.currentlyAvailable;
}

bool operator==(const Book& b1, const Book& b2) {
	return b1.author == b2.author
		&& b1.title == b2.title
		&& b1.publicationYear == b2.publicationYear;
}

bool operator!=(const Book& b1, const Book& b2) {
	return b1.author != b2.author
		|| b1.title != b2.title
		|| b1.publicationYear != b2.publicationYear;
}

Book operator-(const Book& b1, const Book& b2) {
	if (b1 != b2) return b1;
	return Book(b1.author, b1.title, b1.publicationYear, b1.sphere, b1.currentlyAvailable - b2.currentlyAvailable);
}

Book Book::operator+(const Book& book) {
	if (*this != book) return *this;
	return Book(author, title, publicationYear, sphere, currentlyAvailable + book.currentlyAvailable);
}

bool operator<(const Book& b1, const Book& b2) {
	return b1.currentlyAvailable < b2.currentlyAvailable;
}

bool Book::operator>(const Book& b) {
	return currentlyAvailable > b.currentlyAvailable;
}

void Book::operator=(const unsigned int amount) {
	currentlyAvailable = amount;
}

Book operator++(Book& b) {
	Book pb = b;
	b.currentlyAvailable++;
	return pb;
}

void Book::operator++() {
	currentlyAvailable++;
	return;
}

std::ostream& operator<<(std::ostream& out, const Book& b) {
	out <<
		std::setw(25) << b.author <<
		std::setw(50) << b.title <<
		std::setw(7) << b.publicationYear <<
		std::setw(20) << b.sphere <<
		std::setw(7) << b.currentlyAvailable << std::endl;
	return out;
}

/* Reads Book object properties from input stream "in" consecutively, each on a separate line
   Throws invalid_argument exception if input format is invalid.*/
std::istream& operator>>(std::istream& in, Book& b) {

	getline(in, b.author, '\n');
	if (in.fail())
		throw std::invalid_argument("Wrong input stream format (author name)");
	Util::capitalizeFirstLetters(b.author);

	getline(in, b.title, '\n');
	if (in.fail())
		throw std::invalid_argument("Wrong input stream format (book title)");
	Util::capitalizeFirstLetters(b.title);

	in >> b.publicationYear;
	if (in.fail())
		throw std::invalid_argument("Wrong input stream format (publication year)");
	if (b.publicationYear < 1900 || b.publicationYear > 2020)
		b.publicationYear = 1970;
	in.ignore(INT_MAX, '\n');

	getline(in, b.sphere, '\n');
	if (in.fail())
		throw std::invalid_argument("Wrong input stream format (book sphere)");

	in >> b.currentlyAvailable;
	if (in.fail())
		throw std::invalid_argument("Wrong input stream format (book count)");
	in.ignore(INT_MAX, '\n');

	return in;
}