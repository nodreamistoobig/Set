#include <iostream>
#include <set>

using namespace std;


class Set {
	set <unsigned char> symbols;
public:
	Set(set<unsigned char> s) : symbols(s) {}
	Set() {}
	Set getSet();
	void addToSet(unsigned char c);
	void removeFromSet(unsigned char c);
	Set operator +(const Set& s) const;
	Set operator -(const Set& s) const;
	Set& operator +=(const Set& s);
	Set& operator -=(const Set& s);

	bool operator >(const Set& s) const;
	bool operator <(const Set& s) const;
	bool operator >=(const Set& s) const;
	bool operator <=(const Set& s) const;
	bool operator ==(const Set& s) const;
	bool operator !=(const Set& s) const;

	Set overlap(const Set& s) const;
	friend istream& operator >>(istream& in, Set& s);
	friend ostream& operator <<(ostream& out, const Set& s);
};


