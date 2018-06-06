#include <iostream>
#include <fstream>
#include <string>

#include "methods/matrix.h"

using namespace std;

int selectItem(int min, int max) {
	int item;
	cin >> item;

	while (item < min || item > max) {
		cout << "Incorrect item. Try again: ";
		cin >> item;
	}

	return item;
}

void readFromKeyBoard(Matrix &A, Matrix &B) {
	cout << "Enter matrix for read (1 - A, 2 - B): ";
	int item = selectItem(1, 2);
	int rows, cols;

	cout << "Enter rows and cols: ";
	cin >> rows >> cols;

	while (rows < 1 || cols < 1) {
		cout << "Incorrect rows or cols. Try again: ";
		cin >> rows >> cols;
	}

	if (item == 1) {
		deleteMatrix(A);
		A = initMatrix(rows, cols);
		readMatrix(A);
	}
	else {
		deleteMatrix(B);
		B = initMatrix(rows, cols);
		readMatrix(B);
	}
}

void readFromKeyFile(Matrix &A, Matrix &B) {
	cout << "Enter matrix for read (1 - A, 2 - B): ";
	int item = selectItem(1, 2);

	string path;
	cout << "Enter path to file with matrix: ";
	cin >> path;

	fstream f;
	f.open(path, ios::in);

	if (!f) {
		cout << "Incorrect file '" << path << "'" << endl;
	}
	else if (item == 1) {
		deleteMatrix(A);
		A = initMatrix(f);
	}
	else {
		deleteMatrix(B);
		B = initMatrix(f);
	}
}

void printMatrix(const Matrix &A, const Matrix &B) {
	cout << "Enter matrix for print (1 - A, 2 - B, 3 - all): ";
	int item = selectItem(1, 3);

	if (item == 1 || item == 3) {
		cout << "Matrix A:" << endl;
		printMatrix(A);
	}
	
	if (item == 3)
		cout << endl;

	if (item == 2 || item == 3) {
		cout << "Matrix B:" << endl;
		printMatrix(B);
	}
}

void rankMatrix(const Matrix &A, const Matrix &B) {
	cout << "Enter matrix for print rank (1 - A, 2 - B): ";
	int item = selectItem(1, 2);

	if (item == 1) {
		cout << "rank (A) = " << rankMatrix(A) << endl;
	}
	else {
		cout << "rank (B) = " << rankMatrix(B) << endl;
	}
}

void detMatrix(const Matrix &A, const Matrix &B) {
	cout << "Enter matrix for print det (1 - A, 2 - B): ";
	int item = selectItem(1, 2);

	if (item == 1) {
		cout << "|A| = " << determinantMatrix(A) << endl;
	}
	else {
		cout << "|B| = " << determinantMatrix(B) << endl;
	}
}

void solveSystem(const Matrix &A, const Matrix &B) {
	cout << "Enter method to solve (1 - Gauss, 2 - Kramer): ";
	int item = selectItem(1, 2);

	if (item == 1) {
		Matrix X = solveGauss(A, B);

		cout << "AX = B => X:" << endl;
		printMatrix(X);

		deleteMatrix(X);
	}
	else if (item == 2) {

	}
}

int main() {
	int item;

	Matrix A = initMatrix(1, 1);
	Matrix B = initMatrix(1, 1);

	do {
		system("cls");
		cout << "What do you want to do?" << endl;
		cout << "1. Read matrix from keyboard" << endl;
		cout << "2. Read matrix from file" << endl;
		cout << "3. Print matrix" << endl;
		cout << "4. Get determinant" << endl;
		cout << "5. Get rank" << endl;
		cout << "6. Solve AX = B" << endl;
		cout << "7. Quit" << endl;
		cout << "> ";
		cin >> item;

		while (item < 1 || item > 7) {
			cout << "Incorrect item. Try again: ";
			cin >> item;
		}

		switch (item) {
			case 1:
				readFromKeyBoard(A, B);
				break;

			case 2:
				readFromKeyFile(A, B);
				break;

			case 3:
				printMatrix(A, B);
				break;

			case 4:
				detMatrix(A, B);
				break;

			case 5:
				rankMatrix(A, B);
				break;

			case 6:
				solveSystem(A, B);
				break;
		}

		if (item != 7) {
			system("pause");
		}
	} while (item != 7);
}