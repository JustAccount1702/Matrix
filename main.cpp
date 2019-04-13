#include <iostream>
#include "matrix.hpp"
#include "Fraction.hpp"

int main()
{
	Matrix<Fraction> mat("input.txt");

	std::cout << "Инфинитезальная матрица: " << std::endl <<( mat.convert(double())^100) << std::endl;
    Matrix<double> baseVector(1,4);

    baseVector.setValue(0,0,0);
    baseVector.setValue(0,0,0.53);
    baseVector.setValue(0,0,0);
    baseVector.setValue(0,0,0.47);

    Matrix<double> result = baseVector;
	for (int i = 0; i < 40; ++i)
		result = baseVector * mat.convert(double());
    std::cout << "Вектор распределения вероятностей 40 степени: " << std::endl << result << std::endl;
	return 0;
}
