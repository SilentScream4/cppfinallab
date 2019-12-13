#pragma once
#include <stdexcept>

/* Exception class. Designed to help point at a specific file and line of code. 
   Can be caught and rethrown with additional info */
class Exception : public std::exception {

	const char* msg; // Core information about exception
	int line; // Line of code exception was triggered
	const char* file; // File exception was triggered in
	const char* info; // Additional info (ex. misread string name)

public:

	Exception(const char* msg, const int line, const char* file, const char* info = '\0') {
		this->msg = msg;
		this->line = line;
		this->file = file;
		this->info = info;
	}

	const char* getMsg() const {
		return msg;
	}

	int getLine() const {
		return line;
	}

	const char* getFile() const {
		return file;
	}

	const char* getInfo() const {
		return info;
	}

	void setInfo(const char* info) {
		this->info = info;
	}

};