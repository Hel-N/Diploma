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
	Matrix2d waights;		// Веса нейронов
	Matrix2d states;		// Состояния нейронов
	Matrix2d biases;		// Смещения нейронов
	Matrix2d axons;			// Аксоны нейронов
	Matrix2d delta;			// Дельта
	Matrix2d grad;			// Градиент

	Layer();
	Layer(int nneurons, int nprevneurons, ActFuncTypes act_func);

	Layer& operator = (Layer& _l);

	void Init(int nneurons, int nprevneurons, ActFuncTypes act_func, Matrix2d _biases, Matrix2d _waights);

	int GetNumNeurons();

	void CalcStates(Layer& prev_layer);
	void CalcAxons();
	Matrix2d CalcDiffs();
};
