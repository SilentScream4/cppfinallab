#pragma once
#include "String.h"

namespace Util {

	/* Trims excessive white spaces (double spaces, leading and trailing spaces)*/
	void trim(String&);

	/* Removes excessive spaces, makes first letters uppercase, all others lowercase*/
	void capitalizeFirstLetters(String&);

}