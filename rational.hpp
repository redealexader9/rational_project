#pragma once
#include <iostream>
#include <sstream>
class Rational {
public:
	int numerator;
	int denominator;
	static const int doubleBase = 1000000;
	Rational() {
		numerator = 0;
		denominator = 1;
		//doubleBase = 1000000;
	}
	Rational operator+(const Rational& add);
	Rational operator-(const Rational& subtract);
	Rational operator*(const Rational& multiply);
	Rational operator/(const Rational& divide);
	Rational operator -() const;

	Rational& operator +=(Rational const& src);
	Rational& operator -=(Rational const& src);
	Rational& operator *=(Rational const& src);
	Rational& operator /=(Rational const& src);
	//bool operator ==(Rational const& rhs) const;
	bool operator !=(Rational const& rhs) const;
	bool operator <(Rational const& rhs) const;
	bool operator >=(Rational const& rhs) const;
	bool operator >(Rational const& rhs) const;
	bool operator <=(Rational const& rhs) const;
	Rational(int fraction);
	explicit Rational(double fraction);
	operator double() const;
	explicit operator int() const;
	friend std::istream& operator >> (std::istream&, Rational&);
	Rational& operator ++();
	Rational& operator --();
	Rational operator ++(int);
	Rational operator --(int);
	Rational(int num, int denom);
	int num();
	int den();
	void num(int n);
	void den(int d);

};

std::ostream& operator << (std::ostream& os, Rational const& print);

