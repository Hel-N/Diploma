#pragma once
#include "Matrix2d.h"

enum ActFuncTypes { NA, TANH, SGMD, LINE };

class Layer {
private:
	ActFuncTypes activation_func;
	int num_neurons;
	int num_prev_neurons;

	Matrix2d sgmd_func(Matrix2d& _states);		// ������������� �������
	Matrix2d tanh_func(Matrix2d& _states);		// ��������������� �������
	Matrix2d diff_sgmd_func(Matrix2d& _axons);		// ������������� �������
	Matrix2d diff_tanh_func(Matrix2d& _axons);		// ��������������� �������

public:
	Matrix2d waights;		// ���� ��������
	Matrix2d states;		// ��������� ��������
	Matrix2d biases;		// �������� ��������
	Matrix2d axons;			// ������ ��������
	Matrix2d delta;			// ������
	Matrix2d grad;			// ��������

	Layer();
	Layer(int nneurons, int nprevneurons, ActFuncTypes act_func);

	Layer& operator = (Layer& _l);

	void Init(int nneurons, int nprevneurons, ActFuncTypes act_func, Matrix2d _biases, Matrix2d _waights);

	int GetNumNeurons();

	void CalcStates(Layer& prev_layer);
	void CalcAxons();
	Matrix2d CalcDiffs();
};
