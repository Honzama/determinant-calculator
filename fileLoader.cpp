#include "fileLoader.h"

#include <string>
#include <fstream>

fileLoader::fileLoader(std::string n) : name(n) {}

void fileLoader::openOutput() {
	if (!opened) {
		fileOut.open(name + ".txt");
		opened = true;
	}
}

void fileLoader::closeOutput() {
	if (opened) {
		fileOut.close();
		opened = false;
	}
}

void fileLoader::openInput() {
	if (!opened) {
		fileIn.open(name + ".txt");
		opened = true;
	}
}

void fileLoader::closeInput() {
	if (opened) {
		fileIn.close();
		opened = false;
	}
}

bool fileLoader::isOpened() { return opened; }

void fileLoader::writeMatrix(matrixImpl matrix) {
	for (size_t i = 0; i < matrix.data.size(); i++) {
		fileOut << "[";
		for (size_t l = 0; l < matrix.data[i].size(); l++) {
			if (l + 1 < matrix.data[i].size()) fileOut << matrix.data[i][l] << " ";
			else fileOut << matrix.data[i][l];
		}
		fileOut << "]" << std::endl;
	}
}

matrixImpl fileLoader::readMatrix() {
	std::vector<std::vector<double>> matrix;

	std::string line = "";
	std::string number = "";

	while (std::getline(fileIn, line)) {
		std::vector<double> l = {};
		for (char ch : line) {
			if (ch == '[' || ch == ' ' || ch == ']') {
				if (number.size() > 0) {
					l.push_back(std::stod(number));
					number = "";
				}
			}
			else {
				number += ch;
			}
		}
		matrix.push_back(l);
	}

	return matrixImpl(matrix);
}