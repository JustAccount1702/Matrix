#include <iostream>
#include "matrix.h"
#include "Fractions.h"

int main()
{
	Matrix<Fraction> mat("input.txt");

	std::cout << "Transfer matrix" << std::endl << mat << std::endl;
	std::cout << "Transfer matrix ^2" << std::endl << (mat^2) << std::endl;
	std::cout << "Transfer matrix ^3" << std::endl << (mat^3) << std::endl;

	system("pause");
	return 0;	
}
