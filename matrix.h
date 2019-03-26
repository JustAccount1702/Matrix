#include <istream>
class Matrix
{
	int** matrix;

	int length;
	int width;

	public:
	Matrix(const char* filepath);
	int getValue(int indL, int indW);
	int setValue(int indL, int indW, int value);
	friend std::ostream& operator<<(std::ostream& is, const Matrix& m);	
};
