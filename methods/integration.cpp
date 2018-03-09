#include "integration.h"

double squareLeftIntegrate(Fpointer f, double a, double b, int n) {
	double h = (b - a) / n;
	double sum = 0;

	for(int i = 0; i <= n - 1; i++)
		sum += f(a + h * i);

	return sum * h;
}

double squareCenterIntegrate(Fpointer f, double a, double b, int n) {
	double h = (b - a) / n;
	double sum = 0;

	for(int i = 1; i <= n; i++)
		sum += f(a + h * (i - 0.5));

	return sum * h;
}

double squareRightIntegrate(Fpointer f, double a, double b, int n) {
	double h = (b - a) / n;
	double sum = 0;

	for(int i = 1; i <= n; i++)
		sum += f(a + h * i);

	return sum * h;
}


double trapecyIntegrate(Fpointer f, double a, double b, int n) {
	double h = (b - a) / n;
	double sum = 0;

	for (int i = 1; i <= n - 1; i++)
		sum += f(a + h * i);

	return ((f(a) + f(b)) / 2 + sum) * h;
}


double simpsonIntegrate(Fpointer f, double a, double b, int n) {
	double h = (b - a) / n;
	double sum = 0;
	double x = a + h;

	while (x < b) {
		sum += 4 * f(x);
		x += h;
		sum += 2 * f(x);
		x += h;
	}

	return (f(a) + sum - f(b)) * h / 3;
}

/**************************** ИНТЕГРИРОВАНИЕ С ЗАДАННОЙ ТОЧНОСТЬЮ ****************************/
double squareLeftEpsIntegrate(Fpointer f, double a, double b, double eps) {
	long n = 2;

	double h = (b - a) / n;
	double sum = 0, sum1;

	for (int i = 0; i <= n - 1; i++)
		sum += f(a + h * i);
	sum *= h;

	do {
		sum1 = sum;

		h /= 2;
		n *= 2;

		sum = 0;
		for (int i = 0; i <= n - 1; i++)
			sum += f(a + h * i);
		sum *= h;
	} while (fabs(sum - sum1) > eps);

	//std::cout << "Square left iterations: " << n << std::endl;

	return sum;
}

double squareCenterEpsIntegrate(Fpointer f, double a, double b, double eps) {
	long n = 2;

	double h = (b - a) / n;
	double sum = 0, sum1;

	for (int i = 1; i <= n; i++)
		sum += f(a + h * (i - 0.5));
	sum *= h;

	do {
		sum1 = sum;

		h /= 2;
		n *= 2;

		sum = 0;
		for (int i = 1; i <= n; i++)
			sum += f(a + h * (i - 0.5));
		sum *= h;
	} while (fabs(sum - sum1) > eps);

	//std::cout << "Square center iterations: " << n << std::endl;

	return sum;
}

double squareRightEpsIntegrate(Fpointer f, double a, double b, double eps) {
	long n = 2;

	double h = (b - a) / n;
	double sum = 0, sum1;

	for (int i = 1; i <= n; i++)
		sum += f(a + h * i);
	sum *= h;

	do {
		sum1 = sum;

		h /= 2;
		n *= 2;

		sum = 0;
		for (int i = 1; i <= n; i++)
			sum += f(a + h * i);
		sum *= h;
	} while (fabs(sum - sum1) > eps);

	//std::cout << "Square right iterations: " << n << std::endl;

	return sum;
}


double trapecyEpsIntegrate(Fpointer f, double a, double b, double eps) {
	long n = 2;

	double h = (b - a) / n;
	double sum = 0, sum1;

	for (int i = 1; i <= n - 1; i++)
		sum += f(a + h * i);

	sum = ((f(a) + f(b)) / 2 + sum) * h;

	do {
		sum1 = sum;

		h /= 2;
		n *= 2;

		sum = 0;
		for (int i = 1; i <= n - 1; i++)
			sum += f(a + h * i);
		sum = ((f(a) + f(b)) / 2 + sum) * h;
	} while (fabs(sum1 - sum) > eps);

	//std::cout << "Trapecy iterations: " << n << std::endl;

	return sum;
}


double simpsonEpsIntegrate(Fpointer f, double a, double b, double eps) {
	long n = 2;

	double h = (b - a) / n;
	double sum = 0, sum1;
	double x = a + h;

	while (x < b) {
		sum += 4 * f(x);
		x += h;
		sum += 2 * f(x);
		x += h;
	}

	sum = (f(a) + sum - f(b)) * h / 3;

	do {
		sum1 = sum;

		h /= 2;
		n *= 2;

		sum = 0;
		double x = a + h;
		while (x < b) {
			sum += 4 * f(x);
			x += h;
			sum += 2 * f(x);
			x += h;
		}

		sum = (f(a) + sum - f(b)) * h / 3;
	} while (fabs(sum1 - sum) > eps);

	//std::cout << "Simpson iterations: " << n << std::endl;

	return sum;
}