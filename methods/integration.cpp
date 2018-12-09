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

double rungeKutt4Integrate(Fpointer f, double a, double b, int n) {
	double h = (b - a) / n;

	double x0 = a; // начальные условия
	double y0 = 0; // задачи Коши

	double x; // текущие значения
	double y; // решения задачи Коши

	// находим интегральную кривую
	for (int i = 1; i < n; i++) {
		x = x0 + h; // определяем новый x

		// считаем коэффициенты метода Рунге-Кутты
		double k1 = f(x0);
		double k2 = f(x0 + h / 2);
		double k3 = f(x0 + h / 2);
		double k4 = f(x0 + h);

		// находим новое значение y
		y = y0 + h * (k1 + 2 * k2 + 2 * k3 + k4) / 6;

		// сдвигаем начальную точку
		x0 = x;
		y0 = y;
	}

	return y;
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