#pragma once

#include <iostream>
#include <cmath>

// Интегрирование с заданным количеством узлов
double squareLeftIntegrate(double (*f)(double), double a, double b, int n); // методом левых прямоугольников
double squareCenterIntegrate(double (*f)(double), double a, double b, int n); // методом центральных прямоугольников
double squareRightIntegrate(double (*f)(double), double a, double b, int n); // методом правых прямоугольников

double trapecyIntegrate(double (*f)(double), double a, double b, int n); // методом трапеций

double simpsonIntegrate(double (*f)(double), double a, double b, int n); // методом Симпсона (парабол)

double bullIntegrate(double (*f)(double), double a, double b, int n); // методом Буля

double gaussIntegrate(double (*f)(double), double a, double b, int n); // метод Гаусса для 3 точек

double newtoneKotesIntegrate(double (*f)(double), double a, double b, int n, int power); // метод Ньютона-Котеса (0 <= power < 10)

double rungeKutt4Integrate(double (*f)(double), double a, double b, int n); // методом Рунге-Кутты 4-го порядка

// Интегрирование с заданной точностью
double squareLeftEpsIntegrate(double (*f)(double), double a, double b, double eps); // методом левых прямоугольников
double squareCenterEpsIntegrate(double (*f)(double), double a, double b, double eps); // методом центральных прямоугольников
double squareRightEpsIntegrate(double (*f)(double), double a, double b, double eps); // методом правых прямоугольников

double trapecyEpsIntegrate(double (*f)(double), double a, double b, double eps); // методом трапеций

double simpsonEpsIntegrate(double (*f)(double), double a, double b, double eps); // методом Симпсона (парабол)

double bullEpsIntegrate(double (*f)(double), double a, double b, double eps); // методом Буля

double newtoneKotesEpsIntegrate(double (*f)(double), double a, double b, double eps, int power); // метод Ньютона-Котеса (0 <= power < 10)

double gaussEpsIntegrate(double (*f)(double), double a, double b, double eps); // метод Гаусса для 3 точек

double rungeKutt4EpsIntegrate(double (*f)(double), double a, double b, double eps); // методом Рунге-Кутты 4-го порядка