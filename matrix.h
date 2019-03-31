#include <istream>
class Matrix
{
	int** matrix;

	int length;
	int width;

	public:
	explicit Matrix(const char* filepath);
	Matrix(int length, int width);
	Matrix(int** matrix, int length, int width);

	int getValue(int indL, int indW) const;
	int setValue(int indL, int indW, int value) const;
	Matrix transpose();

	friend std::ostream& operator<<(std::ostream& os, const Matrix& m);
	Matrix operator*(const Matrix& m);
};
