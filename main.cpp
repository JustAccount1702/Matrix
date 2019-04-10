#include <iostream>
#include "matrix.hpp"
#include "Fraction.hpp"

int main()
{
	Matrix<Fraction> mat("input.txt");

	std::cout << "Transfer matrix" << std::endl << mat << std::endl;
	std::cout << "Transfer matrix ^2" << std::endl << (mat^2) << std::endl;
	std::cout << "Transfer matrix ^3" << std::endl << (mat^3) << std::endl;
	Matrix<Fraction> baseVector(1,4);
	for (int i = 0; i < 4; ++i)
		baseVector.setValue(0,i, Fraction(1,4));
	
	for (int i = 0; i < 4; ++i)
		baseVector = baseVector * mat;
	std::cout << baseVector << std::endl;
	return 0;	
}
