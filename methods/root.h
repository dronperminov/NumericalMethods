#pragma once

#include <iostream>
#include <cmath>

typedef double (*Fpointer)(double); // указатель на функцию

// метод деления отрезка пополам
double bisectionMethod(Fpointer f, double a, double b, double eps);
// метод хорд
double chordsMethod(Fpointer f, double a, double b, double eps);
// метод Ньютона
double newtoneMethod(Fpointer f, Fpointer df, double x0, double eps);
// метод простой итерации
double simpleIterationMethod(Fpointer f, double x0, double eps);