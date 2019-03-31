#include "matrix.h"
#include <fstream>
#include <istream>
#include <iostream>
#include <ctime>

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
	for (unsigned i = 0; i < length; ++i)
		matrix[i] = new int[width];

	for (unsigned i = 0; i < length; ++i)
		for (unsigned j = 0; j < width; ++j)
			input >> matrix[i][j];
}

Matrix::Matrix(const unsigned length, const unsigned width)
{
	this->length = length;
	this->width = width;
	this->matrix = new int*[length];
	for (unsigned i = 0; i < length; ++i)
		matrix[i] = new int[width];
}

Matrix::Matrix(int** matrix, const unsigned length, const unsigned width)
{
	this->matrix = matrix;
	this->length = length;
	this->width = width;
}

Matrix::Matrix(Matrix& other)
{
	width = other.width;
	length = other.length;
	matrix = new int*[length];
	for (unsigned i = 0; i < length; ++i)
		matrix[i] = new int[width];

	for (unsigned i = 0; i < length; ++i)
		for (unsigned j = 0; j < width; ++j)
			matrix[i][j] = other.matrix[i][j];
}

Matrix::Matrix(Matrix&& other) noexcept
{
	matrix = other.matrix;
	other.matrix = nullptr;
	width = other.width;
	length = other.length;
}


Matrix::~Matrix()
{
	if (matrix)
	for (unsigned i = 0; i < length; ++i)
		delete[] matrix[i];
}

int Matrix::getValue(const unsigned indL, const unsigned indW) const
{
	return matrix[indL][indW];
}

int Matrix::setValue(const unsigned indL, const unsigned indW, const int value) const
{
	matrix[indL][indW] = value;
	return value;
}

void Matrix::fillRandom(const unsigned max) const
{
	static auto seed = static_cast<unsigned>(time(nullptr));
	srand(seed++);
	for (unsigned i = 0; i < length; ++i)
		for (unsigned j = 0; j < width; ++j)
			matrix[i][j] = rand() % max;
}

void Matrix::clear() const
{
	for (unsigned i = 0; i < length; ++i)
		for (unsigned j = 0; j < width; ++j)
			matrix[i][j] = 0;
}

Matrix Matrix::transpose() const
{
	if (length != width)
	{
		throw std::runtime_error("Cannot transpose non-square matrix");
	}
	const auto result = new Matrix(length, width);
	for (unsigned i = 0; i < length; ++i)
		for (unsigned j = 0; j < i; ++j)
				std::swap(matrix[i][j], matrix[j][i]);
	return *result;
}

std::ostream& operator<<(std::ostream& os, const Matrix& other)
{
	for (unsigned i = 0; i < other.length; ++i)
	{
		for (unsigned j = 0; j < other.width; ++j)
			std::cout << other.matrix[i][j] << ' ';
		os << std::endl;
	}
	return os;
}

Matrix& Matrix::operator*(const Matrix& other) const
{
	if (width != other.length)
		throw std::runtime_error("Wrong matrix size");
	const auto result = new Matrix(width, other.length);
	result->clear();
	for (unsigned i = 0; i < result->length; ++i)
		for (unsigned j = 0; j < result->width; ++j)
		{
			for (unsigned k = 0; k < width; ++k)
				result->matrix[i][j] += (matrix[i][k]*other.matrix[k][j]);
		}
	return *result;
}

Matrix& Matrix::operator=(const Matrix& other)
{
	width = other.width;
	length = other.length;

	for (unsigned i = 0; i < length; ++i)
		for (unsigned j = 0; j < width; ++j)
			matrix[i][j] = other.matrix[i][j];

	return *this;
}

Matrix& Matrix::operator^(const unsigned degree)
{
	if (width != length)
		throw std::runtime_error("Wrong matrix size");

	Matrix* result = new Matrix(*this);
	for (unsigned z = 1; z < degree; ++z)
		*result = *result * *this;
	/*for (unsigned z = 1; z < degree; ++z)
	{
		for (unsigned i = 0; i < result->length; ++i)
			for (unsigned j = 0; j < result->width; ++j)
				for (unsigned k = 0; k < result->width; ++k)
					result->matrix[i][j] += matrix[i][k] * result->matrix[k][j];
	}*/
	return *result;
}

Matrix& Matrix::operator=(Matrix&& other) noexcept
{
	matrix = other.matrix;
	other.matrix = nullptr;
	width = other.width;
	length = other.length;
	return *this;
}
