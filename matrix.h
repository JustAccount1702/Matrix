#include <istream>
class Matrix final
{
	int** matrix;

	unsigned length;
	unsigned width;

	public:
	explicit Matrix(const char* filepath);
	Matrix(unsigned length, unsigned width);
	Matrix(int** matrix, unsigned length, unsigned width);
	Matrix(Matrix& other);
	Matrix(Matrix&& other) noexcept;
	~Matrix();

	int getValue(unsigned indL, unsigned indW) const;
	int setValue(unsigned indL, unsigned indW, int value) const;
	void fillRandom(unsigned max = 10) const;
	void clear() const;
	Matrix transpose() const;

	friend std::ostream& operator<<(std::ostream& os, const Matrix& other);
	Matrix& operator*(const Matrix& other) const;
	Matrix& operator=(const Matrix& other);
	Matrix& operator^(unsigned degree);
	Matrix& operator=(Matrix&& other) noexcept;
};
