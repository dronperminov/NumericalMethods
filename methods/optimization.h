#pragma once

#include <iostream>
#include <cmath>

typedef double (*Fpointer)(double x); // указатель на функцию одной переменной
typedef double (*FNpointer)(double *X); // указатель на функцию многих переменных

const double phi = (1 + sqrt(5)) / 2; // значение золотого сечения

// методы одномерной оптимизации - поиск экстремума на [a, b]
double linearExtremum(Fpointer f, double a, double b, double eps);
double dichotomyExtremum(Fpointer f, double a, double b, double eps);
double goldenSectionExtremum(Fpointer f, double a, double b, double eps);

// методы многомерной оптимизации
double* coordinateDescentExtremum(FNpointer f, int n, double a, double b, double eps);
double* gradientDescentExtremum(FNpointer f, int n, double lambda, double eps);