#pragma once
#include <string>
#include <iomanip>
#include <string>

typedef unsigned int date_yr;

class Book {

private:

	std::string author;
	std::string title;
	date_yr publicationYear;
	std::string sphere;
	unsigned int currentlyAvailable;

public:

	Book();
	Book(std::string, std::string, date_yr, std::string, unsigned int);
	Book(const Book&);

	friend bool operator==(const Book&, const Book&);
	friend bool operator!=(const Book&, const Book&);

	friend Book operator-(const Book&, const Book&);
	Book operator+(const Book&);

	friend bool operator<(const Book&, const Book&);
	bool operator>(const Book&);

	void operator=(const unsigned int);

	friend Book operator++(Book& b);
	void operator++();

	friend std::ostream& operator<<(std::ostream& out, const Book& b);
	friend std::istream& operator>>(std::istream& in, Book& b);

};