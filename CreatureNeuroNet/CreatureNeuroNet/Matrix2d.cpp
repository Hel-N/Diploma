#pragma once
#include "Matrix2d.h"
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

random_device rnd_dev;
mt19937 eng = mt19937(rnd_dev());
uniform_int_distribution<> rnd_gen = uniform_int_distribution<>(0, RAND_MAX);

int SomeRand() {
	return rnd_gen(eng);
}

double GetRandVal(double min_val, double max_val) {
	return min_val + (max_val - min_val) * SomeRand() / RAND_MAX;
}


Matrix2d::~Matrix2d()
{
	if (num_rows != 0)
		delete[](matrix);
	matrix = nullptr;
}

Matrix2d::Matrix2d(int nrow, int ncol, double val) {
	num_rows = nrow;
	num_cols = ncol;
	matrix = new double[nrow*ncol];
	for (int i = 0; i < num_rows*num_cols; ++i) {
		matrix[i] = val;
	}
}

Matrix2d::Matrix2d(const Matrix2d& _m) {
	num_rows = _m.num_rows;
	num_cols = _m.num_cols;
	matrix = new double[num_rows*num_cols];
	memcpy_s(matrix, num_rows*num_cols * sizeof(*matrix), _m.matrix, num_rows*num_cols * sizeof(*_m.matrix));
}

Matrix2d::Matrix2d(vector<double>& _m) {
	num_rows = 1;
	num_cols = _m.size();
	matrix = new double[num_cols];
	memcpy_s(matrix, num_rows*num_cols * sizeof(*matrix), _m.data(), num_rows*num_cols * sizeof(*_m.data()));
}

void Matrix2d::InitMatrix(double val) {
	for (int i = 0; i < num_rows; ++i) {
		for (int j = 0; j < num_cols; ++j) {
			at(i, j) = val;
		}
	}
}

void Matrix2d::InitMatrix(int nrow, int ncol, double val) {
	num_rows = nrow;
	num_cols = ncol;
	matrix = new double[nrow*ncol];
	for (int i = 0; i < num_rows*num_cols; ++i) {
		matrix[i] = val;
	}
}

void Matrix2d::InitMatrixDiagByOne() {
	int n = min(num_rows, num_cols);
	for (int i = 0; i < n; ++i) {
		at(i, i) = 1.0;
	}
}

void Matrix2d::InitRandom(double minval, double maxval) {
	for (int i = 0; i < num_rows; ++i) {
		for (int j = 0; j < num_cols; ++j) {
			//at(i, j) = minval + (maxval - minval)*rand() / RAND_MAX;
			at(i, j) = GetRandVal(minval, maxval);
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
			res.at(i, j) = at(j, i);
		}
	}
	return move(res);
}

// Поэлементное умножение матриц
Matrix2d Matrix2d::MultElByEl(const Matrix2d& _m) const {
	if (_m.GetNumRows() != num_rows || _m.GetNumCols() != num_rows) {
		//throw logic_error("Wrong sizes in \"MultElByEl\" operation");
	}

	Matrix2d res(num_rows, num_cols);
	for (int i = 0; i < num_rows; ++i) {
		for (int j = 0; j < num_cols; ++j) {
			res.at(i, j) = at(i, j) * _m.at(i, j);
		}
	}
	return move(res);
}

// Сложение квадрвтов всех элементов матрицы
double Matrix2d::SumAllSqr() const {
	double res = 0.0;
	for (int i = 0; i < num_rows; ++i) {
		for (int j = 0; j < num_cols; ++j) {
			res += at(i, j) * at(i, j);
		}
	}
	return res;
}

// Сложение всех элементов матрицы
double Matrix2d::SumAll() const {
	double res = 0.0;
	for (int i = 0; i < num_rows; ++i) {
		for (int j = 0; j < num_cols; ++j) {
			res += at(i, j);
		}
	}
	return res;
}

double& Matrix2d::at(const int& i, const int& j) {
	return matrix[i*num_cols + j];
}

double Matrix2d::at(const int& i, const int& j) const {
	return matrix[i*num_cols + j];
}

Matrix2d& Matrix2d::operator = (vector<double>& _m) {
	delete[](matrix);
	num_rows = 1;
	num_cols = _m.size();
	matrix = new double[num_rows*num_cols];
	memcpy_s(matrix, num_rows*num_cols * sizeof(*matrix), _m.data(), num_rows*num_cols * sizeof(*_m.data()));
	
	return *this;
}

Matrix2d& Matrix2d::operator = (vector<vector<double>>& _m) {
	delete[](matrix);
	num_rows = _m.size();
	num_cols = (num_rows != 0) ? _m[0].size() : 0;
	matrix = new double[num_rows*num_cols];
	for (int i = 0; i < num_rows; ++i) {
		for (int j = 0; j < num_cols; ++j) {
			at(i, j) = _m[i][j];
		}
	//	memcpy_s(matrix + i*num_cols, num_cols * sizeof(*matrix), _m[i].data(), num_cols * sizeof(*_m.data()));
	}

	return *this;
}

Matrix2d& Matrix2d::operator = (Matrix2d& _m) {
	delete[](matrix);
	num_rows = _m.GetNumRows();
	num_cols = _m.GetNumCols();
	matrix = new double[num_rows*num_cols];
	memcpy_s(matrix, num_rows*num_cols * sizeof(*matrix), _m.matrix, num_rows*num_cols * sizeof(*_m.matrix));

	return *this;
}

// Сложение матрицы с числом
Matrix2d& Matrix2d::operator += (const double val) {
	for (int i = 0; i < num_rows; ++i) {
		for (int j = 0; j < num_cols; ++j) {
			at(i, j) += val;
		}
	}

	return *this;
}

// Сложение матрицы с числом
Matrix2d Matrix2d::operator + (const double val) {
	Matrix2d res = *this;
	res += val;
	return move(res);
}

// Сложение матриц
Matrix2d& Matrix2d::operator += (Matrix2d& _m) {
	if (_m.GetNumRows() != num_rows || _m.GetNumCols() != num_rows) {
		//Error!
		//throw std::logic_error("Wrong sizes in addition operation");
	}

	for (int i = 0; i < num_rows; ++i) {
		for (int j = 0; j < num_cols; ++j) {
			at(i, j) += _m.at(i, j);
		}
	}

	return *this;
}

// Сложение матриц
Matrix2d Matrix2d::operator + (Matrix2d& _m) {
	Matrix2d res = *this;
	res += _m;
	return move(res);
}

// Вычетание числа из матрицы
Matrix2d& Matrix2d::operator -= (const double val) {
	for (int i = 0; i < num_rows; ++i) {
		for (int j = 0; j < num_cols; ++j) {
			at(i, j) -= val;
		}
	}

	return *this;
}

// Вычетание числа из матрицы
Matrix2d Matrix2d::operator - (const double val) {
	Matrix2d res = *this;
	res -= val;
	return move(res);
}

// Вычетание матриц
Matrix2d& Matrix2d::operator -= (Matrix2d& _m) {
	if (_m.GetNumRows() != num_rows || _m.GetNumCols() != num_rows) {
		//Error!
		//throw std::logic_error("Wrong sizes in subtraction operation");
	}

	for (int i = 0; i < num_rows; ++i) {
		for (int j = 0; j < num_cols; ++j) {
			at(i, j) -= _m.at(i, j);
		}
	}

	return *this;
}

// Вычетание матриц
Matrix2d Matrix2d::operator - (Matrix2d& _m) {
	Matrix2d res = *this;
	res -= _m;
	return move(res);
}

// Умножение матрицы на число
Matrix2d& Matrix2d::operator *= (const double val) {
	for (int i = 0; i < num_rows; ++i) {
		for (int j = 0; j < num_cols; ++j) {
			at(i, j) *= val;
		}
	}

	return *this;
}

// Умножение матрицы на число
Matrix2d Matrix2d::operator * (const double val) {
	Matrix2d res = *this;
	res *= val;
	return move(res);
}

// Произведение матриц
Matrix2d Matrix2d::operator * (Matrix2d& _m) {
	if (_m.GetNumRows() != num_cols) {
		//Error!
		//throw std::logic_error("Wrong sizes in multiplication operation");
	}

	Matrix2d res(num_rows, _m.GetNumCols());
	int _mnum_cols = _m.GetNumCols();
	for (int i = 0; i < num_rows; ++i) {
		for (int j = 0; j < _mnum_cols; ++j) {
			res.at(i, j) = 0.0;
			for (int k = 0; k < num_cols; ++k) {
				res.at(i, j) += at(i, k) * _m.at(k, j);
			}
		}
	}

	return move(res);
}

// Деление элементов матрицы на число
Matrix2d& Matrix2d::operator /= (const double val) {
	for (int i = 0; i < num_rows; ++i) {
		for (int j = 0; j < num_cols; ++j) {
			at(i, j) /= val;
		}
	}

	return *this;
}

// Деление элементов матрицы на число
Matrix2d Matrix2d::operator / (const double val) {
	Matrix2d res = *this;
	res /= val;
	return move(res);
}


Matrix2d Matrix2d::Sqrt() {
	Matrix2d res(num_rows, num_cols);
	for (int i = 0; i < num_rows; ++i) {
		for (int j = 0; j < num_cols; ++j) {
			res.at(i, j) = sqrt(fabs(at(i, j)));
		}
	}

	return move(res);
}

Matrix2d operator / (const double val, const Matrix2d& _m) {
	Matrix2d res(_m.num_rows, _m.num_cols);
	for (int i = 0; i < _m.num_rows; ++i) {
		for (int j = 0; j < _m.num_cols; ++j) {
			res.at(i, j) = val / _m.at(i, j);
			if (isinf(res.at(i, j)) || isnan(res.at(i, j)))
				res.at(i, j) = DBL_MAX;
		}
	}

	return move(res);
}

void Matrix2d::InitValue(double val) {
	for (int i = 0; i < num_rows; ++i) {
		for (int j = 0; j < num_cols; ++j) {
			at(i, j) = val;
		}
	}
}