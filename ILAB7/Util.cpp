#include "Util.h"
#include <cstdlib>

/* Trims excessive white spaces (double spaces, leading and trailing spaces)*/
void Util::trim(String& str) {
	String newstr = "";
	int i = 0;
	while (i < str.getLength() && str[i] == ' ')
		i++;
	for (; i < str.getLength(); ++i) {
		if (str[i] == ' ' && str[i + 1] != ' ' && str[i + 1])
			newstr += str[i];
		else if (str[i] != ' ')
			newstr += str[i];
	}
	str = newstr;
}

/* Removes excessive spaces, makes first letters uppercase, all others lowercase*/
void Util::capitalizeFirstLetters(String& str) {
	Util::trim(str);
	for (int i = 0; i < str.getLength(); ++i) {
		if (i == 0 || str[i - 1] == ' ')
			str[i] = toupper(str[i]);
		else str[i] = tolower(str[i]);
	}
	return;
}

/* Returns the length of a C-style string (excluding null-terminator) */
int Util::strlen(const char* str) {
	int c;
	for (c = 0; str != nullptr && str[c]; ++c);
	return c;
}

/* Copies C-style string @source into @dest. Is unsafe (doesn't make sure @dest has enough space) */
void Util::strcpy(char* dest, const char* source) {
	int i;
	for (i = 0; source != nullptr && source[i] != '\0'; ++i)
		dest[i] = source[i];
	dest[i] = '\0';
}

/* Appends C-style string @source at the end of @dest. Is unsafe (doesn't make sure @dest has enough space) */
void Util::strcat(char* dest, const char* source) {
	int i, l = strlen(dest);
	for (i = l; source != nullptr && source[i%l] != '\0'; ++i)
		dest[i] = source[i%l];
	dest[i] = '\0';
}


template<class T>
void Util::memcpy(T* dest, const T* source, const unsigned int size) {
	for (int i = 0; i < size; ++i)
		dest[i] = source[i];
}

