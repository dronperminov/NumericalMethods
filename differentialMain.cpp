#include <iostream>
#include <string>
#include <vector>

#include "methods/differential.h"

double f(double x, double y) {
	return 3*x*x*y;
}

int main() {
	std::string method;
	std::cout << "Welcome to differential application!" << std::endl;
	std::cout << "Enter method for solve ('euler' / 'euler advanced' / 'runge 3' / 'runge 4'): ";
	getline(std::cin, method);

	while (method != "euler" && method != "euler advanced" && method != "runge 3" && method != "runge 4") {
		std::cout << "Incorrect method.Try again: ";
		getline(std::cin, method);
	}

	double a, b, h, y0;
	std::cout << "Enter a: ";
	std::cin >> a;
	std::cout << "Enter b: ";
	std::cin >> b;
	std::cout << "Enter h: ";
	std::cin >> h;

	std::cout << "Enter y0: ";
	std::cin >> y0;

	std::vector<Point> solve;

	if (method == "euler") {
		solve = eulerMethod(f, a, b, h, y0);
	}
	else if (method == "euler advanced") {
		solve = eulerAdvancedMethod(f, a, b, h, y0);
	}
	else if (method == "runge 3") {
		solve = rungeKutt3Method(f, a, b, h, y0);
	}
	else if (method == "runge 4") {
		solve = rungeKutt4Method(f, a, b, h, y0);
	}

	for (size_t i = 0; i < solve.size(); i++) 
		std::cout << "X = " << solve[i].x << ", Y = " << solve[i].y << std::endl;
}