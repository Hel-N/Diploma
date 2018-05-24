#pragma once
#include "Matrix2d.h"
#include <vector>
#include <algorithm>

using namespace std;

// Конструктор по умолчанию
Matrix2d::Matrix2d() {
	num_rows = 0;
	num_cols = 0;
	matrix.resize(0);
}
//
Matrix2d::Matrix2d(int nrow, int ncol, double val) {
	num_rows = nrow;
	num_cols = ncol;
	matrix.clear();
	matrix.resize(nrow, vector<double>(ncol, val));
}
void Matrix2d::InitMatrix(int nrow, int ncol, double val) {
	num_rows = nrow;
	num_cols = ncol;
	matrix.clear();
	matrix.resize(nrow, vector<double>(ncol, val));
}
void Matrix2d::InitMatrixDiagByOne(int nrow, int ncol) {
	num_rows = nrow;
	num_cols = ncol;
	matrix.clear();
	matrix.resize(nrow, vector<double>(ncol, 0.0));
	int n = min(num_rows, num_cols);
	for (int i = 0; i < n; ++i) {
		matrix[i][i] = 1.0;
	}
}
void Matrix2d::InitRandom(double minval, double maxval) {
	for (int i = 0; i < num_rows; ++i) {
		for (int j = 0; j < num_cols; ++j) {
			matrix[i][j] = minval + (maxval - minval)*rand() / RAND_MAX;
		}
	}
}
int Matrix2d::GetNumRows() const {
	return num_rows;
}
int Matrix2d::GetNumCols() const {
	return num_cols;
}
// Транспонирование матрицы
Matrix2d Matrix2d::Transpose() const {
	int n = GetNumCols();
	int m = GetNumRows();
	Matrix2d res(n, m);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			res(i, j) = matrix[j][i];
		}
	}
	return move(res);
}
// Поэлементное умножение матриц
Matrix2d Matrix2d::MultElByEl(Matrix2d _m) const {
	if (_m.GetNumRows() != num_rows || _m.GetNumCols() != num_rows) {
		//Error!
	}

	Matrix2d res(num_rows, num_cols);
	for (int i = 0; i < num_rows; ++i) {
		for (int j = 0; j < num_cols; ++j) {
			res(i, j) = matrix[i][j] * _m(i, j);
		}
	}

	return move(res);
}
// Сложение квадрвтов всех элементов матрицы
double Matrix2d::SumAllSqr() const {
	double res = 0;
	for (int i = 0; i < num_rows; ++i) {
		for (int j = 0; j < num_cols; ++j) {
			res += matrix[i][j] * matrix[i][j];
		}
	}

	return res;
}
// Сложение всех элементов матрицы
double Matrix2d::SumAll() const {
	double res = 0.0;
	for (int i = 0; i < num_rows; ++i) {
		for (int j = 0; j < num_cols; ++j) {
			res += matrix[i][j];
		}
	}

	return res;
}
double& Matrix2d::operator () (int i, int j) {
	if ((i < 0 || i >= num_rows) || (j < 0 || j >= num_cols)) {
		//Error!
	}
	return matrix[i][j];
}
Matrix2d& Matrix2d::operator = (vector<vector<double>>& _m) {
	num_rows = _m.size();
	matrix.clear();
	matrix.resize(num_rows);
	num_cols = (num_rows != 0 ? _m[0].size() : 0);
	for (int i = 0; i < num_rows; ++i) {
		matrix[i].resize(num_cols);
		for (int j = 0; j < num_cols; ++j) {
			matrix[i][j] = _m[i][j];
		}
	}
	return *this;
}
Matrix2d& Matrix2d::operator = (Matrix2d& _m) {
	num_rows = _m.GetNumRows();
	matrix.clear();
	matrix.resize(num_rows);
	num_cols = _m.GetNumCols();
	for (int i = 0; i < num_rows; ++i) {
		matrix[i].resize(num_cols);
		for (int j = 0; j < num_cols; ++j) {
			matrix[i][j] = _m(i, j);
		}
	}
	return *this;
}
// Сложение матрицы с числом
Matrix2d Matrix2d::operator + (const double val) {
	Matrix2d res(num_rows, num_cols);
	for (int i = 0; i < num_rows; ++i) {
		for (int j = 0; j < num_cols; ++j) {
			res(i, j) = matrix[i][j] + val;
		}
	}

	return move(res);
}
// Сложение матрицы с числом
Matrix2d& Matrix2d::operator += (const double val) {
	Matrix2d res = *this;
	res = res + val;
	return *this = res;
}
// Сложение матриц
Matrix2d Matrix2d::operator + (Matrix2d& _m) {
	if (_m.GetNumRows() != num_rows || _m.GetNumCols() != num_rows) {
		//Error!
	}

	Matrix2d res(num_rows, num_cols);
	for (int i = 0; i < num_rows; ++i) {
		for (int j = 0; j < num_cols; ++j) {
			res(i, j) = matrix[i][j] + _m(i, j);
		}
	}

	return move(res);
}
// Сложение матриц
Matrix2d& Matrix2d::operator += (Matrix2d& _m) {
	Matrix2d res = *this;
	res = res + _m;
	return *this = res;
}
// Вычетание числа из матрицы
Matrix2d Matrix2d::operator - (const double val) {
	Matrix2d res(num_rows, num_cols);
	for (int i = 0; i < num_rows; ++i) {
		for (int j = 0; j < num_cols; ++j) {
			res(i, j) = matrix[i][j] - val;
		}
	}

	return move(res);
}
// Вычетание числа из матрицы
Matrix2d& Matrix2d::operator -= (const double val) {
	Matrix2d res = *this;
	res = res - val;
	return *this = res;
}
// Вычетание матриц
Matrix2d Matrix2d::operator - (Matrix2d& _m) {
	if (_m.GetNumRows() != num_rows || _m.GetNumCols() != num_rows) {
		//Error!
	}

	Matrix2d res(num_rows, num_cols);
	for (int i = 0; i < num_rows; ++i) {
		for (int j = 0; j < num_cols; ++j) {
			res(i, j) = matrix[i][j] - _m(i, j);
		}
	}

	return move(res);
}
// Вычетание матриц
Matrix2d& Matrix2d::operator -= (Matrix2d& _m) {
	Matrix2d res = *this;
	res = res - _m;
	return *this = res;
}
// Умножение матрицы на число
Matrix2d Matrix2d::operator * (const double val) {
	Matrix2d res(num_rows, num_cols);
	for (int i = 0; i < num_rows; ++i) {
		for (int j = 0; j < num_cols; ++j) {
			res(i, j) = matrix[i][j] * val;
		}
	}

	return move(res);
}
// Умножение матрицы на число
Matrix2d& Matrix2d::operator *= (const double val) {
	Matrix2d res = *this;
	res = res * val;
	return *this = res;
}
// Произведение матриц
Matrix2d Matrix2d::operator * (Matrix2d& _m) {
	if (_m.GetNumRows() != num_cols) {
		//Error!
	}

	Matrix2d res(num_rows, _m.GetNumCols());
	int _mnum_cols = _m.GetNumCols();
	for (int i = 0; i < num_rows; ++i) {
		for (int j = 0; j < _mnum_cols; ++j) {
			for (int k = 0; k < num_cols; ++k) {
				res(i, j) += matrix[i][k] * _m(k, j);
			}
		}
	}

	return move(res);
}
// Произведение матриц
Matrix2d& Matrix2d::operator *= (Matrix2d& _m) {
	Matrix2d res = *this;
	res = res * _m;
	return *this = res;
}
// Деление элементов матрицы на число
Matrix2d Matrix2d::operator / (const double val) {
	Matrix2d res(num_rows, num_cols);
	for (int i = 0; i < num_rows; ++i) {
		for (int j = 0; j < num_cols; ++j) {
			res(i, j) = matrix[i][j] / val;
		}
	}

	return move(res);
}
// Деление элементов матрицы на число
Matrix2d& Matrix2d::operator /= (const double val) {
	Matrix2d res = *this;
	res = res / val;
	return *this = res;
}
