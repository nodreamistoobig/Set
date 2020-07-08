#include <iostream>
#include <set>
#include "Set.h"

using namespace std;

Set Set::getSet() {
	return symbols;
}

void Set::addToSet(unsigned char c) {
	symbols.insert(c);
}

void Set::removeFromSet(unsigned char c) {
	symbols.erase(c);
}

Set Set:: operator +(const Set& s) const {
	Set res(symbols);
	for (set<unsigned char>::iterator it = s.symbols.begin(); it != s.symbols.end(); it++)
		res.addToSet(*it);
	return res;
}

Set Set:: operator -(const Set& s) const {
	Set res(symbols);
	for (set<unsigned char>::iterator it = s.symbols.begin(); it != s.symbols.end(); it++)
		if (res.symbols.find(*it)!=res.symbols.end())
			res.removeFromSet(*it);
	return res;
}

Set& Set:: operator +=(const Set& s) {
	for (set<unsigned char>::iterator it = s.symbols.begin(); it != s.symbols.end(); it++)
		this->addToSet(*it);
	return *this;
}

Set& Set:: operator -=(const Set& s) {
	for (set<unsigned char>::iterator it = s.symbols.begin(); it != s.symbols.end(); it++)
		if (symbols.find(*it) != symbols.end())
			this->removeFromSet(*it);
	return *this;
}

bool Set:: operator >(const Set& s) const {
	return symbols.size() > s.symbols.size();
}

bool Set:: operator <(const Set& s) const {
	return symbols.size() < s.symbols.size();
}

bool Set:: operator >=(const Set& s) const {
	return symbols.size() >= s.symbols.size();
}

bool Set:: operator <=(const Set& s) const {
	return symbols.size() <= s.symbols.size();
}

bool Set:: operator ==(const Set& s) const {
	return symbols == s.symbols;
}

bool Set:: operator !=(const Set& s) const {
	return symbols != s.symbols;
}

Set Set:: overlap(const Set& s) const {
	Set res;
	for (set<unsigned char>::iterator it = s.symbols.begin();  it != s.symbols.end(); it++)
		if (symbols.find(*it) != symbols.end())
			res.addToSet(*it);
	return res;
}

istream& operator >>(istream& in, Set& s)
{
	unsigned char c;
	in >> c;
	s.symbols.insert(c);
	return in;
}

ostream& operator <<(ostream& out, const Set& s)
{
	for (set<unsigned char>::iterator it = s.symbols.begin(); it != s.symbols.end(); it++)
		out << *it;
	return out;
}