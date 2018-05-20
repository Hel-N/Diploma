#pragma once
#include <iostream>
#include <iomanip>
#include <queue>
#include "Matrix2d.h"
#include "Layer.h"
#include "NeuroNet.h"

using namespace std;

NeuroNet::NeuroNet() {
	num_inputs = 0;
	num_layers = 0;
	num_outputs = 0;
	layers.resize(0);
}
NeuroNet::NeuroNet(int ninputs, int nlayers, vector<int> nlneurons, vector<ActFuncTypes> _aft, int noutputs) {
	num_inputs = ninputs;
	num_layers = nlayers;
	num_outputs = noutputs;
	layers.push_back(Layer(ninputs, 0, LINE));
	for (int i = 0; i < nlayers; ++i) {
		layers.push_back(Layer(nlneurons[i], layers.back().GetNumNeurons(), _aft[i]));
	}
	int nprevneurons = layers.back().GetNumNeurons();
	Matrix2d _wm;
	_wm.InitMatrixDiagByOne(noutputs, nprevneurons);
	Matrix2d _bm = Matrix2d(noutputs, nprevneurons);
	layers.push_back(Layer());
	layers.back().Init(noutputs, nprevneurons, LINE, _bm, _wm);
}

void NeuroNet::Init(int ninputs, int nlayers, vector<int> nlneurons, vector<ActFuncTypes> _aft, int noutputs, vector<Matrix2d> _biases, vector<Matrix2d> _waights) {
	num_inputs = ninputs;
	num_layers = nlayers;
	num_outputs = noutputs;
	outputs = Matrix2d(1, noutputs);
	Matrix2d _wm, _bm;
	_wm.InitMatrix(ninputs, 1, 1.0);
	_bm = Matrix2d(1, ninputs);
	layers.push_back(Layer());
	layers.back().Init(ninputs, 0, LINE, _bm, _wm);

	int nprevneurons;
	for (int i = 0; i < nlayers; ++i) {
		nprevneurons = layers.back().GetNumNeurons();
		layers.push_back(Layer());
		layers.back().Init(nlneurons[i], nprevneurons, _aft[i], _biases[i], _waights[i]);
	}
	nprevneurons = layers.back().GetNumNeurons();
	_wm.InitMatrixDiagByOne(noutputs, nprevneurons);
	_bm = Matrix2d(noutputs, nprevneurons);
	layers.push_back(Layer());
	layers.back().Init(noutputs, nprevneurons, LINE, _bm, _wm);
}
void NeuroNet::AddTest(queue<Test>& ts, vector<vector<double>> _in, vector<vector<double>> _out) {
	Matrix2d test_in;
	Matrix2d test_out;
	test_in = _in;
	test_out = _out;
	if (ts.size() > NUM_TESTS)
		ts.pop();
	Test new_test(test_in, test_out);
	ts.push(new_test);
}
void NeuroNet::AddTest(queue<Test>& ts, Matrix2d _in, Matrix2d _out) {
	if (ts.size() > NUM_TESTS)
		ts.pop();
	Test new_test(_in, _out);
	ts.push(new_test);
}
void NeuroNet::Running(Test& test) {
	int n = layers[0].states.GetNumRows();
	int m = layers[0].states.GetNumCols();
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			layers[0].states(i, j) = test.inputs(i, j);
		}
	}
	layers[0].CalcAxons();

	for (int i = 1; i < layers.size(); ++i) {
		layers[i].CalcStates(layers[i - 1]);
		layers[i].CalcAxons();
	}
	outputs = layers.back().axons;
}
void NeuroNet::Running(vector<vector<double>>& inputs) {
	Test new_test;
	new_test.inputs = inputs;
	Running(new_test);
}
double NeuroNet::RunningLearningOffline(vector<Test> & tests) {
	vector<Matrix2d> _delta(layers.size());
	vector<Matrix2d> _grad(layers.size());

	for (int i = 0; i < layers.size(); ++i) {
		_delta[i] = Matrix2d(layers[i].delta.GetNumRows(), layers[i].delta.GetNumCols());
		_grad[i] = Matrix2d(layers[i].grad.GetNumRows(), layers[i].grad.GetNumCols());
	}

	for (int i = 0; i < tests.size(); ++i) {
		Running(tests[i]);
		CalcDeltaAndGrad(tests[i]);

		for (int i = 1; i < layers.size() - 1; ++i) {
			_delta[i] += layers[i].delta;
			_grad[i] += layers[i].grad;
		}
	}

	// Вычисление суммы квадратов градиентов
	double norm = 0.0;
	for (int i = 1; i < layers.size() - 1; ++i) {
		norm += _delta[i].SumAllSqr();
		norm += _grad[i].SumAllSqr();
	}

	if (norm == 0.0) {
		return 0.0;
	}

	// Нормировка градиентов
	norm = sqrt(norm);

	for (int i = 1; i < layers.size() - 1; ++i) {
		_delta[i] /= norm;
		_grad[i] /= norm;
	}

	CorrectWaightsAndBiases(_grad, _delta);

	return norm;
}
double NeuroNet::RunningLearningOffline(queue<Test> tests) {
	vector<Test> vtests;
	queue<Test> qt = tests;
	while (!qt.empty()) {
		vtests.push_back(qt.front());
		qt.pop();
	}
	return RunningLearningOffline(vtests);
}
void NeuroNet::PrintWaightsAndBiases(bool print_null) {
	cout << "----------Weights------------" << endl;
	for (int i = 1; i < layers.size() - 1; ++i) {
		Matrix2d m = layers[i].waights.Transpose();
		for (int j = 0; j < m.GetNumRows(); ++j) {
			for (int k = 0; k < m.GetNumCols(); ++k) {
				if (!print_null)
					cout << fixed << setprecision(7) << m(j, k) << " ";
				else
					cout << fixed << setprecision(7) << 0.0 << " ";
			}
			cout << endl;
		}
	}
	cout << "----------Biases------------" << endl;
	for (int i = 1; i < layers.size() - 1; ++i) {
		Matrix2d m = layers[i].biases;
		for (int j = 0; j < m.GetNumRows(); ++j) {
			for (int k = 0; k < m.GetNumCols(); ++k) {
				if (!print_null)
					cout << fixed << setprecision(7) << m(j, k) << " ";
				else
					cout << fixed << setprecision(7) << 0.0 << " ";
			}
			cout << endl;
		}
	}
}
Matrix2d NeuroNet::GetOutput() {
	return outputs;
}
void NeuroNet::CalcDeltaAndGrad(Test& test) {
	layers[layers.size() - 2].delta = (layers[layers.size() - 2].axons - test.outputs).MultElByEl(layers[layers.size() - 2].CalcDiffs());
	for (int i = layers.size() - 3; i > 0; --i) {
		layers[i].delta = (layers[i + 1].delta*layers[i + 1].waights).MultElByEl(layers[i].CalcDiffs());
	}

	for (int i = 1; i < layers.size() - 1; ++i) {
		layers[i].grad = layers[i].delta.Transpose() * layers[i - 1].axons;
	}
}
void NeuroNet::CorrectWaightsAndBiases(vector<Matrix2d>& _gradient, vector<Matrix2d>& _delta) {
	for (int i = 1; i < layers.size() - 1;++i) {
		layers[i].waights -= _gradient[i] * LearningRate;
		layers[i].biases -= _delta[i] * LearningRate;
	}
}
ostream& operator << (ostream& out, NeuroNet& _nnet) {
	for (int i = 0; i < _nnet.num_outputs; ++i) {
		out << fixed << setprecision(6) << _nnet.outputs(0, i) << " ";
	}
	return out;
}