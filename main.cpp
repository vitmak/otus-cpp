#include "matrix.h"
#include <iostream>


int main() {
	Matrix<int, 0> matrix;

	for (auto index = 0; index <= 9; ++index) {
		matrix[index][index] = index;
	}

	for (auto row = 9, column = 0; row >= 0; --row, ++column) {
		matrix[row][column] = row;
	}

	for (auto row = 1; row <= 8; ++row) {
		for (auto column = 1; column <= 8; ++column) {
			std::cout << matrix[row][column].GetValue() << " ";
		}
		std::cout << std::endl;
	}

	std::cout << matrix.size() << std::endl;

	for (const auto& v : matrix)
	{
		int x;
		int y;
		int value;
		std::tie(x, y, value) = v;
		std::cout << x << y << value << std::endl;
	}

	((matrix[100][100] = 314) = 0) = 217;

	return 0;
}