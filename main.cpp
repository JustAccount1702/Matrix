#include <iostream>
#include "matrix.hpp"
#include "Fraction.hpp"

int main()
{
	Matrix<Fraction> mat("input.txt");

	std::cout << "Transfer matrix" << std::endl << mat << std::endl;
    Matrix<Fraction> baseVector(1,4);
	for (int i = 0; i < 4; ++i)
		baseVector.setValue(0, i, Fraction(1,4));
    Matrix<Fraction> result = baseVector;
	for (int i = 0; i < 40; ++i)
		result = baseVector * mat;
	std::cout << result << std::endl;
	return 0;	
}
