#include "String.h"
#include <iostream>
#include <stdexcept>
#include <cstring>

/* Unparameterized constructor instantiates empty C-string */
String::String() {
	length = 0;
	str = new char[length + 1];
	str[length] = '\0';
}

/* Parameterized constructor copies argumenent C-string */
String::String(const char* newstr) {
	length = newstr == nullptr ? 0 : strlen(newstr);
	str = new char[length + 1];
	for (int i = 0; i < length; ++i)
		str[i] = newstr[i];
	str[length] = '\0';
}

/* Copy constructor copies another String */
String::String(const String& string) {
	length = string.length;
	str = new char[length + 1];
	for (int i = 0; i < length; ++i)
		str[i] = string.str[i];
	str[length] = '\0';
}

/* Destructor return allocated memory */
String::~String() {
	if (str != nullptr)
		delete[] str;
}

/* Returns String length without terminator */
int String::getLength() {
	return length;
}

/* Returns C-style string (immutable) */
const char* String::get() const {
	return str;
}

/* Copies C-style string recieved as a parameter */
void String::set(const char* newstr) {
	length = newstr == nullptr ? 0 : strlen(newstr);
	if (str != nullptr)
		delete[] str;
	str = new char[length + 1];
	for (int i = 0; i < length; ++i)
		str[i] = newstr[i];
	str[length] = '\0';
}

/* Copies C-style string recieved as a parameter */
String& String::operator=(const char* newstr) {
	set(newstr);
	return *this;
}

/* Copies String recieved as a parameter */
String& String::operator=(const String& string) {
	set(string.str);
	return *this;
}

/* Concats two Strings */
String operator+(const String& str1, const String& str2) {
	char* newstr = new char[str1.length + str2.length + 1];
	int i = 0;
	while (i < str1.length)
		newstr[i] = str1.str[i++];
	while (i < str2.length)
		newstr[i] = str2.str[i++%str1.length];
	newstr[i] = '\0';
	return String(newstr);
}

/* Appends String with a single character */
String operator+(const String& string, const char ch) {
	char* newstr = new char[string.length + 2];
	int i = 0;
	while (i < string.length)
		newstr[i] = string.str[i++];
	newstr[i++] = ch;
	newstr[i] = '\0';
	return String(newstr);
}

/* Appends this String with another String */
String& String::operator+=(const String& string) {
	char* newstr = new char[length + string.length + 1];
	int i = 0;
	while (i < length)
		newstr[i] = str[i++];
	while (i < string.length)
		newstr[i] = string.str[i++%length];
	newstr[i] = '\0';
	if (str != nullptr)
		delete[] str;
	length += string.length;
	str = newstr;
	return *this;
}

/* Appends this String with a single character */
String& String::operator+=(const char ch) {
	char* newstr = new char[length + 2];
	int i = 0;
	while (i < length)
		newstr[i] = str[i++];
	newstr[i++] = ch;
	newstr[i] = '\0';
	if (str != nullptr)
		delete[] str;
	length++;
	str = newstr;
	return *this;
}

/* Returns true if two Strings are of the same length and consist of exactly
   the same characters */
bool operator==(const String& str1, const String& str2) {
	if (str1.length != str2.length)
		return false;
	for (int i = 0; i < str1.length; ++i)
		if (str1.str[i] != str2.str[i])
			return false;
	return true;
}

/* Returns true if two Strings are of the different length or consist of different characters */
bool operator!=(const String& str1, const String& str2) {
	return !(str1 == str2);
}

/* Returns character at index */
char& String::operator[](const int index) {
	if (index < 0 || index > length)
		throw std::out_of_range("String index out of bounds");
	return str[index];
}

/* Outputs String into stream &out */
std::ostream& operator<<(std::ostream& out, const String& string) {
	out << string.str;
	return out;
}

/* Reads a String until a delimiting character is met */
void getline(
	std::istream& in,
	String& string,
	const unsigned int len,
	const char delim
) {
	char* buf = new char[len];
	in.getline(buf, len, delim);
	if (in.fail())
		throw std::invalid_argument("Wrong input stream format (author name)");
	string.set(buf);
	delete[] buf;
}