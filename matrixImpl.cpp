#include "matrixImpl.h"

#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <thread>

matrixImpl::matrixImpl(int columns, int rows, int min, int max) {
	data = generate_matrix(columns, rows, min, max);
}

matrixImpl::matrixImpl(std::vector<std::vector<double>> matrix) {
	data = matrix;
}

void matrixImpl::determinantStep(size_t i, size_t N) {
	double pivotElement = data[i][i];
	size_t pivotRow = i;
	for (size_t row = i + 1; row < N; ++row) {
		if (std::abs(data[row][i]) > std::abs(pivotElement)) {
			pivotElement = data[row][i];
			pivotRow = row;
		}
	}
	if (pivotElement == 0.0) {
		det = 0;
		return;
	}
	if (pivotRow != i) {
		data[i].swap(data[pivotRow]);
		det *= -1.0;
	}
	det *= pivotElement;

	for (size_t row = i + 1; row < N; ++row) {
		for (size_t col = i + 1; col < N; ++col) {
			data[row][col] -= data[row][i] * data[i][col] / pivotElement;
		}
	}
}

void matrixImpl::determinant() {
	size_t N = static_cast<size_t>(data.size());
	
	for (size_t i = 0; i < N; ++i)
		determinantStep(i, N);
}

void matrixImpl::determinantRange(size_t l, size_t m) {
	size_t N = static_cast<size_t>(data.size());

	for (size_t i = l; i < m; ++i)
		determinantStep(i, N);
}

long double matrixImpl::calculate_determinant(int mode) {
	if (mode == 0) { determinant(); }
	if (mode == 1) {
		size_t N = static_cast<size_t>(data.size());

		std::vector<std::thread> threads;

		for (size_t i = 0; i < N; i++) {
			threads.push_back(std::thread(&matrixImpl::determinantRange, this, size_t(i), size_t(i + 1)));
		}

		for (auto& thr : threads) {
			thr.join();
		}
	}

	return det;
}

void matrixImpl::swap_rows(int firstRow, int secondRow) { swap(data[firstRow], data[secondRow]); }

void matrixImpl::print() {
	std::cout << std::setprecision(2) << std::fixed;
	for(size_t i = 0; i < data.size(); i++) {
		std::cout << "[";
		for (size_t l = 0; l < data[i].size(); l++) {
			if (l +1 < data[i].size()) std::cout << data[i][l] << ", ";
			else std::cout << data[i][l];
		}
		std::cout << "]" << std::endl;
	}
}

std::vector<std::vector<double>> matrixImpl::generate_matrix(int columns, int rows, int min, int max) {
	std::vector<std::vector<double>> matrix;

	for (int i = 0; i < columns; i++) {
		std::vector<double> temp;
		for (int l = 0; l < rows; l++) {
			temp.push_back(get_random_double(min, max));
		}
		matrix.push_back(temp);
	}

	return matrix;
}

double matrixImpl::get_random_double(int min, int max) {
	static std::mt19937 mt{ std::random_device{}() };
	static std::uniform_real_distribution<> dist(-min, max);
	return dist(mt);
}