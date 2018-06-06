#include "matrix.h"

Matrix initMatrix(size_t rows, size_t cols) {
	Matrix matrix;

	matrix.rows = rows;
	matrix.cols = cols;
	matrix.values = new double*[rows];

	for (size_t i = 0; i < matrix.rows; i++) {
		matrix.values[i] = new double[matrix.cols];

		for (size_t j = 0; j < matrix.cols; j++)
			matrix.values[i][j] = 0;
	}

	return matrix;
}

Matrix initMatrix(std::fstream &f) {
	Matrix matrix;

	f >> matrix.rows >> matrix.cols;

	matrix.values = new double*[matrix.rows];

	for (size_t i = 0; i < matrix.rows; i++) {
		matrix.values[i] = new double[matrix.cols];

		for (size_t j = 0; j < matrix.cols; j++)
			f >> matrix.values[i][j];
	}

	return matrix;
}

Matrix copyMatrix(const Matrix &matrix) {
	Matrix copy;

	copy.rows = matrix.rows;
	copy.cols = matrix.cols;
	copy.values = new double*[matrix.rows];

	for (size_t i = 0; i < matrix.rows; i++) {
		copy.values[i] = new double[matrix.cols];

		for (size_t j = 0; j < matrix.cols; j++)
			copy.values[i][j] = matrix.values[i][j];
	}

	return copy;
}

void readMatrix(Matrix &matrix) {
	for (size_t i = 0; i < matrix.rows; i++) {
		std::cout << "Enter row: ";

		for (size_t j = 0; j < matrix.cols; j++)
			std::cin >> matrix.values[i][j];
	}
}

void printMatrix(Matrix matrix) {
	for (size_t i = 0; i < matrix.rows; i++) {
		for (size_t j = 0; j < matrix.cols; j++)
			std::cout << std::setw(7) << matrix.values[i][j];

		std::cout << std::endl;
	}
}

void deleteMatrix(Matrix &matrix) {
	if (matrix.rows == 0)
		return;

	for (size_t i = 0; i < matrix.rows; i++)
		delete[] matrix.values[i];

	delete[] matrix.values;

	matrix.rows = 0;
	matrix.cols = 0;
	matrix.values = NULL;
}

double determinantMatrix(const Matrix &matrix) {
	if (matrix.rows != matrix.cols)
		throw "determimant: matrix mast be square";

	Matrix copy = copyMatrix(matrix);
	double det = 1;
	size_t n = matrix.rows;

	for (size_t j = 0; j < n; j++) {
		if (copy.values[j][j] == 0) {
			size_t rowNum = j;

			while (rowNum < n && copy.values[rowNum][j] == 0)
				rowNum++;

			if (rowNum == n) {
				deleteMatrix(copy);
				return 0;
			}

			double *tmp = copy.values[rowNum];
			copy.values[rowNum] = copy.values[j];
			copy.values[j] = tmp;

			det *= -1;
		}

		det *= copy.values[j][j];

		for (size_t i = j + 1; i < n; i++) {
			double elem = copy.values[i][j] / copy.values[j][j];

			for (size_t k = 0; k < n; k++)
				copy.values[i][k] -= copy.values[j][k] * elem;
		}
	}

	deleteMatrix(copy);

	return det;
}

size_t rankMatrix(const Matrix& matrix) {
	Matrix copy = copyMatrix(matrix);
	size_t n = copy.rows > copy.cols ? copy.cols : copy.rows;

	for (size_t j = 0; j < n; j++) {
		size_t rowNum = j;

		while (rowNum < copy.rows && copy.values[rowNum][j] == 0)
			rowNum++;

		if (rowNum != copy.rows) {
			double *tmp = copy.values[rowNum];
			copy.values[rowNum] = copy.values[j];
			copy.values[j] = tmp;

			for (size_t i = j + 1; i < copy.rows; i++) {
				double elem = copy.values[i][j] / copy.values[j][j];

			 	for (size_t k = 0; k < n; k++)
					copy.values[i][k] -= copy.values[j][k] * elem;
			}
		}
	}

	size_t rank = 0;

	for (size_t i = 0; i < copy.rows; i++) {
		size_t j = 0;

		while (j < copy.cols && copy.values[i][j] == 0)
			j++;

		if (j < copy.cols)
			rank++;
	}

	deleteMatrix(copy);

	return rank ? rank : 1;
}

Matrix solveGauss(const Matrix& a, const Matrix& b) {
	if (a.rows != a.cols || a.rows != b.rows)
		throw "solveGauss: incorrect sizes";

	Matrix A = copyMatrix(a);
	Matrix B = copyMatrix(b);
	size_t n = a.rows;

	// derect step
	for (size_t j = 0; j < n; j++) {
        if (A.values[j][j] == 0) {
            size_t rowNum = j + 1;

            while (rowNum < n && A.values[rowNum][j] == 0)
                rowNum++;

            if (rowNum == n)
               throw "solveGauss: |A| = 0";

           	double *tmp = A.values[rowNum];
			A.values[rowNum] = A.values[j];
			A.values[j] = tmp;

			tmp = B.values[rowNum];
			B.values[rowNum] = B.values[j];
			B.values[j] = tmp;
        }

        for (size_t i = j + 1; i < n; i++) {
            double elem = A.values[i][j] / A.values[j][j];

            for (size_t k = 0; k < n; k++) {
                A.values[i][k] -= A.values[j][k] * elem;
                B.values[i][k] -= B.values[j][k] * elem;
            }
        }
    }

    // reverse step
    Matrix X = initMatrix(n, b.cols);

    for (int i = n - 1; i >= 0; i--) {
    	for (size_t j = 0; j < b.cols; j++) {
	        double sum = B.values[i][j];

	        for (int k = n - 1; k > i; k--)
	            sum -= A.values[i][k] * X.values[k][j];

	        X.values[i][j] = sum / A.values[i][i];
	    }
    }

    deleteMatrix(A);
    deleteMatrix(B);

    return X;
}

Vector initVector(size_t size) {
	Vector vector;

	vector.size = size;
	vector.values = new double[size];

	for (size_t i = 0; i < size; i++)
		vector.values[i] = 0;

	return vector;
}

void deleteVector(Vector &vector) {
	if (vector.size == 0)
		return;

	delete[] vector.values;
	vector.values = NULL;
	vector.size = 0;
}