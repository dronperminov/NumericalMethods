#include "optimization.h"

/*************************** МЕТОДЫ ОДНОМЕРНОй ОПТИМИЗАЦИИ ***************************/
// линейный поиск (использовать только в крайнем случае)
double linearExtremum(Fpointer f, double a, double b, double eps) {
	double x0 = a;
	double y0 = f(a);

	for (double x = a + eps; x <= b; x+=eps) {
		double y = f(x);

		// для поиска максимума поменять на y > y0
		if (y < y0) {
			y0 = y;
			x0 = x;
		}
	}

	return x0;
}

// метод деления отрезка пополам
double dichotomyExtremum(Fpointer f, double a, double b, double eps) {
	do {
		double x = (a + b) / 2;
		double y1 = f(x - eps);
		double y2 = f(x + eps);

		// для поиска максимума поменять на y1 <= y2
		if (y1 >= y2) {
			a = x;
		}
		else {
			b = x;
		}
	} while (fabs(b - a) > eps);

	return (a + b) / 2;
}

// метод золотого сечения поиска экстремума функции
double goldenSectionExtremum(Fpointer f, double a, double b, double eps) {
	do {
		double x1 = b - (b - a) / phi;
		double x2 = a + (b - a) / phi;

		double y1 = f(x1);
		double y2 = f(x2);

		// для поиска максимума поменять на y1 <= y2
		if (y1 >= y2) {
			a = x1;
		}
		else {
			b = x2;
		}
	} while (fabs(b - a) > eps);

	return (a + b) / 2;
}

/*************************** МЕТОДЫ МНОГОМЕРНОй ОПТИМИЗАЦИИ **************************/
// метод покоординатного спуска
double* coordinateDescentExtremum(FNpointer f, int n, double a, double b, double eps) {
	double *X0 = new double[n];
	double *X = new double[n];
	double *Xa = new double[n];
	double *Xb = new double[n];

	double norm;

	for (int i = 0; i < n; i++) {
		X[i] = 0;
		Xa[i] = a;
		Xb[i] = b;
	}

	do {
		for (int i = 0; i < n; i++) {
			X0[i] = X[i];

			do {
				double mid = (Xa[i] + Xb[i]) / 2;

				X[i] = mid - eps;
				double y1 = f(X);
				X[i] = mid + eps;
				double y2 = f(X);

				if (y1 >= y2) {
					Xa[i] = mid;
				}
				else {
					Xb[i] = mid;
				}
			} while (fabs(Xb[i] - Xa[i]) > eps);

			norm = 0;
		}

		norm = 0;

		for (int i = 0; i < n; i++) {
			if (fabs(X[i] - X0[i]) > norm)
				norm = fabs(X[i] - X0[i]);
		}
	} while (norm > eps);

	delete[] Xa;
	delete[] Xb;
	delete[] X0;

	return X;
}

// метод градиентного спуска
double* gradientDescentExtremum(FNpointer f, int n, double lambda, double eps) {
	double *X = new double[n];
	double *X0 = new double[n];

	double norm;

	for (int i = 0; i < n; i++)
		X0[i] = 0;

	do {
		norm = 0;

		for (int i = 0; i < n; i++) {
			X[i] = X0[i] + eps / 2;
			double f1 = f(X);
			X[i] = X0[i] - eps / 2;
			double f2 = f(X);
			X[i] = X0[i];

			double grad = (f1 - f2) / eps; // вычисляем градиент функции

			X0[i] = X[i] - lambda * grad; // делаем шаг метода

			if (fabs(X[i] - X0[i]) > norm)
				norm = fabs(X[i] - X0[i]);
		}
	} while (norm > eps);

	delete[] X0;

	return X;
}