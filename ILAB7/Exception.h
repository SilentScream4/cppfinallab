#pragma once
#include <stdexcept>

class Exception : public std::exception {

	const char* msg;
	int line;
	const char* file;
	const char* info;

public:

	Exception(const char* msg, const int line, const char* file, const char* info = '\0') {
		this->msg = msg;
		this->line = line;
		this->file = file;
		this->info = info;
	}

	/*~Exception() {
		delete[] msg;
		delete[] file;
		delete[] info;
	}*/

	const char* getMsg() {
		return msg;
	}

	int getLine() {
		return line;
	}

	const char* getFile() {
		return file;
	}

	const char* getInfo() {
		return info;
	}

	void setInfo(const char* info) {
		this->info = info;
	}

};