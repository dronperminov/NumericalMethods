#pragma once

#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

// структура точки на координатной плоскости
struct Point {
	double x;
	double y;
};

// получение массива точек из файла
std::vector<Point> getPointsFromFile(const std::string &path);
// получение точек с помощью ввода с клавиатуры
std::vector<Point> getPoints();

// вывод на экран массива точек
void printPoints(std::vector<Point> &points);

// линейная интерполяция
double linearInterpolation(double x, Point p1, Point p2); // для двух точек
double linearInterpolation(double x, std::vector<Point> &points);

// интерполяция полиномом Лагранжа
double lagrangeInterpolation(double x, std::vector<Point> &points);

// интерполяция полиномом Ньютона
double newtoneInterpolation(double x, std::vector<Point> &points);
double newtoneInterpolationDiff(double x, std::vector<Point> &points); // с помощью разностных отношений

// интерполяция кубическим сплайном
double splineInterpolation(double x, std::vector<Point> points);