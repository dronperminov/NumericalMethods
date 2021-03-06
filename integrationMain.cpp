#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

#include "methods/integration.h"

double f(double x) {
	return 1 / x;
}

int main() {
	std::string option;
	std::cout << "Welcome to integration application!" << std::endl;
	std::cout << "Enter how would you like to integrate ('precision' / 'count'): ";
	getline(std::cin, option);

	while (option != "precision" && option != "count") {
		std::cout << "Incorrect option. Try again: ";
		getline(std::cin, option);
	}

	std::string method;
	std::cout << "Enter method ('square left' / 'square center' / 'square right' / 'trapecy' / 'simpson' / 'bull' / 'newtone-kotes' / 'gauss' / 'runge kutt 4'): ";
	getline(std::cin, method);

	while (method != "square left" && method != "square center" && method != "square right" && 
		   method != "trapecy" && method != "simpson" && method != "bull" && 
		   method != "newtone-kotes" && method != "gauss" && method != "runge kutt 4") {
		std::cout << "Incorrect option. Try again: ";
		getline(std::cin, method);
	}

	double a, b;

	std::cout << "Enter a: ";
	std::cin >> a;
	std::cout << "Enter b: ";
	std::cin >> b;

	double eps, I;
	int n;

	if (option == "precision") {
		std::cout << "Enter eps: ";
		std::cin >> eps;

		if (method == "square left") {
			I = squareLeftEpsIntegrate(f, a, b, eps);
		}
		else if (method == "square center") {
			I = squareCenterEpsIntegrate(f, a, b, eps);
		}
		else if (method == "square right") {
			I = squareRightEpsIntegrate(f, a, b, eps);
		}
		else if (method == "trapecy") {
			I = trapecyEpsIntegrate(f, a, b, eps);
		}
		else if (method == "simpson") {
			I = simpsonEpsIntegrate(f, a, b, eps);
		}
		else if (method == "bull") {
			I = bullEpsIntegrate(f, a, b, eps);
		}
		else if (method == "newtone-kotes") {
			int power;
			std::cout << "Enter power (0 <= power < 10): ";
			std::cin >> power;

			I = newtoneKotesEpsIntegrate(f, a, b, eps, power);
		}
		else if (method == "gauss") {
			I = gaussEpsIntegrate(f, a, b, eps);
		}
		else if (method == "runge kutt 4") {
			I = rungeKutt4EpsIntegrate(f, a, b, eps);
		}
	}
	else {
		std::cout << "Enter n: ";
		std::cin >> n;	

		if (method == "square left") {
			I = squareLeftIntegrate(f, a, b, n);
		}
		else if (method == "square center") {
			I = squareCenterIntegrate(f, a, b, n);
		}
		else if (method == "square right") {
			I = squareRightIntegrate(f, a, b, n);
		}
		else if (method == "trapecy") {
			I = trapecyIntegrate(f, a, b, n);
		}
		else if (method == "simpson") {
			I = simpsonIntegrate(f, a, b, n);
		}
		else if (method == "bull") {
			I = bullIntegrate(f, a, b, n);
		}
		else if (method == "newtone-kotes") {
			int power;
			std::cout << "Enter power (0 <= power < 10): ";
			std::cin >> power;

			I = newtoneKotesIntegrate(f, a, b, n, power);
		}
		else if (method == "gauss") {
			I = gaussIntegrate(f, a, b, n);
		}
		else if (method == "runge kutt 4") {
			I = rungeKutt4Integrate(f, a, b, n);
		}
	}

	std::cout << "Integrate = " << std::setprecision(15) << I << std::endl;
}