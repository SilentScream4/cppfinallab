#pragma once

class String {

	char* str;
	size_t length;

public:

	String();
	String(const char*);
	String(const String&);

	int getLength();
	
	const char* get() const;
	void set(const char*);

	void operator=(const char*);

	friend String operator+(const String&, const String&);

	friend bool operator==(const String&, const String&);
	friend bool operator!=(const String&, const String&);

	char operator[](const int index);

};