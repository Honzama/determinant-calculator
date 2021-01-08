#include "console.h"
#include "matrixImpl.h"
#include "fileLoader.h"

#include <iostream>
#include <string>
#include <vector>
#include <chrono>

const std::string app_name("Determinant calculator");
const std::string app_version("1.0.0");
const std::string app_description("Welcome to the matrix single/multi thread determinant calculator.");
const std::string spacer("---------------------------------------------------------------");

const std::string error_parameters("!error in input parameters!");
const std::vector<std::string> parameters = {"single", "multi", "--help"};
const std::vector<std::string> difficulty_names = {"50x50", "150x150", "250x250", "500x500", "750x750", "1000x1000"};
const std::vector<int> difficulty_values = {50, 150, 250, 500, 750, 1000};
const int matrix_range = 1000;
const std::string help_description = "Please insert parameter \"single\" or \"multi\" for automatic test of "+std::to_string(difficulty_values.size())+
		" matrices in "+std::to_string(difficulty_names.size())+" different sizes. Each matrix will be saved in \"size\" + \".txt\" file.";

void bootUp();
void print(std::string txt);
bool checkParameters(char* argv[]);
void calculateMatrix(matrixImpl m, char* argv[], std::string difficulty);

int run(int argc, char* argv[]) {
	bootUp();

	if (argc != 2 || (argc == 2 && !checkParameters(argv))) {
		print(error_parameters); 
		return -1; 
	}

	if (argv[1] == parameters[2]) { print(help_description); return 0; }

	print("	Testing matrices in "+ std::string(argv[1])+" thread mode: \n");

	for (size_t i = 0; i < difficulty_names.size(); i++) {
		print(spacer);
		print("DIFFICULTY TEST: "+difficulty_names[i]);
		print(" -generating matrix");
		calculateMatrix(matrixImpl(difficulty_values[i], difficulty_values[i], matrix_range, matrix_range), argv, difficulty_names[i]);
		print(spacer);
		if(i+1 < difficulty_names.size()) print("");
	}
	
	return 0;
}

void calculateMatrix(matrixImpl m, char* argv[], std::string difficulty) {
	print(" -generating file");

	fileLoader fl = fileLoader(difficulty);
	fl.openOutput();
	fl.writeMatrix(m);
	fl.closeOutput();

	print(" -calculating determinant");
	print(spacer);
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	
	if (argv[1] == parameters[0]) print("det = "+ std::to_string(m.calculate_determinant(0)));
	if (argv[1] == parameters[1]) print("det = " + std::to_string(m.calculate_determinant(1)));

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	print("");

	std::cout << "Determinant calculation time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "ms" << std::endl;
	std::cout << "Determinant calculation time difference = " << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() << "s" << std::endl;
}

bool checkParameters(char* argv[]) {
	for (std::string parameter : parameters) {
		if (argv[1] == parameter) return true;
	}
	return false;
}

void bootUp() {
	print(app_name + " " + app_version);
	print("BOOTING UP...");
	print("");
	print(app_description);
	print(spacer);
}

void print(std::string txt) {
	std::cout << txt << std::endl;
}