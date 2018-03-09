#include <iostream>
#include <string>
#include <cmath>
#include "methods/optimization.h"

double fn(double *x) {
	return x[0] * x[0] + (x[1] - 2) * (x[1] - 2) - 5 * x[0] + x[1]; 
}

double f(double x) {
	return exp(x) - 2 * x;
}

int main() {
	std::string option;
	std::cout << "Welcome to optimization application!" << std::endl;
	std::cout << "Enter count of variables ('one' / 'many'): ";
	getline(std::cin, option);

	while (option != "one" && option != "many") {
		std::cout << "Incorrect option. try again: ";
		getline(std::cin, option);
	}

	if (option == "one") {
		std::cout << "Enter method ('linear' / 'dichotomy' / 'golden section'): ";
		getline(std::cin, option);

		while (option != "linear" && option != "dichotomy" && option != "golden section") {
			std::cout << "Incorrect method. try again: ";
			getline(std::cin, option);
		}

		double a, b, eps, x;

		std::cout << "Enter a: ";
		std::cin >> a;
		std::cout << "Enter b: ";
		std::cin >> b;
		std::cout << "Enter eps: ";
		std::cin >> eps;

		if (option == "linear") {
			x = linearExtremum(f, a, b, eps);
		}
		else if (option == "dichotomy") {
			x = dichotomyExtremum(f, a, b, eps);
		}
		else if (option == "golden section") {
			x = goldenSectionExtremum(f, a, b, eps);
		}

		std::cout << "Extremum for function at [" << a << ", " << b << "] is " << x << std::endl;
	}
	else {
		std::cout << "Enter method ('coordinate' / 'gradient'): ";
		getline(std::cin, option);

		while (option != "coordinate" && option != "gradient") {
			std::cout << "Incorrect method. try again: ";
			getline(std::cin, option);
		}

		double a, b, eps, lambda;

		if (option == "coordinate") {
			std::cout << "Enter a: ";
			std::cin >> a;
			std::cout << "Enter b: ";
			std::cin >> b;
		}	
		else {
			std::cout << "Enter lambda: ";
			std::cin >> lambda;
		}

		std::cout << "Enter eps: ";
		std::cin >> eps;

		double *x = NULL;

		if (option == "coordinate") {
			x = coordinateDescentExtremum(fn, 2, a, b, eps);
		}
		else if (option == "gradient") {
			x = gradientDescentExtremum(fn, 2, lambda, eps);
		}

		std::cout << "Extremum for function is (" << x[0] << ", " << x[1] << ")" << std::endl;
	}
}