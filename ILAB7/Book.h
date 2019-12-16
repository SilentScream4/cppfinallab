#pragma once
#include <iomanip>

#include "String.h"

#define BOOK_MAX_SPHERE_COUNT 5
#define BOOK_AUTHOR_WIDTH 25
#define BOOK_TITLE_WIDTH 50
#define BOOK_YEAR_WIDTH 7
#define BOOK_SPHERE_WIDTH 20
#define BOOK_COUNT_WIDTH 7

typedef unsigned short date_y;

class Book {

	String author;
	String title;
	date_y publicationYear;
	unsigned int sphereCount;
	String* spheres;
	unsigned int currentlyAvailable;

	static bool isValidName(const String&); // Returns true if a string could be a valid name (consists of only alphabetic characters or '-')

	static bool isValidSphere(const String&); // Return true if a string could be a valid sphere name (consists of only alphabetic characters)

	static String trimToSize(const String&, const unsigned int); // Returns trimmed string to fit in size

public:

	/* Instantiates a Book with empty fields/default values */
	Book();
	/* Instantiates a Book with recieved arguments */
	Book(String, String, date_y, unsigned int, String*, unsigned int);
	/* Instantiates a copy of the Book @book */
	Book(const Book&);
	/* Destructor cleans up spheres memory */
	~Book();
	/* Returns this Book's author as a String copy */
	String getAuthor() const;
	/* Returns this Book's title as a String copy */
	String getTitle() const;
	/* Returns this Book's publication year as an integer */
	int getPublicationYear() const;
	/* Returns this Book's sphere count as a an integer */
	int getSpheresCount() const;
	/* Returns immutable pointer to spheres array */
	const String* getSpheres() const;
	/* Returns this Book's copy amount as an integer */
	int getCurrentAmount() const;

	/* Sets this Book's author */
	void setAuthor(const String&);
	/* Sets this Book's title */
	void setTitle(const String&);
	/* Sets this Book's publication year */
	void setPublicationYear(const int);
	/* Sets this Book's spheres and sphere count*/
	void setSpheres(const String*, const int);
	/* Sets this Book's current copy amount */
	void setCurrentAmount(const int);

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
	Book operator+(const Book&) const;

	/* Returns true if the first Book has less available copies
   (does not check for Book equality) */
	friend bool operator<(const Book&, const Book&);
	/* Return true if the first Book has more available copies
   (does not check for Book equality */
	bool operator>(const Book&) const;

	/* Copies values from parameter to this Book */
	Book& operator=(const Book&);

	/* Sets the amount of avaialable copies to the value on the right of equals */
	Book& operator=(const unsigned int);

	/* Incerements the amount of available copies of this Book by 1 (postfix version) */
	friend const Book operator++(Book& b, int);
	/* Incerements the amount of available copies of this Book by 1 (prefix version) */
	const Book& operator++();

	/* Decrements the amount of available copies of this Book by 1 (postfix version) */
	friend const Book operator--(Book& b, int);
	/* Decrements the amount of available copies of this Book by 1 (prefix version) */
	const Book& operator--();

	/* Outputs information about this Book into the stream &out as table row */
	friend std::ostream& operator<<(std::ostream& out, const Book& b);
	/* Reads Book object properties from input stream &in consecutively, each on a separate line
   Throws invalid_argument exception if input format is invalid.*/
	friend std::istream& operator>>(std::istream& in, Book& b);

	friend void copySpheres(String*, const String*, const unsigned int);

};