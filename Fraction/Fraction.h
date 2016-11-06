//Fraction.h - represents a mathematical fraction.
//Author: Andrey Melnikov

#include <iostream>

#ifndef FRACTION_H
#define FRACTION_H

using std::istream;
using std::ostream;

//TODO polynomial class -> can add, subtract...divide by...etc
//TODO fraction -> RationalNumber? 
//TODO what about a fraction of polynomials?
//TODO - a fraction requires certain properties of its types... addition, division, multiplication, subtraction? 
//TODO - make sure to make negative always in numerator
//TODO - exception - division by zero, make custom exception
//TODO - simplify to simpest form
//TODO

//TODO is the below true?
//Fractions are always kept in simplest form, so the default equality operator is sufficient.
//TODO make default equality operator...using default.
class Fraction
{
	private:
		long numerator;
		long denominator;

		void setNumerator(long numerator);
		void setDenominator(long denominator);		

		void simplify();
	public:
		//Constructors
		Fraction(long numerator 1L, long denominator = 1L);
		
		//Getters
		long getNumerator() const;
		long getDenominator() const;
		double toDecimal() const;
		
		/*
		 * Returns the inverse fraction, which, for fraction a/b is b/a. 
		 */
		Fraction inverse() const;

		//Operators
		Fraction operator-() const;

		Fraction operator+(const Fraction& that) const;
		Fraction operator-(const Fraction& that) const;
		Fraction operator*(const Fraction& that) const;
		Fraction operator/(const Fraction& that) const;

		const Fraction& operator+=(const Fraction& that);	
		const Fraction& operator-=(const Fraction& that);
		const Fraction& operator*=(const Fraction& that);
		const Fraction& operator/=(const Fraction& that);

		bool operator<(const Fraction& that) const;
		bool operator>(const Fraction& that) const;

		//Input and Output
		friend ostream& operator<<(ostream& output, const Fraction& fraction);
		friend istream& operator>>(istream& input, Fraction& fraction);
};


#endif 
