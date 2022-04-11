#include <iostream>
#include <cmath>
#include <numeric>
#include <vector>
#include <iomanip>
#include "rational.hpp"
using std::vector;

vector<int> reduceFraction(int numerator, int denominator);

vector<int> addFraction(int num1, int den1, int num2, int den2) 
{
	vector<int> fraction;
	int multiple1;
	int lcm = std::lcm(den1, den2);
	int denAns = lcm;
	int numAns;

	if (den1 == den2) {
		fraction = reduceFraction(num1 + num2, den1);
	}
	else if (lcm == den1) {
		multiple1 = den1 / den2;
		numAns = (num2 * multiple1) + num1;
		fraction = reduceFraction(numAns, denAns);
	}
	else if (lcm == den2) {
		multiple1 = den2 / den1;
		numAns = (num1 * multiple1) + num2;
		fraction = reduceFraction(numAns, denAns);
	}
	else {
		multiple1 = lcm / den1;
		int multiple2 = lcm / den2;
		numAns = (num1 * multiple1) + (num2 * multiple2);
		fraction = reduceFraction(numAns, denAns);
	}
	return fraction;

}

vector<int> subFraction(int num1, int den1, int num2, int den2) 
{
	vector<int> fraction;
	int multiple1;
	int lcm = std::lcm(den1, den2);
	int denAns = lcm;
	int numAns;

	if (den1 == den2) {
		fraction = reduceFraction(num1 - num2, lcm);
	}
	else if (lcm == den1) {
		multiple1 = den1 / den2;
		numAns = num1 - (num2 * multiple1);
		fraction = reduceFraction(numAns, denAns);
	}
	else if (lcm == den2) {
		multiple1 = den2 / den1;
		numAns = (num1 * multiple1) - num2;
		fraction = reduceFraction(numAns, denAns);
	}
	else {
		multiple1 = lcm / den1;
		int multiple2 = lcm / den2;
		numAns = (num1 * multiple1) - (num2 * multiple2);
		fraction = reduceFraction(numAns, denAns);
	}
	return fraction;

}
vector<int> multFraction(int num1, int den1, int num2, int den2) {
	int numResult = num1 * num2;
	int denResult = den1 * den2;
	vector<int> reducedFraction = reduceFraction(numResult, denResult);
	return reducedFraction;
}
vector<int> divideFraction(int num1, int den1, int num2, int den2) {

	if (den1 == 0 || den2 == 0 || num1 == 0 || num2 == 0) {
		throw std::domain_error("Cannot divide by 0");

	}
	vector<int> dividedFraction = multFraction(num1, den1, den2, num2);

	return dividedFraction;
}

vector<int> reduceFraction(int numerator, int denominator) 
{
	vector<int> fraction(2);
	if (numerator == 0) {
		fraction.at(0) = 0;
		fraction.at(1) = 1;
		return fraction;
	}
	if (denominator == 0) {
		throw std::domain_error("Denominator cannot be set to 0");
	}
	int d;
	d = std::gcd(numerator, denominator);
	int num1 = numerator;
	int num2 = denominator;
	numerator = numerator / d;
	denominator = denominator / d;

	if (numerator < 0 && denominator < 0) {
		numerator = abs(numerator);
		denominator = abs(denominator);
	}
	else if (denominator < 0) {
		numerator = 0 - numerator;
		denominator = abs(denominator);
	}
	fraction.at(0) = numerator;
	fraction.at(1) = denominator;
	return fraction;
}
int Rational::den() 
{
	return Rational::denominator;
}
int Rational::num() 
{
	return Rational::numerator;
}
void Rational::num(int setNum) 
{
	vector<int> frac = reduceFraction(setNum, Rational::denominator);
	Rational::denominator = frac.at(1);
	Rational::numerator = frac.at(0);
}
void Rational::den(int setDen) 
{
	vector<int> frac = reduceFraction(Rational::numerator, setDen);
	Rational::numerator = frac.at(0);
	Rational::denominator = frac.at(1);
}


Rational Rational::operator+(const Rational& add)
{
	vector<int> added = addFraction(this->numerator, this->denominator, add.numerator, add.denominator);
	Rational a(added.at(0), added.at(1));
	return a;
}

Rational Rational::operator-(const Rational& subtract)
{
	vector<int> subbed = subFraction(this->numerator, this->denominator, subtract.numerator, subtract.denominator);
	Rational s(subbed.at(0), subbed.at(1));
	return s;
}

Rational Rational::operator*(const Rational& multiply)
{
	vector<int> mult = multFraction(this->numerator, this->denominator, multiply.numerator, multiply.denominator);
	Rational m(mult.at(0), mult.at(1));
	return m;
}

Rational Rational::operator/(const Rational& divide)
{
	vector<int> div = divideFraction(this->numerator, this->denominator, divide.numerator, divide.denominator);
	if (this->numerator == 0 || this->denominator == 0 || divide.numerator == 0 || divide.denominator == 0) {
		throw std::domain_error("Cannot divide by 0");
	}
	Rational d(div.at(0), div.at(1));
	return d;
}

Rational Rational::operator-() const
{
	int num = 0 - this->numerator;
	Rational r(num, this->denominator);
	return r;
}

Rational& Rational::operator+=(Rational const& srcAdd)
{
	Rational leftSide(this->numerator, this->denominator);
	Rational rightSide(srcAdd.numerator, srcAdd.denominator);
	Rational add;
	add = leftSide + rightSide;
	this->numerator = add.numerator;
	this->denominator = add.denominator;
	return *this;
}

Rational& Rational::operator-=(Rational const& srcSub)
{
	Rational leftSide(this->numerator, this->denominator);
	Rational rightSide(srcSub.numerator, srcSub.denominator);
	Rational subtract;
	subtract = leftSide - rightSide;
	this->numerator = subtract.numerator;
	this->denominator = subtract.denominator;
	return *this;
}

Rational& Rational::operator*=(Rational const& srcMult)
{
	Rational leftSide(this->numerator, this->denominator);
	Rational rightSide(srcMult.numerator, srcMult.denominator);

	Rational multiply;
	multiply = leftSide * rightSide;
	this->numerator = multiply.numerator;
	this->denominator = multiply.denominator;
	return *this;
}

Rational& Rational::operator/=(Rational const& srcDiv)
{
	Rational leftSide(this->numerator, this->denominator);
	Rational rightSide(srcDiv.numerator, srcDiv.denominator);

	Rational divide;
	divide = leftSide / rightSide;
	this->numerator = divide.numerator;
	this->denominator = divide.denominator;
	return *this;
}





bool Rational::operator!=(Rational const& rhs) const
{
	if (this->numerator == rhs.numerator && this->denominator == rhs.denominator) {
		return false;

	}
	else {
		return true;
	}
}

bool Rational::operator<(Rational const& rhs) const
{
	double leftSide = double(this->numerator) / double(this->denominator);
	double rightSide = double(rhs.numerator) / double(rhs.denominator);
	if (leftSide < rightSide) {
		return true;
	}
	else {
		return false;
	}
}

bool Rational::operator>=(Rational const& rhs) const
{
	double leftSide = double(this->numerator) / double(this->denominator);
	double rightSide = double(rhs.numerator) / double(rhs.denominator);
	if (leftSide >= rightSide) {
		return true;
	}
	else {
		return false;
	}
}

bool Rational::operator>(Rational const& rhs) const
{
	double leftSide = double(this->numerator) / double(this->denominator);
	double rightSide = double(rhs.numerator) / double(rhs.denominator);
	if (leftSide > rightSide) {
		return true;
	}
	else {
		return false;
	}
}

bool Rational::operator<=(Rational const& rhs) const
{
	double leftSide = double(this->numerator) / double(this->denominator);
	double rightSide = double(rhs.numerator) / double(rhs.denominator);
	if (leftSide <= rightSide) {
		return true;
	}
	else {
		return false;
	}
}

Rational::Rational(int fraction)	// implicit conversion from int to Rational
{
		this->numerator = fraction;
		this->denominator = 1;
}

Rational::Rational(double fraction)	//implicit conversion from double to Rational
{
	std::cout << std::showpoint << std::setprecision(1);
	vector<int> reducedFraction = reduceFraction(fraction * doubleBase, doubleBase);
	this->numerator = reducedFraction.at(0);
	this->denominator = reducedFraction.at(1);
}

Rational::operator double() const	// explicit conversion from Rational to double
{
	std::cout << std::fixed << std::setprecision(1);
	if (denominator == 1) {
		return (double)numerator;
	}
	else {
		return (double)numerator / (double)denominator;
	}
}

Rational::operator int() const	// explicit conversion from Rational to int
{
	return numerator / denominator;
}

Rational& Rational::operator++()
{
	vector<int> increment = addFraction(this->numerator, this->denominator, 1, 1);
	this->numerator = increment.at(0);
	this->denominator = increment.at(1);
	return *this;
}

Rational& Rational::operator--()
{
	vector<int> decrement = subFraction(this->numerator, this->denominator, 1, 1);
	this->numerator = decrement.at(0);
	this->denominator = decrement.at(1);
	return *this;
}

Rational Rational::operator++(int)		// Postfix increment operator
{
	Rational postAdd = *this;
	vector<int> increment = addFraction(this->numerator, this->denominator, 1, 1);
	this->numerator = increment.at(0);
	this->denominator = increment.at(1);
	return postAdd;
}

Rational Rational::operator--(int)		// Postfix decrement operator
{
	Rational postSub = *this;
	vector<int> decrement = subFraction(this->numerator, this->denominator, 1, 1);
	this->numerator = decrement.at(0);
	this->denominator = decrement.at(1);
	return postSub;
}

Rational::Rational(int n, int d) 
{
	vector<int> fract = reduceFraction(n, d);
	Rational::numerator = fract.at(0);
	Rational::denominator = fract.at(1);
}

std::ostream& operator<<(std::ostream& os, Rational const& print)
{
	os << print.numerator << "/" << print.denominator;
	return os;
}

std::istream& operator>>(std::istream& is, Rational& input)
{
	char slash;
	is >> input.numerator >> slash >> input.denominator;
	if (input.numerator < 0 && input.denominator < 0) {
		input.numerator = abs(input.numerator);
		input.denominator = abs(input.denominator);
	}
	else if (input.denominator < 0) {
		input.numerator = 0 - input.numerator;
		input.denominator = abs(input.denominator);
	}
	return is;
}

