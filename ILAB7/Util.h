#pragma once
#include "String.h"

namespace Util {

	/* Trims excessive white spaces (double spaces, leading and trailing spaces)*/
	void trim(String&);

	/* Removes excessive spaces, makes first letters uppercase, all others lowercase*/
	void normalizeString(String&);

	/* Returns the length of a C-style string (excluding null-terminator) */
	int strlen(const char*);

	/* Copies C-style string @source into @dest. Is unsafe (doesn't make sure @dest has enough space) */
	void strcpy(char*, const char*);

	/* Appends C-style string @source at the end of @dest. Is unsafe (doesn't make sure @dest has enough space) */
	void strcat(char*, const char*);

	template<class T>
	void memcpy(T*, const T*, const unsigned int);

}