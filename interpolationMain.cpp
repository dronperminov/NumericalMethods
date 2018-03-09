#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>

#include "methods/interpolation.h"

int main() {
	std::string option;
	std::cout << "Welcome to interpolation application!" << std::endl;
	std::cout << "How do you want to enter points? ('file' / 'keyboard'): ";
	getline(std::cin, option);

	while (option != "file" && option != "keyboard") {
		std::cout << "Incorrect option. Try again: ";
		getline(std::cin, option);
	}

	std::vector<Point> points;

	if (option == "file") {
		std::string path;
		std::cout << "Enter path to file with points: ";
		getline(std::cin, path);

		points = getPointsFromFile(path);
	}
	else {
		points = getPoints();
	}
	
	std::cout << std::endl << "Entered points:" << std::endl;
	printPoints(points);

	std::cout << std::endl << "Enter option for interpolate ('linear' / 'lagrange' / 'newtone' / 'newtone diff' / 'spline'): ";
	getline(std::cin, option);

	while (option != "linear" && option != "lagrange" && option != "newtone" && option != "newtone diff" && option != "spline") {
		std::cout << "Incorrect option. Try again: ";
		getline(std::cin, option);
	}

	std::string inputPath;
	std::cout << "Enter path to file with test X values: ";
	getline(std::cin, inputPath);

	std::string outputPath;
	std::cout << "Enter path to output file: ";
	getline(std::cin, outputPath);

	std::fstream input;
	std::fstream output;

	input.open(inputPath, std::ios::in);
	output.open(outputPath, std::ios::out);

	Point p;

	while (input >> p.x) {
		if (option == "linear") {
			p.y = linearInterpolation(p.x, points);
		}
		else if (option == "lagrange") {
			p.y = lagrangeInterpolation(p.x, points);
		}
		else if (option == "newtone") {
			p.y = newtoneInterpolation(p.x, points);
		}
		else if (option == "newtone diff") {
			p.y = newtoneInterpolationDiff(p.x, points);
		}
		else if (option == "spline") {
			p.y = splineInterpolation(p.x, points);
		}

		std::cout << "x: " << p.x << ", y: " << p.y << std::endl;
		output << p.y << std::endl;
	}

	input.close();
	output.close();
}