#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>

typedef struct Matrix {
	size_t rows; // число строк
	size_t cols; // число столбцов

	double **values; // значения элементов
} Matrix;

typedef struct Vector {
	size_t size;
	double *values;
} Vector;

Matrix initMatrix(size_t rows, size_t cols);
Matrix initMatrix(std::fstream &f);
Matrix copyMatrix(const Matrix &matrix);

void readMatrix(Matrix &matrix);
void printMatrix(Matrix matrix);
void deleteMatrix(Matrix &matrix);

double determinantMatrix(const Matrix& matrix);
size_t rankMatrix(const Matrix& matrix);

Matrix solveGauss(const Matrix& A, const Matrix& B);

Vector initVector(size_t size);
void deleteVector(Vector &vector);