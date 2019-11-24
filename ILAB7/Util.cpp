#include "Util.h"
#include <string>
#include <cstdlib>

/* Trims excessive white spaces (double spaces, leading and trailing spaces)*/
void Util::trim(std::string& str) {
	std::string newstr = "";
	int i = 0;
	while (i < str.length() && str[i] == ' ')
		i++;
	for (; i < str.length(); ++i) {
		if (str[i] == ' ' && str[i + 1] != ' ')
			newstr += str[i];
		else if (str[i] != ' ')
			newstr += str[i];
	}
	str = newstr;
	return;
}

/* Removes excessive spaces, makes first letters uppercase, all others lowercase*/
void Util::capitalizeFirstLetters(std::string& str) {
	Util::trim(str);
	for (int i = 0; i < str.length(); ++i) {
		if (i == 0 || str[i - 1] == ' ')
			 str[i] = toupper(str[i]);
		else str[i] = tolower(str[i]);
	}
	return;
}