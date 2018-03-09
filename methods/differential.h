#pragma once

#include <iostream>
#include <vector>
#include <cmath>

typedef double (*Fpointer)(double x, double y); // указатель на функцию двух переменных f(x, y)

struct Point {
	double x;
	double y;
};

std::vector<Point> eulerMethod(Fpointer f, double a, double b, double h, double y0); // метод Эйлера
std::vector<Point> eulerAdvancedMethod(Fpointer f, double a, double b, double h, double y0); // модифицированный метод Эйлера
std::vector<Point> rungeKutt3Method(Fpointer f, double a, double b, double h, double y0); // метод Рунге-Кутты 3-го порядка
std::vector<Point> rungeKutt4Method(Fpointer f, double a, double b, double h, double y0); // метод Рунге-Кутты 4-го порядка