#include "matrix.h"
#include <iostream>
#include <fstream>
#include <istream>

Matrix::Matrix(const char* filepath)
{
	std::ifstream input(filepath);
	
	input >> length;
	input >> width;
	if (width <= 0 || length <= 0) 
		std::runtime_error("Bad input");
	
	int **matrix = new int*[length];
	
	for (int i = 0; i < length; ++i)
		matrix[i] = new int[width];
	for (int i = 0; i < length; ++i)
		for (int j = 0; j < width; ++j)
			input >> matrix[i][j];
}

int Matrix::getValue(int indL, int indW)
{
	return matrix[indL][indW];
}

int Matrix::setValue(int indL, int indW, int value)
{
	matrix[indL][indW] = value;
	return value;
}

std::ostream& operator<<(std::ostream& os, const Matrix& m)
{
	std::cout << "Hello";
	for (int i = 0; i < m.length; ++i)
	{
		for (int j = 0; j < m.width; ++j) 
			os << m.matrix[i][j] << ' ';
		os << std::endl;
	}
	return os;
}
