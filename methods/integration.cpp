#include "integration.h"

// метод левых прямоугольников
double squareLeftIntegrate(Fpointer f, double a, double b, int n) {
	double h = (b - a) / n; // шаг интегрирования
	double sum = 0;

	// находим сумму по формуле левых прямоугольников
	for(int i = 0; i <= n - 1; i++)
		sum += f(a + i * h);

	return sum * h; // возвращаем найденное значение интеграла
}

// метод центральных прямоугольников
double squareCenterIntegrate(Fpointer f, double a, double b, int n) {
	double h = (b - a) / n; // шаг интегрирования
	double sum = 0;

	// находим сумму по формуле центральных прямоугольников
	for(int i = 1; i <= n; i++)
		sum += f(a + (i - 0.5) * h);

	return sum * h; // возвращаем найденное значение интеграла
}

// метод правых прямоугольников
double squareRightIntegrate(Fpointer f, double a, double b, int n) {
	double h = (b - a) / n; // шаг интегрирования
	double sum = 0;

	// находим сумму по формуле правых прямоугольников
	for(int i = 1; i <= n; i++)
		sum += f(a + i * h);

	return sum * h; // возвращаем найденное значение интеграла
}

// метод трапеций
double trapecyIntegrate(Fpointer f, double a, double b, int n) {
	double h = (b - a) / n; // шаг интегрирования
	double sum = (f(a) + f(b)) / 2;

	// находим сумму по формуле трапеций
	for (int i = 1; i <= n - 1; i++)
		sum += f(a + i * h);

	return sum * h; // возвращаем найденное значение интеграла
}

// метод Симпсона (парабол)
double simpsonIntegrate(Fpointer f, double a, double b, int n) {
	if (n % 2 != 0)
		throw "n must be even";

	double h = (b - a) / n; // шаг интегрирования
	double sum = f(a) + f(b);
	
	for (int i = 1; i <= n / 2; i++)
		sum += 4 * f(a + (2 * i - 1) * h);

	for (int i = 1; i < n / 2; i++)
		sum += 2 * f(a + 2 * i * h);

	return sum * h / 3; // возвращаем найденное значение интеграла
}

// метод Буля
double bullIntegrate(Fpointer f, double a, double b, int n) {
	if (n % 4 != 0)
		throw "n must be a multiple of 4";

	double h = (b - a) / n; // шаг интегрирования
	double sum = 7 * (f(a) 	+ f(b));

	for (int i = 1; i < n / 4; i++)
		sum += 14 * f(a + 4 * i * h);

	for (int i = 1; i <= n / 2; i++)
		sum += 32 * f(a + (2 * i - 1) * h);

	for (int i = 1; i <= n / 4; i++)
		sum += 12 * f(a + (4 * i - 2) * h);

	return sum * 4 * h / 90;
}

// метод Рунге-Кутты 4-го порядка
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
// метод левых прямоугольников
double squareLeftEpsIntegrate(Fpointer f, double a, double b, double eps) {
	long n = 2; // начальное число разбиений

	double h = (b - a) / n; // шаг интегрирования
	double sum = 0, sum1;

	// вычисляем значение интеграла для n = 2
	for (int i = 0; i <= n - 1; i++)
		sum += f(a + i * h);

	sum *= h;

	do {
		sum1 = sum; // обновляем старое значение суммы
		sum = 0; // сбрасываем текущее

		h /= 2; // дробим шаг в два раза
		n *= 2; // увеличиваем число интервалов в два раза

		// считаем более точное значение интеграла
		for (int i = 0; i <= n - 1; i++)
			sum += f(a + i * h);

		sum *= h;
	} while (fabs(sum - sum1) > eps); // повторяем, пока не достигнем нужной точности

	return sum; // возвращаем найденное значение интеграла
}

// метод центральных прямоугольников
double squareCenterEpsIntegrate(Fpointer f, double a, double b, double eps) {
	long n = 2; // начальное число разбиений

	double h = (b - a) / n; // шаг интегрирования
	double sum = 0, sum1;

	// вычисляем значение интеграла для n = 2
	for (int i = 1; i <= n; i++)
		sum += f(a + h * (i - 0.5));

	sum *= h;

	do {
		sum1 = sum; // обновляем старое значение суммы
		sum = 0; // сбрасываем текущее

		h /= 2; // дробим шаг в два раза
		n *= 2; // увеличиваем число интервалов в два раза

		// считаем более точное значение интеграла
		for (int i = 1; i <= n; i++)
			sum += f(a + (i - 0.5) * h);

		sum *= h;
	} while (fabs(sum - sum1) > eps); // повторяем, пока не достигнем нужной точности

	return sum; // возвращаем найденное значение интеграла
}

// метод правых прямоугольников
double squareRightEpsIntegrate(Fpointer f, double a, double b, double eps) {
	long n = 2; // начальное число разбиений

	double h = (b - a) / n; // шаг интегрирования
	double sum = 0, sum1;

	// вычисляем значение интеграла для n = 2
	for (int i = 1; i <= n; i++)
		sum += f(a + i * h);

	sum *= h;

	do {
		sum1 = sum; // обновляем старое значение суммы
		sum = 0; // сбрасываем текущее

		h /= 2; // дробим шаг в два раза
		n *= 2; // увеличиваем число интервалов в два раза

		// считаем более точное значение интеграла
		for (int i = 1; i <= n; i++)
			sum += f(a + i * h);

		sum *= h;
	} while (fabs(sum - sum1) > eps); // повторяем, пока не достигнем нужной точности

	return sum; // возвращаем найденное значение интеграла
}

// метод трапеций
double trapecyEpsIntegrate(Fpointer f, double a, double b, double eps) {
	long n = 2;

	double h = (b - a) / n;
	double sum = 0, sum1;

	for (int i = 1; i <= n - 1; i++)
		sum += f(a + i * h);

	sum = ((f(a) + f(b)) / 2 + sum) * h;

	do {
		sum1 = sum;
		sum = 0;

		h /= 2;
		n *= 2;

		for (int i = 1; i <= n - 1; i++)
			sum += f(a + i * h);

		sum = ((f(a) + f(b)) / 2 + sum) * h;
	} while (fabs(sum1 - sum) > eps);

	return sum;
}

// метод Симпсона (парабол)
double simpsonEpsIntegrate(Fpointer f, double a, double b, double eps) {
	long n = 2; // начальное число разбиений

	double h = (b - a) / n; // шаг интегрирования
	double sum = 0, sum1;
	
	// вычисляем значение интеграла для n = 2
	for (int i = 1; i <= n / 2; i++)
		sum += 4 * f(a + (2 * i - 1) * h);

	for (int i = 1; i < n / 2; i++)
		sum += 2 * f(a + 2 * i * h);

	sum = (f(a) + sum + f(b)) * h / 3;

	do {
		sum1 = sum; // обновляем старое значение суммы
		sum = 0; // сбрасываем текущее

		h /= 2; // дробим шаг в два раза
		n *= 2; // увеличиваем число интервалов в два раза

		// считаем более точное значение интеграла
		for (int i = 1; i <= n / 2; i++)
			sum += 4 * f(a + (2 * i - 1) * h);

		for (int i = 1; i < n / 2; i++)
			sum += 2 * f(a + 2 * i * h);

		sum = (f(a) + sum + f(b)) * h / 3;
	} while (fabs(sum1 - sum) > eps); // повторяем, пока не достигнем нужной точности

	return sum; // возвращаем найденное значение интеграла
}

// метод Буля
double bullEpsIntegrate(Fpointer f, double a, double b, double eps) {
	long n = 4; // начальное число разбиений
	
	double h = (b - a) / n; // шаг интегрирования
	double sum = 7 * (f(a) + f(b));
	double sum1;

	for (int i = 1; i < n / 4; i++)
		sum += 14 * f(a + 4 * i * h);

	for (int i = 1; i <= n / 2; i++)
		sum += 32 * f(a + (2 * i - 1) * h);

	for (int i = 1; i <= n / 4; i++)
		sum += 12 * f(a + (4 * i - 2) * h);

	sum *= 4 * h / 90;

	do {
		sum1 = sum; // обновляем старое значение суммы
		sum = 7 * (f(a) + f(b)); // сбрасываем текущее

		h /= 4; // дробим шаг в четыре раза
		n *= 4; // увеличиваем число интервалов в четыре раза

		// считаем более точное значение интеграла
		for (int i = 1; i < n / 4; i++)
			sum += 14 * f(a + 4 * i * h);

		for (int i = 1; i <= n / 2; i++)
			sum += 32 * f(a + (2 * i - 1) * h);

		for (int i = 1; i <= n / 4; i++)
			sum += 12 * f(a + (4 * i - 2) * h);

		sum *= 4 * h / 90;
	} while (fabs(sum1 - sum) > eps); // повторяем, пока не достигнем нужной точности

	return sum; // возвращаем найденное значение интеграла
}

// метод Рунге-Кутты 4-го порядка
double rungeKutt4EpsIntegrate(Fpointer f, double a, double b, double eps) {
	long n = 2; // начальное число разбиений

	double h = (b - a) / n; // шаг интегрирования

	double x0 = a; // начальные условия
	double y0 = 0; // задачи Коши

	double x; // текущие значения
	double y; // решения задачи Коши
	double y1;

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

	do {
		y1 = y;

		// сбрасываем начальные условия
		x0 = a;
		y0 = 0;

		h /= 2; // дробим шаг в два раза
		n *= 2; // увеличиваем число интервалов в два раза

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
	} while (fabs(y - y1) > eps); // повторяем, пока не достигнем нужной точности

	return y; // возвращаем найденное значение интеграла
}