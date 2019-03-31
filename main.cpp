#include <iostream>
#include "matrix.h"

int main()
{
	Matrix m("input.txt");
	std::cout << m;


	Matrix transposedM = m.transpose();
	std::cout << transposedM;


	system("pause");
	return 0;	
}
