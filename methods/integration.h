#pragma once

#include <iostream>
#include <cmath>

typedef double (*Fpointer)(double); // указатель на функцию для интегрирования

// Интегрирование с заданным количеством узлов
double squareLeftIntegrate(Fpointer f, double a, double b, int n); // методом левых прямоугольников
double squareCenterIntegrate(Fpointer f, double a, double b, int n); // методом центральных прямоугольников
double squareRightIntegrate(Fpointer f, double a, double b, int n); // методом правых прямоугольников

double trapecyIntegrate(Fpointer f, double a, double b, int n); // методом трапеций

double simpsonIntegrate(Fpointer f, double a, double b, int n); // методом Симпсона (парабол)

double rungeKutt4Integrate(Fpointer f, double a, double b, int n); // методом Рунге-Кутты 4-го порядка

// Интегрирование с заданной точностью
double squareLeftEpsIntegrate(Fpointer f, double a, double b, double eps); // методом левых прямоугольников
double squareCenterEpsIntegrate(Fpointer f, double a, double b, double eps); // методом центральных прямоугольников
double squareRightEpsIntegrate(Fpointer f, double a, double b, double eps); // методом правых прямоугольников

double trapecyEpsIntegrate(Fpointer f, double a, double b, double eps); // методом трапеций

double simpsonEpsIntegrate(Fpointer f, double a, double b, double eps); // методом Симпсона (парабол)