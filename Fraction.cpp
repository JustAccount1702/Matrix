#include <iostream>
#include <string>
#include "Fraction.hpp"

int gcf(int a, int b)
{
	if (a == 0 && b != 0)
		return b;
	if (b == 0 && a != 0)
		return a;
	while (b != 0)
	{
		int temp = a % b;
		a = b;
		b = temp;
	}
	return a;
}

Fraction::Fraction()
{
	numerator = 0;
	denominator = 1;
	sign = true;
}

Fraction::Fraction(long numer,long denum)
{
	if (denum == 0)
		throw std::runtime_error("Divivsion by zero");
	sign = ((numer >= 0 && denum >= 0) || (numer < 0 && denum < 0));
	numerator = abs(numer);
	denominator = abs(denum);
	normalize();
}

void Fraction::normalize()
{
	if (numerator == 0)
	{
		sign = true;
		denominator = 1;
		return;
	}
	long normizer = gcf(numerator, denominator);
	numerator /= normizer;
	denominator /= normizer;
}

Fraction Fraction::inverse() const
{
	if (numerator == 0)
		throw std::runtime_error("Inversion of null");
	return Fraction(denominator, numerator);
}

Fraction Fraction::operator+=(const Fraction & other)
{
	return Fraction(*this = *this + other);
}

Fraction Fraction::operator-=(const Fraction & other)
{
	return Fraction(*this = *this - other);
}

Fraction Fraction::operator*=(const Fraction & other)
{
	return Fraction(*this = *this * other);
}

Fraction Fraction::operator/=(const Fraction & other)
{
	return Fraction(*this = *this / other);
}

Fraction Fraction::operator+(const Fraction& other) const
{
	Fraction result = *this;
	if (result.denominator == other.denominator)
	{
		long temp = ((sign) ? 1 : -1)*result.numerator + ((other.sign) ? 1 : -1)*other.numerator;
		result.sign = (((temp >= 0) ? 1 : -1)*((sign) ? 1 : -1)*((other.sign) ? 1 : -1) == -1) ? false : true;
		result.numerator = abs(temp);
		result.denominator = this->denominator;
	}
	else
	{
		Fraction otherC = other;

		result.numerator *= otherC.denominator;
		otherC.numerator *= result.denominator;
		long temp = (sign ? 1 : -1)*result.numerator + (other.sign ? 1 : -1)*otherC.numerator;
		result.sign = (((temp >= 0) ? 1 : -1)*((sign) ? 1 : -1)*((other.sign) ? 1 : -1) == -1) ? false : true;
		result.numerator = abs(temp);
		result.denominator *= otherC.denominator;
	}
	result.normalize();
	return result;
}

Fraction Fraction::operator-(const Fraction & other) const
{
	Fraction result = *this;
	if (result.denominator == other.denominator)
	{
		long temp = ((sign)?1:-1)*result.numerator - ((other.sign) ? 1 : -1)*other.numerator;
		result.sign = (((temp >= 0) ? 1 : -1)*((sign) ? 1 : -1)*((other.sign) ? 1 : -1) == -1) ? false : true;
		result.numerator = abs(temp);
		result.denominator = this->denominator;
	}
	else
	{
		Fraction otherC = other;

		result.numerator *= otherC.denominator;
		otherC.numerator *= result.denominator;
		long temp = ((sign) ? 1 : -1)*result.numerator - ((other.sign) ? 1 : -1)*otherC.numerator;
		result.sign = (((temp >= 0) ? 1 : -1)*((sign) ? 1 : -1)*((other.sign) ? 1 : -1) == -1) ? true : false;
		result.numerator = abs(temp);
		result.denominator *= otherC.denominator;
	}
	result.normalize();
	return result;
}

Fraction Fraction::operator*(const Fraction& other) const
{
	Fraction result = *this;
	result.sign = ((sign && other.sign) || (!sign && !other.sign));
	result.numerator *= other.numerator;
	result.denominator *= other.denominator;
	result.normalize();

	return result;
}

Fraction Fraction::operator/(const Fraction & other) const
{
	return *this  * other.inverse();
}

Fraction Fraction::operator=(const Fraction & other)
{
	numerator = other.numerator;
	denominator = other.denominator;
	sign = other.sign;
	return *this;
}

Fraction Fraction::operator=(const long other)
{
	return (*this = Fraction(other, 1));
}

Fraction Fraction::operator-()
{
	Fraction result = *this;
	result.sign = !(result.sign);
	return result;
}


Fraction Fraction::operator^(const int degree)
{
	if (degree == 0)
			return Fraction(1, 1);
	if (degree > 0)
	{
		Fraction result = *this;

		for (int i = 1; i < degree; ++i)
			result = result * *this;
		return result;
	}
	else
	{
		Fraction result(this->inverse());
		for (int i = 1; i < abs(degree); ++i)
			result = result * this->inverse();
		return result;
	}
}

Fraction::operator int() const
{
	return (sign ? 1 : -1)*(numerator / denominator);
}

Fraction::operator double() const
{
	return (double)(sign ? 1 : -1)*(double)numerator / (double)denominator;
}

bool Fraction::operator==(const Fraction & other) const
{
	return (*this - other).numerator == 0;
}

bool Fraction::operator>(const Fraction & other) const
{
	Fraction result = (*this - other);
	return result.sign && result.numerator != 0;
}

bool Fraction::operator>=(const Fraction & other) const
{
	return (*this - other).sign;
}

bool Fraction::operator<(const Fraction & other) const
{
	return !(*this - other).sign && (*this - other).numerator != 0;
}

bool Fraction::operator<=(const Fraction & other) const
{
	return !(*this - other).sign || (*this - other).numerator == 0;
}

std::ostream & operator<<(std::ostream & os, const Fraction & f)
{
	os << ((f.sign)?' ':'-') << f.numerator << '/' << f.denominator;
	return os;
}

std::istream & operator>>(std::istream & is, Fraction & f)
{
	std::string input;
	is >> input;

	f.numerator = 0;
	f.denominator = 0;
	f.sign = (input[0] != '-');

	unsigned i = (f.sign ? 0 : 1);
	char c;
	while ((c = input[i++]) != '/' && i < input.length())
	{
		f.numerator *= 10;
		f.numerator += c - 48;
	}
	while (i < input.length())
	{
		c = input[i++];
		f.denominator *= 10;
		f.denominator += c - 48;
	}
	if (f.denominator == 0)
		f.denominator = 1;
	f.normalize();
	return is;
}
