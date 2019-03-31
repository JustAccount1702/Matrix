#include <iostream>
#include "matrix.h"

int main()
{
	Matrix<int> a(5,5);
	Matrix<int> b(5, 5);
	const Matrix<int> c("input.txt");
	a.fillRandom(2);
	b.fillRandom(2);

	std::cout << a;/*
	std::cout << "B:" << std::endl << b << std::endl;
	std::cout << "C:" << std::endl << c << std::endl;
	std::cout << "A*B:" << std::endl << a * b << std::endl;
	std::cout << "C^2:" << std::endl << c*c << std::endl;*/

	system("pause");
	return 0;	
}
