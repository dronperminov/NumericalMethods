#include <iostream>
#include <string>
#include <vector>

#include "methods/root.h"

double f(double x) {
	return exp(x) - 3*x*x;
}

double df(double x) {
	return exp(x) - 6*x;
}

double d2f(double x) {
	return exp(x) - 6;
}

int main() {
	std::string method;
	std::cout << "Welcome to find root application!" << std::endl;
	std::cout << "Enter method for solve ('bisection' / 'chords' / 'newtone' / 'simple iteration'): ";
	getline(std::cin, method);

	while (method != "bisection" && method != "chords" && method != "newtone" && method != "simple iteration") {
		std::cout << "Incorrect method.Try again: ";
		getline(std::cin, method);
	}

	double a, b, eps, x0;

	if (method == "bisection" || method == "chords") {
		std::cout << "Enter a: ";
		std::cin >> a;
		std::cout << "Enter b: ";
		std::cin >> b;
	}
	else {
		std::cout << "Enter x0: ";
		std::cin >> x0;
	}

	std::cout << "Enter eps: ";
	std::cin >> eps;

	double x;

	if (method == "bisection") {
		x = bisectionMethod(f, a, b, eps);
	}
	else if (method == "chords") {
		x = chordsMethod(f, a, b, eps);
	}
	else if (method == "newtone") {
		x = newtoneMethod(f, df, x0, eps);
	}
	else if (method == "simple iteration") {
		x = simpleIterationMethod(f, x0, eps);
	}
	
	std::cout << "Root is " << x << std::endl;
}