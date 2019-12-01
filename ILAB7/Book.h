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

	/* Instantiates a Book with empty fields/default values */
	Book();
	/* Instantiates a Book with recieved arguments */
	Book(String, String, date_y, String, unsigned int);
	/* Instantiates a copy of the Book @book */
	Book(const Book&);

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

	/* Returns true if Books share the same author, title and publication year
   (not sphere though) */
	friend bool operator==(const Book&, const Book&);
	/* Returns true if Books have different authors or titles or publication years
   (not spheres though) */
	friend bool operator!=(const Book&, const Book&);

	/* Decrements the available amount of the first Book, if the Books are the same.
   Return the first Book otherwise */
	friend Book operator-(const Book&, const Book&);
	/* Increments the available amount of the first Book, if the Books are the same.
   Return the first Book otherwise */
	Book operator+(const Book&);

	/* Returns true if the first Book has less available copies
   (does not check for Book equality) */
	friend bool operator<(const Book&, const Book&);
	/* Return true if the first Book has more available copies
   (does not check for Book equality */
	bool operator>(const Book&);

	/* Sets the amount of avaialable copies to the value on the right of equals */
	Book& operator=(const unsigned int);

	/* Incerements the amount of available copies of this Book by 1 (postfix version) */
	friend const Book operator++(Book& b,int);
	/* Incerements the amount of available copies of this Book by 1 (prefix version) */
	const Book& operator++(int);

	/* Outputs information about this Book into the stream &out as table row */
	friend std::ostream& operator<<(std::ostream& out, const Book& b);
	/* Reads Book object properties from input stream &in consecutively, each on a separate line
   Throws invalid_argument exception if input format is invalid.*/
	friend std::istream& operator>>(std::istream& in, Book& b);

};