#pragma once
#include <vector>
#include <random>
using namespace std;

extern random_device rnd_dev;
extern mt19937 eng;
extern uniform_int_distribution<> rnd_gen;

int SomeRand();

double GetRandVal(double min_val, double max_val);

class Matrix2d {
private:
	int num_rows;
	int num_cols;
	double* matrix;
public:
	Matrix2d() { num_rows = 0; num_cols = 0; matrix = nullptr; };	// ����������� �� ���������
	~Matrix2d();
	Matrix2d(int nrow, int ncol, double val = 0.0);
	Matrix2d(const Matrix2d& _m);						// ����������� �����������
	Matrix2d(vector<double>& _m);

	void InitMatrix(double val);
	void InitMatrix(int nrow, int ncol, double val);
	void InitMatrixDiagByOne();
	void InitRandom(double minval, double maxval);
	void InitValue(double val);

	int GetNumRows() const;
	int GetNumCols() const;

	Matrix2d Transpose() const;							// ���������������� �������
	Matrix2d MultElByEl(const Matrix2d& _m) const;			// ������������ ��������� ������
	double SumAll() const;								// �������� ���� ��������� �������
	double SumAllSqr() const;							// �������� ��������� ���� ��������� �������
	Matrix2d Sqrt();

	double& at(const int& i, const int& j);
	double at(const int& i, const int& j) const;

	Matrix2d& operator = (vector<double>& _m);
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

	Matrix2d operator / (const double val);		// ������� ��������� ������� �� �����
	Matrix2d& operator /= (const double val);		// ������� ��������� ������� �� �����

	friend Matrix2d operator / (const double val, const Matrix2d& _m);
};
