#include "integration.h"

// метод левых прямоугольников
double squareLeftIntegrate(double (*f)(double), double a, double b, int n) {
	double h = (b - a) / n; // шаг интегрирования
	double sum = 0;

	// находим сумму по формуле левых прямоугольников
	for(int i = 0; i <= n - 1; i++)
		sum += f(a + i * h);

	return sum * h; // возвращаем найденное значение интеграла
}

// метод центральных прямоугольников
double squareCenterIntegrate(double (*f)(double), double a, double b, int n) {
	double h = (b - a) / n; // шаг интегрирования
	double sum = 0;

	// находим сумму по формуле центральных прямоугольников
	for(int i = 1; i <= n; i++)
		sum += f(a + (i - 0.5) * h);

	return sum * h; // возвращаем найденное значение интеграла
}

// метод правых прямоугольников
double squareRightIntegrate(double (*f)(double), double a, double b, int n) {
	double h = (b - a) / n; // шаг интегрирования
	double sum = 0;

	// находим сумму по формуле правых прямоугольников
	for(int i = 1; i <= n; i++)
		sum += f(a + i * h);

	return sum * h; // возвращаем найденное значение интеграла
}

// метод трапеций
double trapecyIntegrate(double (*f)(double), double a, double b, int n) {
	double h = (b - a) / n; // шаг интегрирования
	double sum = (f(a) + f(b)) / 2;

	// находим сумму по формуле трапеций
	for (int i = 1; i <= n - 1; i++)
		sum += f(a + i * h);

	return sum * h; // возвращаем найденное значение интеграла
}

// метод Симпсона (парабол)
double simpsonIntegrate(double (*f)(double), double a, double b, int n) {
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
double bullIntegrate(double (*f)(double), double a, double b, int n) {
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

// метод Ньютона - Котеса, полином степени power (0 <= power < 10)
double newtoneKotesIntegrate(double (*f)(double), double a, double b, int n, int power) {
	// коэффициенты метода Ньютона-Котеса
	int coef[10][10] = {
		{     1,     0,     0,     0,     0,     0,     0,     0,     0,     0 },
		{     1,     1,     0,     0,     0,     0,     0,     0,     0,     0 },
		{     1,     4,     1,     0,     0,     0,     0,     0,     0,     0 },
		{     1,     3,     3,     1,     0,     0,     0,     0,     0,     0 },
		{     7,    32,    12,    32,     7,     0,     0,     0,     0,     0 },
		{    19,    75,    50,    50,    75,    19,     0,     0,     0,     0 },
		{    41,   216,    27,   272,    27,   216,    41,     0,     0,     0 },
		{   751,  3577,  1323,  2989,  2989,  1323,  3577,   751,     0,     0 },
		{   989,  5888,  -928, 10496, -4540, 10496,  -928,  5888,   989,     0 },
		{  2857, 15741,  1080, 19344,  5778,  5778, 19344,  1080, 15741,  2857 }
	};

	// нормирующие коэффициенты метода Ньютона-Котеса
	double norm[] = {
		1.0, 1.0 / 2, 1.0 / 3, 3.0 / 8, 2.0 / 45, 5.0 / 288, 1.0 / 140, 7.0 / 17280, 4.0 / 14175, 9.0 / 89600
	};

	int step = power > 0 ? power : 1; // шаг изменения кординаты на отрезке [a, b]
	double h = (b - a) / (n * step); // шаг интегрирования
	double sum = 0;

	for (int i = 0; i < n; i++) {
		double s = 0;

		// считыаем частичную сумму
		for (int j = 0; j <= power; j++)
			s += coef[power][j] * f(a + (i * step + j) * h);

		sum += norm[power] * s * h; // прибавляем к сумме, умноженной на шаг и нормирующий коэффициент
	}

	return sum; // возвращаем найденное значение интеграла
}

// метод Гаусса для 3 точек
double gaussIntegrate(double (*f)(double), double a, double b, int n) {
	const double Xi[3] = { -sqrt(0.6), 0, sqrt(0.6) }; // узлы интегрирования
	const double Ci[3] = { 5.0 / 9, 8.0 / 9, 5.0 / 9 }; // веса интегрирования

	double h = (b - a) / n; // шаг интегрирования
	double sum = 0;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < 3; j++)
			sum += Ci[j] * f(a + (2 * i + 1 + Xi[j]) * h / 2);

	return sum * h / 2; // возвращаем найденное значение интеграла
}

// метод Рунге-Кутты 4-го порядка
double rungeKutt4Integrate(double (*f)(double), double a, double b, int n) {
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
double squareLeftEpsIntegrate(double (*f)(double), double a, double b, double eps) {
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
double squareCenterEpsIntegrate(double (*f)(double), double a, double b, double eps) {
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
double squareRightEpsIntegrate(double (*f)(double), double a, double b, double eps) {
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
double trapecyEpsIntegrate(double (*f)(double), double a, double b, double eps) {
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
double simpsonEpsIntegrate(double (*f)(double), double a, double b, double eps) {
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
double bullEpsIntegrate(double (*f)(double), double a, double b, double eps) {
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

// метод Ньютона - Котеса, полином степени power (0 <= power < 10)
double newtoneKotesEpsIntegrate(double (*f)(double), double a, double b, double eps, int power) {
	// коэффициенты метода Ньютона-Котеса
	int coef[10][10] = {
		{     1,     0,     0,     0,     0,     0,     0,     0,     0,     0 },
		{     1,     1,     0,     0,     0,     0,     0,     0,     0,     0 },
		{     1,     4,     1,     0,     0,     0,     0,     0,     0,     0 },
		{     1,     3,     3,     1,     0,     0,     0,     0,     0,     0 },
		{     7,    32,    12,    32,     7,     0,     0,     0,     0,     0 },
		{    19,    75,    50,    50,    75,    19,     0,     0,     0,     0 },
		{    41,   216,    27,   272,    27,   216,    41,     0,     0,     0 },
		{   751,  3577,  1323,  2989,  2989,  1323,  3577,   751,     0,     0 },
		{   989,  5888,  -928, 10496, -4540, 10496,  -928,  5888,   989,     0 },
		{  2857, 15741,  1080, 19344,  5778,  5778, 19344,  1080, 15741,  2857 }
	};

	// нормирующие коэффициенты метода Ньютона-Котеса
	double norm[] = {
		1.0, 1.0 / 2, 1.0 / 3, 3.0 / 8, 2.0 / 45, 5.0 / 288, 1.0 / 140, 7.0 / 17280, 4.0 / 14175, 9.0 / 89600
	};

	long n = 2; // начальное число разбиений
	int step = power > 0 ? power : 1; // шаг изменения кординаты на отрезке [a, b]
	double h = (b - a) / (n * step); // шаг интегрирования
	double sum = 0;
	double sum1;

	for (int i = 0; i < n; i++) {
		double s = 0;

		// считыаем частичную сумму
		for (int j = 0; j <= power; j++)
			s += coef[power][j] * f(a + (i * step + j) * h);

		sum += norm[power] * s * h; // прибавляем к сумме, умноженной на шаг и нормирующий коэффициент
	}

	do {
		sum1 = sum; // обновляем старое значение суммы
		sum = 0; // сбрасываем текущее

		h /= 2; // дробим шаг в два раза
		n *= 2; // увеличиваем число интервалов в два раза

		for (int i = 0; i < n; i++) {
			double s = 0;

			// считыаем частичную сумму
			for (int j = 0; j <= power; j++)
				s += coef[power][j] * f(a + (i * step + j) * h);

			sum += norm[power] * s * h; // прибавляем к сумме, умноженной на шаг и нормирующий коэффициент
		}
	} while (fabs(sum1 - sum) > eps); // повторяем, пока не достигнем нужной точности

	return sum;
}

// метод Гаусса для 3 точек
double gaussEpsIntegrate(double (*f)(double), double a, double b, double eps) {
	const double Xi[3] = { -sqrt(0.6), 0, sqrt(0.6) }; // узлы интегрирования
	const double Ci[3] = { 5.0 / 9, 8.0 / 9, 5.0 / 9 }; // веса интегрирования

	long n = 2; // начальное число разбиений

	double h = (b - a) / n; // шаг интегрирования
	double sum = 0;
	double sum1;

	// вычисялем значение интеграла
	for (int i = 0; i < n; i++)
		for (int j = 0; j < 3; j++)
			sum += Ci[j] * f(a + (2 * i + 1 + Xi[j]) * h / 2);

	sum *= h / 2;

	do {
		sum1 = sum; // обновляем старое значение суммы
		sum = 0; // сбрасываем текущее

		h /= 2; // дробим шаг в два раза
		n *= 2; // увеличиваем число интервалов в два раза

		// считаем более точное значение интеграла
		for (int i = 0; i < n; i++)
			for (int j = 0; j < 3; j++)
				sum += Ci[j] * f(a + (2 * i + 1 + Xi[j]) * h / 2);

		sum *= h / 2;
	} while (fabs(sum - sum1) > eps); // повторяем, пока не достигнем нужной точности

	return sum; // возвращаем найденное значение интеграла
}

// метод Рунге-Кутты 4-го порядка
double rungeKutt4EpsIntegrate(double (*f)(double), double a, double b, double eps) {
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