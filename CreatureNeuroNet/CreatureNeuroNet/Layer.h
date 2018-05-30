#pragma once
#include "Matrix2d.h"

enum ActFuncTypes { NA, TANH, SGMD, LINE };

class Layer {
private:
	ActFuncTypes activation_func;
	int num_neurons;
	int num_prev_neurons;

	Matrix2d sgmd_func(Matrix2d& _states);		// Сигмоидальная функция
	Matrix2d tanh_func(Matrix2d& _states);		// Гиперболический тангенс
	Matrix2d diff_sgmd_func(Matrix2d& _axons);		// Сигмоидальная функция
	Matrix2d diff_tanh_func(Matrix2d& _axons);		// Гиперболический тангенс

public:
	Matrix2d weights;		// Веса нейронов
	Matrix2d states;		// Состояния нейронов
	Matrix2d biases;		// Смещения нейронов
	Matrix2d axons;			// Аксоны нейронов
	Matrix2d delta;			// Дельта
	Matrix2d prev_delta;	// Предыдущая дельта
	Matrix2d delta_sum;
	Matrix2d prev_delta_sum;
	Matrix2d grad;			// Градиент
	Matrix2d prev_grad;
	Matrix2d grad_sum;
	Matrix2d prev_grad_sum;

	Matrix2d weights_correct;
	Matrix2d biases_correct;

	//RMS
	Matrix2d rms;
	Matrix2d rms_biases;
	Matrix2d rmsn;
	Matrix2d rmsn_biases;


	Layer();
	Layer(int nneurons, int nprevneurons, ActFuncTypes act_func);

	Layer& operator = (Layer& _l);

	void Init(int nneurons, int nprevneurons, ActFuncTypes act_func, Matrix2d _biases, Matrix2d _weights);

	int GetNumNeurons();

	void CalcStates(Layer& prev_layer);
	void CalcAxons();
	Matrix2d CalcDiffs();
};
