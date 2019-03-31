#include "matrix.h"
#include <fstream>
#include <istream>
#include <iostream>

Matrix::Matrix(const char* filepath)
{
	std::ifstream input(filepath);

	if (!input.is_open())
		return;

	input >> length;
	input >> width;
	if (width <= 0 || length <= 0) 
		throw std::runtime_error("Bad input");
	
	matrix = new int*[length];
	
	for (int i = 0; i < length; ++i)
		matrix[i] = new int[width];
	for (int i = 0; i < length; ++i)
		for (int j = 0; j < width; ++j)
			input >> matrix[i][j];
}

Matrix::Matrix(int length, int width)
{
	length = length;
	width = width;
	int** matrix = new int*[length];
	for (int i = 0; i < length; ++i)
		matrix[i] = new int[width];
}

Matrix::Matrix(int** matrix, int length, int width)
{
	matrix = matrix;
	length = length;
	width = width;
}

int Matrix::getValue(const int indL, const int indW) const
{
	return matrix[indL][indW];
}

int Matrix::setValue(const int indL, const int indW, const int value) const
{
	matrix[indL][indW] = value;
	return value;
}

Matrix Matrix::transpose()
{
	if (length != width)
	{
		throw std::runtime_error("Cannot transpose non-square matrix");
	}
	Matrix* result = new Matrix(length, width);
	for (int i = 0; i < length; ++i)
		for (int j = 0; j < i; ++j)
				std::swap(matrix[i][j], matrix[j][i]);
	return *result;
}

std::ostream& operator<<(std::ostream& os, const Matrix& m)
{
	for (int i = 0; i < m.length; ++i)
	{
		for (int j = 0; j < m.width; ++j) 
			std::cout << m.matrix[i][j] << ' ';
		os << std::endl;
	}
	return os;
}

Matrix Matrix::operator*(const Matrix& m)
{
	if (width != m.length)
		throw std::runtime_error("Wrong matrix size");
	Matrix* result = new Matrix(width, m.length);
	for (int i = 0; i < result->length; ++i)
		for (int j = 0; j < result->width; ++j)
		{
			for (int k = 0; k < width; ++k)
				result->matrix[i][j] += (matrix[i][k] + m.matrix[k][j]);
		}
	return *result;
}
