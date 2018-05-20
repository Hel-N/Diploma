#pragma once
#include <vector>
#include "Matrix2d.h"
#include "Layer.h"

using namespace std;

Matrix2d Layer::sgmd_func(Matrix2d& _states) {
	int n = _states.GetNumRows();
	int m = _states.GetNumCols();
	Matrix2d res(n, m);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (_states(i, j) < (-1.0 * 35))
				res(i, j) = 1e-12;
			else
				res(i, j) = 1.0 / (1.0 + exp(-_states(i, j)));
		}
	}
	return res;
}
Matrix2d Layer::tanh_func(Matrix2d& _states) {
	int n = _states.GetNumRows();
	int m = _states.GetNumCols();
	//Matrix2d res = sgmd_func(_states * 2) * 2 - 1;
	Matrix2d res(n, m);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			res(i, j) = tanh(_states(i, j));
		}
	}
	return res;
}
Matrix2d Layer::diff_sgmd_func(Matrix2d& _axons) {
	int n = _axons.GetNumRows();
	int m = _axons.GetNumCols();
	Matrix2d res(n, m);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			res(i, j) = (1.0 - _axons(i, j)) * _axons(i, j);
		}
	}
	return res;
}
Matrix2d Layer::diff_tanh_func(Matrix2d& _axons) {
	int n = _axons.GetNumRows();
	int m = _axons.GetNumCols();
	Matrix2d res(n, m);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			res(i, j) = (1.0 - _axons(i, j) * _axons(i, j));
		}
	}
	return res;
}

Layer::Layer() {
	activation_func = NA;
	num_prev_neurons = 0;
	num_neurons = 0;
	waights = Matrix2d();
	states = Matrix2d();
	biases = Matrix2d();
	axons = Matrix2d();
	delta = Matrix2d();
	grad = Matrix2d();
}
Layer::Layer(int nneurons, int nprevneurons, ActFuncTypes act_func) {
	activation_func = act_func;
	num_prev_neurons = nprevneurons;
	num_neurons = nneurons;

	waights = Matrix2d(nneurons, nprevneurons);
	waights.InitRandom(0.0, 1.0);
	states = Matrix2d(1, nneurons);
	biases = Matrix2d(1, nneurons);
	biases.InitRandom(-1.0, 1.0);
	axons = Matrix2d(1, nneurons);
	delta = Matrix2d(1, nneurons);
	grad = Matrix2d(nneurons, nprevneurons);
}
Layer& Layer::operator = (Layer& _l) {
	activation_func = _l.activation_func;
	num_prev_neurons = _l.num_prev_neurons;
	num_neurons = _l.GetNumNeurons();
	waights = _l.waights;
	states = _l.states;
	biases = _l.biases;
	axons = _l.axons;
	delta = _l.delta;
	grad = _l.grad;
	return *this;
}
void Layer::Init(int nneurons, int nprevneurons, ActFuncTypes act_func, Matrix2d _biases, Matrix2d _waights) {
	activation_func = act_func;
	num_prev_neurons = nprevneurons;
	num_neurons = nneurons;
	waights = _waights;
	states = Matrix2d(1, nneurons);
	biases = _biases;
	axons = Matrix2d(1, nneurons);
	delta = Matrix2d(1, nneurons);
	grad = Matrix2d(nneurons, nprevneurons);
}
int Layer::GetNumNeurons() {
	return num_neurons;
}
void Layer::CalcStates(Layer& prev_layer) {
	states = prev_layer.axons * waights.Transpose() + biases;
}
void Layer::CalcAxons() {
	switch (activation_func) {
	case TANH: axons = tanh_func(states); break;
	case SGMD: axons = sgmd_func(states); break;
	case LINE: axons = states; break;
	default: break;
	}
}
Matrix2d Layer::CalcDiffs() {
	switch (activation_func) {
	case TANH: return diff_tanh_func(axons); break;
	case SGMD: return diff_sgmd_func(axons); break;
	case LINE:
	{
		Matrix2d m;
		m.InitMatrix(axons.GetNumRows(), axons.GetNumCols(), 1.0);
		return m;
		break;
	}
	default: break;
	}
}
