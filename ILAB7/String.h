#pragma once
#include <iostream>

class String {

	char* str;
	size_t length;

public:

	String();
	String(const char*);
	String(const String&);
	~String();

	/* Returns String length without terminator */
	int getLength();

	/* Returns C-style string (immutable) */
	const char* get() const;
	/* Copies C-style string recieved as a parameter */
	void set(const char*);

	String& operator=(const char*);
	String& operator=(const String&);

	friend String operator+(const String&, const String&);
	friend String operator+(const String&, const char);

	String& operator+=(const String&);
	String& operator+=(const char);

	friend bool operator==(const String&, const String&);
	friend bool operator!=(const String&, const String&);

	char& operator[](const int index);

	friend std::ostream& operator<<(std::ostream&, const String&);

};

/* Reads a String until a delimiting character is met */
void getline(
	std::istream& in,
	String& string,
	const unsigned int len = 255,
	const char delim = '\n'
);