#pragma once

#include <vector>
#include <string>

class matrixImpl {
public:
	std::vector<std::vector<double>> data;

	matrixImpl(int columns, int rows, int min, int max);
	matrixImpl(std::vector<std::vector<double>> matrix);
	void print();
	long double calculate_determinant(int mode);
	std::vector<std::vector<double>> generate_matrix(int columns, int rows, int min, int max);
private:
	long double det = 1;
	void determinant();
	void determinantStep(size_t i, size_t N);
	void determinantRange(size_t l, size_t m);
	void swap_rows(int firstRow, int secondRow);
	double get_random_double(int min, int max);
};