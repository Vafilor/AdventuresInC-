#include <stdexcept>
#include "Fraction.h"

//TODO prime factorization method - maybe simplify common denominator?
using std::domain_error;

Fraction::Fraction(long numerator, long denominator)
{
	this->setNumerator(numerator);
	this->setDenominator(denominator);
	this->simplify(); 
}

void Fraction::setNumerator(long numerator)
{
	this->numerator = numerator;
}

void Fraction::setDenominator(long denominator)
{
	if(denominator == 0)
	{
		throw domain_error("Denominator can not be 0 for Fraction");
	}

	this->denominator = denominator;
}

void Fraction::simplify()
{
	//TODO
}

long getNumerator() const
{
	return this->numerator;
}

long getDenominator() const 
{
	return this->denominator;
}

double toDecimal() const
{
	return this->numerator / this->denominator;
}

Fraction Fraction::operator-() const
{
	return Fraction(-this.numerator, this.denominator);
}


Fraction Fraction::operator+(const Fraction& that) const
{
	return Fraction(this->getNumerator() * that.getDenominator() + that.getNumerator() * this->getDenominator(),
			this->getDenominator() * that.getDenominator()
			);
}

Fraction Fraction::operator-(const Fraction& that) const
{
	return (*this) + (-that);
}

Fraction Fraction::operator*(const Fraction& that) const
{
	return Fraction(
			this->getNumerator() * that.getNumerator(),
			this->getDenominator() * that.getDenominator()
			);
}

Fraction Fraction::operator/(const Fraction& that) const
{
	return (*this) * that.inverse();
}

const Fraction& Fraction::operator+=(const Fraction& that)
{
	long newNumerator = 0;
	long newDenominator = 0;

	//TODO simplify after getting common

	this->setNumerator(newNumerator);
	this->setDenominator(newDenominator);

	return (*this);
}

const Fraction& Fraction::operator-=(const Fraction& that)
{
	//tODO
	return (*this);
}

const Fraction& Fraction::operator*=(const Fraction& that)
{
	//TODO
}

const Fraction& Fraction::operator/=(const Fraction& that)
{
	//TODO
}

bool Fraction::operator<(const Fraction& that) const
{
	//TODO
}	

bool Fraction::operator>(const Fraction& that) const
{
	//TODO
}

ostream& operator<<(ostream& output, const Fraction& fraction)
{
	//TODO
	return output;
}

istream& operator>>(istream& input, Fraction& fraction)
{
	return input;
}

