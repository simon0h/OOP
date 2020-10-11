#include <iostream>
#include <string>

class Rational {

friend std::ostream& operator<< (std::ostream& os, const Rational& r);
friend std::istream& operator>> (std::istream& is, Rational& r);
friend bool operator== (const Rational& lhs, const Rational& rhs);
friend bool operator< (const Rational& lhs, const Rational& rhs);

public:
	Rational(int num = 0, int den = 1);

	void normalize();

	int greatestCommonDivisor(int x, int y);

	Rational& operator+= (const Rational& rhs);

	Rational& operator++ ();

	Rational operator++ (int);

	explicit operator bool() const;

private:
	int numerator;
	int denominator;

};

std::ostream& operator<< (std::ostream& os, const Rational& r);

std::istream& operator>> (std::istream& is, Rational& r);

Rational operator+ (const Rational& lhs, const Rational& rhs);

bool operator== (const Rational& lhs, const Rational& rhs);

bool operator!= (const Rational& lhs, const Rational& rhs);

Rational& operator-- (Rational& lhs);

Rational operator-- (Rational& lhs, int);

bool operator< (const Rational& lhs, const Rational& rhs);

bool operator> (const Rational& lhs, const Rational& rhs);

bool operator<= (const Rational& lhs, const Rational& rhs);

bool operator>= (const Rational& lhs, const Rational& rhs);