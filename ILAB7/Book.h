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

	/* Returns this Book's author as a String copy */
	String getAuthor();
	/* Returns this Book's title as a String copy */
	String getTitle();
	/* Returns this Book's publication year as an integer */
	int getPublicationYear();
	/* Returns this Book's sphere as a String copy */
	String getSphere();
	/* Returns this Book's copy amount as an integer */
	int getCurrentAmount();

	/* Sets this Book's author */
	void setAuthor(String&);
	/* Sets this Book's title */
	void setTitle(String&);
	/* Sets this Book's publication year */
	void setPublicationYear(int);
	/* Sets this Book's spehre*/
	void setSphere(String&);
	/* Sets this Book's current copy amount */
	void setCurrentAmount(int);

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