#include "String.h"
#include <stdexcept>

String::String() {
	str = nullptr;
	length = 0;
}

String::String(const char* str) {
	const char* strc = str;
	size_t l = 1;
	while (++strc)
		l++;
	length = l;
	this->str = new char[length];
	for (int i = 0; i < l; ++i)
		this->str[i] = str[i];
}

String::String(const String& string) {
	length = string.length;
	str = new char[length];
	for (int i = 0; i < length; ++i)
		str[i] = string.str[i];
}

int String::getLength() {
	return length;
}

const char* String::get() const {
	return str;
}

void String::set(const char* newstr) {
	const char* strc = newstr;
	size_t l = 1;
	while (++strc)
		l++;
	length = l;
	delete[] str;
	str = new char[length];
	for (int i = 0; i < l; ++i)
		str[i] = newstr[i];
}

void String::operator=(const char* newstr) {
	set(newstr);
}

String operator+(const String& str1, const String& str2) {
	char* newstr = new char[str1.length + str2.length];
	int i = 0;
	while (i < str1.length)
		newstr[i] = str1.str[i++];
	while (i < str2.length)
		newstr[i] = str2.str[i++%str1.length];
	return String(newstr);
}

bool operator==(const String& str1, const String& str2) {
	if (str1.length != str2.length)
		return false;
	for (int i = 0; i < str1.length; ++i)
		if (str1.str[i] != str2.str[i])
			return false;
	return true;
}

bool operator!=(const String& str1, const String& str2) {
	return !(str1 == str2);
}

char String::operator[](const int index) {
	if (index < 0 || index >= length)
		throw std::out_of_range("String index out of bounds");
	return str[index];
}