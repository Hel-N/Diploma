#pragma once
#include <vector>
using namespace std;

class Matrix2d {
private:
	int num_rows;
	int num_cols;
	vector<vector<double>> matrix;
public:
	Matrix2d();											// Конструктор по умолчанию
	Matrix2d(int nrow, int ncol, double val = 0.0);
	//Matrix2d(Matrix2d& _m);						// Конструктор копирования

	void InitMatrix(int nrow, int ncol, double val);
	void InitMatrixDiagByOne(int nrow, int ncol);
	void InitRandom(double minval, double maxval);
	void InitValue(double val);

	int GetNumRows() const;
	int GetNumCols() const;

	Matrix2d Transpose() const;							// Транспонирование матрицы
	Matrix2d MultElByEl(Matrix2d _m) const;				// Поэлементное умножение матриц
	double SumAll() const;								// Сложение всех элементов матрицы
	double SumAllSqr() const;							// Сложение квадрвтов всех элементов матрицы
	Matrix2d Sqrt();

	double& operator () (int i, int j);
	Matrix2d& operator = (vector<vector<double>>& _m);
	Matrix2d& operator = (Matrix2d& _m);

	Matrix2d operator + (const double val);		// Сложение матрицы с числом
	Matrix2d& operator += (const double val);		// Сложение матрицы с числом
	Matrix2d operator + (Matrix2d& _m);			// Сложение матриц
	Matrix2d& operator += (Matrix2d& _m);			// Сложение матриц

	Matrix2d operator - (const double val);		// Вычетание числа из матрицы
	Matrix2d& operator -= (const double val);		// Вычетание числа из матрицы
	Matrix2d operator - (Matrix2d& _m);			// Вычетание матриц
	Matrix2d& operator -= (Matrix2d& _m);			// Вычетание матриц

	Matrix2d operator * (const double val);		// Умножение матрицы на число
	Matrix2d& operator *= (const double val);		// Умножение матрицы на число
	Matrix2d operator * (Matrix2d& _m);			// Произведение матриц
	Matrix2d& operator *= (Matrix2d& _m);			// Произведение матриц

	Matrix2d operator / (const double val);		// Деление элементов матрицы на число
	Matrix2d& operator /= (const double val);		// Деление элементов матрицы на число

	friend Matrix2d operator / (const double val, const Matrix2d& _m);
};
