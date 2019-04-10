#include <iostream>

class Fraction
{
	bool sign;
	unsigned numerator;
	unsigned denominator;

	void normalize();
public:
	Fraction();
	Fraction(int a, int b);

	Fraction inverse() const;

	Fraction operator+=(const Fraction& other);
	Fraction operator-=(const Fraction& other);
	Fraction operator*=(const Fraction& other);
	Fraction operator/=(const Fraction& other);

	Fraction operator+(const Fraction& other) const;
	Fraction operator-(const Fraction& other) const;
	Fraction operator*(const Fraction& other) const;
	Fraction operator/(const Fraction& other) const;
	Fraction operator=(const Fraction& other);
	Fraction operator=(const int other);

	Fraction operator-();

	friend std::ostream& operator<<(std::ostream& os, const Fraction& f);
	friend std::istream& operator>>(std::istream& is, Fraction& f);
	Fraction operator^(const int degree);

	operator int() const;
	operator double() const;

	bool operator== (const Fraction& other) const;
	bool operator> (const Fraction& other) const;
	bool operator>= (const Fraction& other) const;
	bool operator<(const Fraction & other) const;
	bool operator<=(const Fraction & other) const;

};
