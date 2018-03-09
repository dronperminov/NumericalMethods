#include "root.h"

double bisectionMethod(Fpointer f, double a, double b, double eps) {
	if (b < a)
		std::swap(a, b);

	while (fabs(b - a) > eps) {
		double c = (b + a) / 2; // вычисляем точку в центре

		// вычисляем значения в точках
		double fa = f(a);
		double fb = f(b);
		double fc = f(c);

		if (fa * fc <= 0) {
			b = c;
		}
		else if (fc * fb <= 0) {
			a = c;
		}
	}

	return (a + b) / 2;
}

double chordsMethod(Fpointer f, double a, double b, double eps) {
	if (b < a)
		std::swap(a, b);

	while (fabs(f(b)) > eps) {
		a = b - (b - a) * f(b) / (f(b) - f(a));
		b = a + (b - a) * f(a) / (f(b) - f(a));
	}

	return b;
}

double newtoneMethod(Fpointer f, Fpointer df, double x0, double eps) {
	double x;

	do {
		x = x0;
		x0 -= f(x0) / df(x0);
	} while (fabs(x - x0) > eps);

	return x;
}

double simpleIterationMethod(Fpointer f, double x0, double eps) {
	double x;

	do {
		x = x0;
		x0 = f(x) + x; // заменяем f(x) = 0 -> g(x) = x <-> f(x) + x = x
	} while (fabs(x0 - x) > eps);

	return x;
}
