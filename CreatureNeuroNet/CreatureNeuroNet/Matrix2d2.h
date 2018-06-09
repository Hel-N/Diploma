#pragma once
#include <vector>
using namespace std;

class Matrix2d {
private:
	int num_rows;
	int num_cols;
	vector<vector<double>> matrix;
public:
	Matrix2d();											// ����������� �� ���������
	Matrix2d(int nrow, int ncol, double val = 0.0);
	//Matrix2d(Matrix2d& _m);						// ����������� �����������

	void InitMatrix(int nrow, int ncol, double val);
	void InitMatrixDiagByOne(int nrow, int ncol);
	void InitRandom(double minval, double maxval);
	void InitValue(double val);

	int GetNumRows() const;
	int GetNumCols() const;

	Matrix2d Transpose() const;							// ���������������� �������
	Matrix2d MultElByEl(Matrix2d _m) const;				// ������������ ��������� ������
	double SumAll() const;								// �������� ���� ��������� �������
	double SumAllSqr() const;							// �������� ��������� ���� ��������� �������
	Matrix2d Sqrt();

	double& operator () (int i, int j);
	Matrix2d& operator = (vector<vector<double>>& _m);
	Matrix2d& operator = (Matrix2d& _m);

	Matrix2d operator + (const double val);		// �������� ������� � ������
	Matrix2d& operator += (const double val);		// �������� ������� � ������
	Matrix2d operator + (Matrix2d& _m);			// �������� ������
	Matrix2d& operator += (Matrix2d& _m);			// �������� ������

	Matrix2d operator - (const double val);		// ��������� ����� �� �������
	Matrix2d& operator -= (const double val);		// ��������� ����� �� �������
	Matrix2d operator - (Matrix2d& _m);			// ��������� ������
	Matrix2d& operator -= (Matrix2d& _m);			// ��������� ������

	Matrix2d operator * (const double val);		// ��������� ������� �� �����
	Matrix2d& operator *= (const double val);		// ��������� ������� �� �����
	Matrix2d operator * (Matrix2d& _m);			// ������������ ������
	Matrix2d& operator *= (Matrix2d& _m);			// ������������ ������

	Matrix2d operator / (const double val);		// ������� ��������� ������� �� �����
	Matrix2d& operator /= (const double val);		// ������� ��������� ������� �� �����

	friend Matrix2d operator / (const double val, const Matrix2d& _m);
};
