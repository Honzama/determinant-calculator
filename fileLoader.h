#pragma once

#include "matrixImpl.h"

#include <string>
#include <iostream>
#include <fstream>

class fileLoader {
public:
	fileLoader(std::string n);
	void openOutput();
	void closeOutput();
	void openInput();
	void closeInput();
	bool isOpened();
	void writeMatrix(matrixImpl matrix);
	matrixImpl readMatrix();
private:
	std::string name;
	std::ofstream fileOut;
	std::ifstream fileIn;
	bool opened;
};