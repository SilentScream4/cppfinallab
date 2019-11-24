#pragma once
#include <iomanip>

#include "String.h"

typedef unsigned int date_y;

class Book {

private:

	String author;
	String title;
	date_y publicationYear;
	String sphere;
	unsigned int currentlyAvailable;

public:

	Book();
	Book(String, String, date_y, String, unsigned int);
	Book(const Book&);
	~Book() {}

	friend bool operator==(const Book&, const Book&);
	friend bool operator!=(const Book&, const Book&);

	friend Book operator-(const Book&, const Book&);
	Book operator+(const Book&);

	friend bool operator<(const Book&, const Book&);
	bool operator>(const Book&);

	Book& operator=(const unsigned int);

	friend Book operator++(Book& b);
	void operator++();

	friend std::ostream& operator<<(std::ostream& out, const Book& b);
	friend std::istream& operator>>(std::istream& in, Book& b);

};