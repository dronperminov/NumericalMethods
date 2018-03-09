#include "interpolation.h"

using namespace std;

bool comparePoints(const Point &p1, const Point &p2) {
    return p1.x < p2.x;
}

// получение массива точек из файла
vector<Point> getPointsFromFile(const string &path) {
	fstream file;
	file.open(path, ios::in); // открываем файл на чтение

	if (!file)
		throw string("Error during opening file '") + path + "'";
	
	vector<Point> points; // заводим вектор точек
	Point p; // переменная для считывания точки

	// считываем данные из входного файла
	while (file >> p.x >> p.y)
		points.push_back(p); // добавляем считанную точку из файла

	file.close(); // закрываем файл

	sort(points.begin(), points.end(), comparePoints);

	return points;
}

// получение точек с помощью ввода с клавиатуры
std::vector<Point> getPoints() {
	vector<Point> points; // заводим вектор точек
	Point p; // переменная для считывания точки

	// считываем данные из входного файла
	while (cin >> p.x >> p.y)
		points.push_back(p); // добавляем считанную точку из файла

	sort(points.begin(), points.end(), comparePoints);

	return points;
}

// вывод на экран массива точек
void printPoints(std::vector<Point> &points) {
	for (size_t i = 0; i < points.size(); i++)
		printf("X%Lu = %-15lf F%Lu = %-15lf\n", i + 1, points[i].x, i + 1,  points[i].y);
}

/******************************* ЛИНЕЙНАЯ ИНТЕРПОЛЯЦИЯ *******************************/
double linearInterpolation(double x, Point p1, Point p2) {
	return p1.y + (p2.y - p1.y) * (x - p1.x) / (p2.x - p1.x);
}

double linearInterpolation(double x, vector<Point> &points) {
	if (x < points[0].x)
		return linearInterpolation(x, points[0], points[1]);

	if (x > points[points.size() - 1].x)
		return linearInterpolation(x, points[points.size() - 2], points[points.size() - 1]);

	size_t i = 0;
	size_t j = points.size() - 1;

	while (i + 1 < j) {
		size_t k = (i + j) / 2;

		if (x <= points[k].x) {
			j = k;
		}
		else {
			i = k;
		}
	}

	return linearInterpolation(x, points[j - 1], points[j]);
}

/************************** ИНТЕРПОЛЯЦИЯ ПОЛИНОМОМ ЛАГРАНЖА **************************/
double lagrangeInterpolation(double x, vector<Point> &points) {
	double lagrange = 0;

	for (size_t i = 0; i < points.size(); i++) {
		double pol = 1;

		for (size_t j = 0; j < points.size(); j++)
			if (j != i)
				pol *= (x - points[j].x) / (points[i].x - points[j].x);

		lagrange += pol * points[i].y;
	}

	return lagrange;
}

/************************** ИНТЕРПОЛЯЦИЯ ПОЛИНОМОМ НЬЮТОНА ***************************/
double newtoneInterpolation(double x, vector<Point> &points) {
	vector<long double> A = vector<long double>(points.size());

	for (size_t i = 0; i < points.size(); i++) {
		A[i] = 0;

		for (size_t k = 0; k <= i; k++) {
			long double p = points[k].y;

			for (size_t j = 0; j <= i; j++)
				if (j != k)
					p /= (points[k].x - points[j].x);

			A[i] += p;
		}
	}

	double newtone = A[0];
	double denominator = 1;

	for (size_t i = 1; i < points.size(); i++) {
		denominator *= x - points[i - 1].x;
		newtone += A[i] * denominator;
	}

	return newtone;
}

// разностное отношение k-о порядка
double f(int i, int k, vector<Point> points) {
	if (k == 0)
		return points[i].y;

	if (k == 1)
		return (points[i + 1].y - points[i].y) / (points[i + 1].x - points[i].x);

	return (f(i + 1, k - 1, points) - f(i, k - 1, points)) / (points[i + k].x - points[i].x);
}

// интерполяция полиномом Ньютона с помощью разностных отношений
double newtoneInterpolationDiff(double x, vector<Point> &points) {
	double newtone = f(0, 0, points);
	double denominator = 1;

	for (size_t i = 1; i < points.size(); i++) {
		denominator *= x - points[i - 1].x;
		newtone += f(0, i, points) * denominator;
	}

	return newtone;
}

/************************* ИНТЕРПОЛЯЦИЯ КУБИЧЕСКИМ СПЛАЙНОМ **************************/
struct Spline {
	double a, b, c, d, x;
};

double splineInterpolation(double x, vector<Point> points) {
	size_t n = points.size();

	Spline *splines = new Spline[n];

	for (size_t i = 0; i < n; i++)	{
		splines[i].x = points[i].x;
		splines[i].a = points[i].y;
	}
	
	splines[0].c = splines[n - 1].c = 0.0;

	// Решение СЛАУ относительно коэффициентов сплайнов c[i] методом прогонки для трехдиагональных матриц
	// Вычисление прогоночных коэффициентов - прямой ход метода прогонки
	double* alpha = new double[n - 1];
	double* beta = new double[n - 1];

	alpha[0] = beta[0] = 0.0;

	for (size_t i = 1; i < n - 1; i++)	{
		double hi  = points[i].x - points[i - 1].x;
		double hi1 = points[i + 1].x - points[i].x;

		double A = hi;
		double C = 2.0 * (hi + hi1);
		double B = hi1;
		double F = 6.0 * ((points[i + 1].y - points[i].y) / hi1 - (points[i].y - points[i - 1].y) / hi);
		double z = (A * alpha[i - 1] + C);

		alpha[i] = -B / z;
		beta[i] = (F - A * beta[i - 1]) / z;
	}

	// нахождение решения - обратный ход метода прогонки
	for (size_t i = n - 2; i > 0; --i)
		splines[i].c = alpha[i] * splines[i + 1].c + beta[i];

	// по известным коэффициентам c[i] находим значения b[i] и d[i]
	for (size_t i = n - 1; i > 0; i--) {
		double hi = points[i].x - points[i - 1].x;
		splines[i].d = (splines[i].c - splines[i - 1].c) / hi;
		splines[i].b = hi * (2.0 * splines[i].c + splines[i - 1].c) / 6.0 + (points[i].y - points[i - 1].y) / hi;
	}

	size_t index;

	if (x <= splines[0].x) {
		index = 0; // если x меньше точки сетки x[0] - пользуемся первым сплайном
	}
	else if (x >= splines[n - 1].x) {
		index = n - 1; // если x больше точки сетки x[n - 1] - пользуемся последним сплайном
	}
	else { 
		// Иначе x лежит между граничными точками сетки - производим бинарный поиск нужного эл-та массива
		size_t i = 0;
		size_t j = n - 1;

		while (i + 1 < j) {
			size_t k = (i + j) / 2;

			if (x <= splines[k].x) {
				j = k;
			}
			else {
				i = k;
			}
		}

		index = j;
	}

	double dx = x - splines[index].x;

	double y = splines[index].a + splines[index].b * dx + splines[index].c * dx * dx / 2 + splines[index].d * dx * dx * dx / 6;

	delete[] splines;
	delete[] alpha;
	delete[] beta;

	return y;
}