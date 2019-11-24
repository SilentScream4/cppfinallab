#include "Util.h"
#include <string>
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