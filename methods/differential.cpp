#include "differential.h"

using namespace std;

vector<Point> eulerMethod(Fpointer f, double a, double b, double h, double y0) {
	int n = (b - a) / h + 1;
	vector<Point> solve = vector<Point>(n);

	solve[0].x = a;
	solve[0].y = y0; // начальные условия

	for (int i = 1; i < n; i++) {
		solve[i].x = solve[i - 1].x + h;
		solve[i].y = solve[i - 1].y + h * f(solve[i - 1].x, solve[i - 1].y);
	}
	
	return solve;
}

vector<Point> eulerAdvancedMethod(Fpointer f, double a, double b, double h, double y0) {
	int n = (b - a) / h + 1;
	vector<Point> solve = vector<Point>(n);

	solve[0].x = a;
	solve[0].y = y0; // начальные условия

	for (int i = 1; i < n; i++) {
		solve[i].x = solve[i - 1].x + h;
		solve[i].y = solve[i - 1].y + h * f(solve[i - 1].x + h / 2, solve[i - 1].y + h / 2 * f (solve[i - 1].x, solve[i - 1].y));
	}

	return solve;
}

vector<Point> rungeKutt3Method(Fpointer f, double a, double b, double h, double y0) {
	int n = (b - a) / h + 1;
	vector<Point> solve = vector<Point>(n);

	solve[0].x = a;
	solve[0].y = y0; // начальные условия

	for (int i = 1; i < n; i++) {
		solve[i].x = solve[i - 1].x + h;

		double k1 = f(solve[i - 1].x, solve[i - 1].y);
		double k2 = f(solve[i - 1].x + h / 2, solve[i - 1].y + h * k1 / 2);
		double k3 = f(solve[i - 1].x + h, solve[i - 1].y + h * (2 * k2 - k1));

		solve[i].y = solve[i - 1].y + h * (k1 + 4 * k2 + k3) / 6;
	}

	return solve;
}

vector<Point> rungeKutt4Method(Fpointer f, double a, double b, double h, double y0) {
	int n = (b - a) / h + 1;
	vector<Point> solve = vector<Point>(n);

	solve[0].x = a;
	solve[0].y = y0; // начальные условия

	for (int i = 1; i < n; i++) {
		solve[i].x = solve[i - 1].x + h;

		double k1 = f(solve[i - 1].x, solve[i - 1].y);
		double k2 = f(solve[i - 1].x + h / 2, solve[i - 1].y + h * k1 / 2);
		double k3 = f(solve[i - 1].x + h / 2, solve[i - 1].y + h * k2 / 2);
		double k4 = f(solve[i - 1].x + h, solve[i - 1].y + h * k3);

		solve[i].y = solve[i - 1].y + h * (k1 + 2 * k2 + 2 * k3 + k4) / 6;
	}

	return solve;
}