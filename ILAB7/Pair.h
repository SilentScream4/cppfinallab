#pragma once

/* Template Pair class - holds two items: first and second of type T and U */
template<class T, class U>
class Pair {

	T first;
	U second;

public:

	Pair(const T& first, const U& second) {
		this->first = first;
		this->second = second;
	}

	Pair(const Pair& p) {
		first = p.first;
		second = p.second;
	}

	const T& getFirst() const {
		return first;
	}

	const U& getSecond() const {
		return second;
	}

	void setFirst(const T& first) {
		this->first = first;
	}

	void setSecond(const U& second) {
		this->second = second;
	}

};

/* Template function - used to skip (assign automatically) template arguments when making a pair */
template<class T, class U>
Pair<T, U> makePair(const T& first, const U& second) {
	return Pair<T, U>(first, second);
}