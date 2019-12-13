#pragma once
#include <iostream>

/* String class - holds a C-style string. Designed to make string interaction
   easy. Has most overloaded operators. Is mutable, but changing String size
   frequently may lead to perfomance drops */
class String {

	char* str;
	size_t length;

public:

	/* Unparameterized constructor instantiates empty C-string */
	String();
	/* Parameterized constructor copies argumenent C-string */
	String(const char*);
	/* Copy constructor copies another String */
	String(const String&);
	/* Destructor return allocated memory */
	~String();

	/* Returns String length without terminator */
	int getLength() const;

	/* Returns C-style string (immutable) */
	const char* get() const;
	/* Copies C-style string recieved as a parameter */
	void set(const char*);

	/* Copies C-style string recieved as a parameter */
	String& operator=(const char*);
	/* Copies String recieved as a parameter */
	String& operator=(const String&);

	/* Concats two Strings */
	friend String operator+(const String&, const String&);
	/* Appends String with a single character */
	friend String operator+(const String&, const char);

	/* Appends this String with another String */
	String& operator+=(const String&);
	/* Appends this String with a single character */
	String& operator+=(const char);

	/* Returns true if two Strings are of the same length and consist of exactly
   the same characters */
	friend bool operator==(const String&, const String&);
	/* Returns true if two Strings are of the different length or consist of different characters */
	friend bool operator!=(const String&, const String&);

	/* Returns character at index */
	char& operator[](const int index);

	/* Immutable version */
	const char& operator[](const int index) const;

	/* Outputs String into stream &out */
	friend std::ostream& operator<<(std::ostream&, const String&);

	/* Returns true if @str1 is lexicographically less than @str2 */
	friend bool operator<(const String&, const String&);
	/* Returns true if @str1 is lexicographically more than @str2 */
	friend bool operator>(const String&, const String&);

};

/* Reads a String until a delimiting character is met */
void getline(
	std::istream& in,
	String& string,
	const unsigned int len = 255,
	const char delim = '\n'
);