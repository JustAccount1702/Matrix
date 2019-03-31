#include <istream>
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

	friend std::ostream& operator<<(std::ostream& os, const Matrix& other);
	Matrix& operator*(const Matrix& other) const;
	Matrix& operator=(const Matrix& other);
	Matrix& operator^(const unsigned degree);
	Matrix& operator=(Matrix&& other) noexcept;
};
