#pragma once
#include <ostream>
#include <fstream>
#include <ctime>

template <typename T>
class Matrix
{
	T** matrix;

	unsigned length;
	unsigned width;

	public:
	explicit Matrix(const char* filepath);
	Matrix(unsigned length, unsigned width);
	Matrix(int** matrix, unsigned length, unsigned width);
	Matrix(Matrix& other);
	Matrix(Matrix&& other) noexcept;
	~Matrix();

	T getValue(unsigned indL, unsigned indW) const;
	T setValue(unsigned indL, unsigned indW, T value) const;
	void fillRandom(unsigned max = 10) const;
	void clear() const;
	Matrix transpose() const;

	friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& m);
	Matrix& operator*(const Matrix& other) const;
	Matrix& operator=(const Matrix& other);
	Matrix& operator^(const unsigned degree);
	Matrix& operator=(Matrix&& other) noexcept;
};

template <typename T>
Matrix<T>::Matrix(const char* filepath)
{
	std::ifstream input(filepath);

	if (!input.is_open())
		return;

	input >> length;
	input >> width;
	if (width <= 0 || length <= 0)
		throw std::runtime_error("Bad input");

	matrix = new T*[length];
	for (unsigned i = 0; i < length; ++i)
		matrix[i] = new T[width];

	for (unsigned i = 0; i < length; ++i)
		for (unsigned j = 0; j < width; ++j)
			input >> matrix[i][j];
}

template <typename T>
Matrix<T>::Matrix(const unsigned length, const unsigned width)
{
	this->length = length;
	this->width = width;
	this->matrix = new T*[length];
	for (unsigned i = 0; i < length; ++i)
		matrix[i] = new T[width];
}

template <typename T>
Matrix<T>::Matrix(int** matrix, const unsigned length, const unsigned width)
{
	this->matrix = matrix;
	this->length = length;
	this->width = width;
}

template <typename T>
Matrix<T>::Matrix(Matrix<T>& other)
{
	width = other.width;
	length = other.length;
	matrix = new T*[length];
	for (unsigned i = 0; i < length; ++i)
		matrix[i] = new T[width];

	for (unsigned i = 0; i < length; ++i)
		for (unsigned j = 0; j < width; ++j)
			matrix[i][j] = other.matrix[i][j];
}

template <typename T>
Matrix<T>::Matrix(Matrix<T>&& other) noexcept
{
	matrix = other.matrix;
	other.matrix = nullptr;
	width = other.width;
	length = other.length;
}

template <typename T>
Matrix<T>::~Matrix()
{
	if (matrix)
		for (unsigned i = 0; i < length; ++i)
			delete[] matrix[i];
}

template <typename T>
T Matrix<T>::getValue(const unsigned indL, const unsigned indW) const
{
	return matrix[indL][indW];
}

template <typename T>
T Matrix<T>::setValue(const unsigned indL, const unsigned indW, const T value) const
{
	matrix[indL][indW] = value;
	return value;
}

template <typename T>
void Matrix<T>::fillRandom(const unsigned max) const
{
	static auto seed = static_cast<unsigned>(time(nullptr));
	srand(seed++);
	for (unsigned i = 0; i < length; ++i)
		for (unsigned j = 0; j < width; ++j)
			matrix[i][j] = rand() % max;
}

template <typename T>
void Matrix<T>::clear() const
{
	for (unsigned i = 0; i < length; ++i)
		for (unsigned j = 0; j < width; ++j)
			matrix[i][j] = 0;
}

template <typename T>
Matrix<T> Matrix<T>::transpose() const
{
	if (length != width)
	{
		throw std::runtime_error("Cannot transpose non-square matrix");
	}
	const auto result = new Matrix<T>(length, width);
	for (unsigned i = 0; i < length; ++i)
		for (unsigned j = 0; j < i; ++j)
			std::swap(matrix[i][j], matrix[j][i]);
	return *result;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& m)
{
	for (unsigned i = 0; i < m.length; ++i)
	{
		for (unsigned j = 0; j < m.width; ++j)
			os << m.matrix[i][j] << ' ';
		os << std::endl;
	}
	return os;
}

template <typename T>
Matrix<T>& Matrix<T>::operator*(const Matrix<T>& other) const
{
	if (width != other.length)
		throw std::runtime_error("Wrong matrix size");
	const auto result = new Matrix(width, other.length);
	result->clear();
	for (unsigned i = 0; i < result->length; ++i)
		for (unsigned j = 0; j < result->width; ++j)
		{
			for (unsigned k = 0; k < width; ++k)
				result->matrix[i][j] += (matrix[i][k] * other.matrix[k][j]);
		}
	return *result;
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other)
{
	width = other.width;
	length = other.length;

	for (unsigned i = 0; i < length; ++i)
		for (unsigned j = 0; j < width; ++j)
			matrix[i][j] = other.matrix[i][j];

	return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator^(const unsigned degree)
{
	if (width != length)
		throw std::runtime_error("Wrong matrix size");

	Matrix* result = new Matrix(*this);
	for (unsigned z = 1; z < degree; ++z)
		*result = *result * *this;

	return *result;
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(Matrix<T>&& other) noexcept
{
	matrix = other.matrix;
	other.matrix = nullptr;
	width = other.width;
	length = other.length;
	return *this;
}