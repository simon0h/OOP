#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Rational.h"
using namespace std;

#ifndef RATIONAL_H
#define RATIONAL_H

Rational::Rational(int num, int den): numerator(num), denominator(den) {
	normalize();
}

void Rational::normalize() {
	int gcd;
	if (denominator < 0) {
		numerator *= -1;
		denominator *= -1;
	}
	if (numerator != 0 && denominator != 0) {
		gcd = greatestCommonDivisor(numerator, denominator);
		numerator = numerator / gcd;
		denominator = denominator / gcd;
	}
	else {
		numerator = 0;
		denominator = 0;
	}
}

int Rational::greatestCommonDivisor(int x, int y) {
    while (y != 0) {
        int temp = x % y;
        x = y;
        y = temp;
    }
    return x;
}

Rational& Rational::operator+=(const Rational& rhs) {
	int commonDenominator;
	int numeratorToAdd;
	if (numerator != 0 && rhs.numerator != 0) {
		commonDenominator = denominator * rhs.denominator;
		numeratorToAdd = rhs.numerator * denominator;
		numerator *= rhs.denominator;
		numerator = numerator + numeratorToAdd;
		denominator = commonDenominator;
		normalize();
	}
	else {
		numerator = rhs.numerator;
		denominator = rhs.denominator;
	}
	return *this;
}

Rational& Rational::operator++() {
	numerator += denominator;
	return *this;
}

Rational Rational::operator++(int) {
	numerator += denominator;
	Rational temp(*this);
	return temp;
}

Rational::operator bool() const {
	return (numerator != 0);
}


ostream& operator<< (ostream& os, const Rational& r) {
	os << r.numerator << "/" << r.denominator;
	return os;
}

istream& operator>> (istream& is, Rational& r) {
	char dash;
	is >> r.numerator >> dash >> r.denominator;
	return is;
}

Rational operator+ (const Rational& lhs, const Rational& rhs) {
	Rational sum;
	sum += lhs;
	sum += rhs;
	return sum;
}

bool operator== (const Rational& lhs, const Rational& rhs) {
	return (lhs.numerator == rhs.numerator && lhs.denominator == rhs.denominator);
}

bool operator!= (const Rational& lhs, const Rational& rhs) {
	if (lhs == rhs) {
		return false;
	}
	return true;
}

Rational& operator-- (Rational& lhs) {
	lhs += -1;
	return lhs;
}

Rational operator-- (Rational& lhs, int) {
	Rational negative(-1, 1);
	negative += lhs;
	return negative;
}

bool operator< (const Rational& lhs, const Rational& rhs) {
	int lhsNumerator;
	int rhsNumerator;
	lhsNumerator = lhs.numerator * rhs.denominator;
	rhsNumerator = rhs.numerator * lhs.denominator;
	if (lhsNumerator > rhsNumerator) {
		return false;
	}
	return true;
}

bool operator> (const Rational& lhs, const Rational& rhs) {
	return (lhs < rhs);
}

bool operator<= (const Rational& lhs, const Rational& rhs) {
	if (lhs < rhs || lhs == rhs) {
		return true;
	}
	return false;
}

bool operator>= (const Rational& lhs, const Rational& rhs) {
	if (lhs < rhs || lhs == rhs) {
		return false;
	}
	return true;
}

#endif









