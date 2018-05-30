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

void NeuroNet::Init(int ninputs, int nlayers, vector<int> nlneurons, vector<ActFuncTypes> _aft, int noutputs, vector<Matrix2d> _biases, vector<Matrix2d> _weights) {
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
		layers.back().Init(nlneurons[i], nprevneurons, _aft[i], _biases[i], _weights[i]);
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
	if (ts.size() >= NUM_TESTS)
		ts.pop();
	Test new_test(test_in, test_out);
	ts.push(new_test);
}
void NeuroNet::AddTest(queue<Test>& ts, Matrix2d _in, Matrix2d _out) {
	if (ts.size() >= NUM_TESTS)
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

	CorrectWeightsAndBiases(_grad, _delta);

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

void NeuroNet::ResilientPropagation() {
	double EttaPlus = 1.2;
	double EttaMinus = 0.5;
	double MinCorrectVal = 1e-6;
	double MaxCorrectVal = 50.0;
	for (int i = 1; i < layers.size() - 1; ++i)
	{
		for (int j = 0; j < layers[i].grad_sum.GetNumRows(); ++j)
		{
			for (int k = 0; k < layers[i].grad_sum.GetNumCols(); ++k)
			{
				double correct_val = 0.0;
				double curmatrixult = layers[i].grad_sum(j, k) * layers[i].prev_grad_sum(j, k);
				if (curmatrixult == 0.0)
					correct_val = rand() / RAND_MAX;
				else if (curmatrixult > 0.0)
					correct_val = min(EttaPlus * layers[i].weights_correct(j, k), MaxCorrectVal);
				else if (curmatrixult < 0.0)
					correct_val = max(EttaMinus * layers[i].weights_correct(j, k), MinCorrectVal);

				layers[i].weights_correct(j, k) = correct_val;

				if (layers[i].grad_sum(j, k) == 0.0)
					continue;

				if (layers[i].grad_sum(j, k) > 0.0)
					layers[i].weights(j, k) -= correct_val;
				else
					layers[i].weights(j, k) += correct_val;
			}
		}

		for (int j = 0; j < layers[i].delta_sum.GetNumRows(); ++j)
		{
			double cur_correct = 0.0;
			double curmatrixult = layers[i].delta_sum(0, j) * layers[i].prev_delta_sum(0, j);
			if (curmatrixult == 0.0)
				cur_correct = rand() / RAND_MAX;
			else if (curmatrixult > 0.0)
				cur_correct = min(EttaPlus * layers[i].biases_correct(0, j), MaxCorrectVal);
			else if (curmatrixult < 0.0)
				cur_correct = max(EttaMinus * layers[i].biases_correct(0, j), MinCorrectVal);

			layers[i].biases_correct(0, j) = cur_correct;

			if (layers[i].delta_sum(0, j) == 0.0) 
				continue;

			if (layers[i].delta_sum(0, j) > 0.0)
				layers[i].biases(0, j) -= cur_correct;
			else
				layers[i].biases(0, j) += cur_correct;
		}
	}
}
double NeuroNet::RPropLearningOffline(vector<Test> & tests) {
	for (int i = 0; i < layers.size(); ++i) {
		layers[i].delta_sum.InitValue(0.0);
		layers[i].grad_sum.InitValue(0.0);
	}

	for (int i = 0; i < tests.size(); ++i) {
		Running(tests[i]);
		CalcDeltaAndGrad(tests[i]);

		for (int i = 1; i < layers.size() - 1; ++i) {
			layers[i].delta_sum += layers[i].delta;
			layers[i].grad_sum += layers[i].grad;
		}
	}

	// Вычисление суммы квадратов градиентов
	double norm = 0.0;
	for (int i = 1; i < layers.size() - 1; ++i) {
		norm += layers[i].delta_sum.SumAllSqr();
		norm += layers[i].grad_sum.SumAllSqr();
	}

	if (norm < 1e-6) {
		return 0.0;
	}

	ResilientPropagation();

	for (int i = 1; i < layers.size() - 1; ++i) {
		layers[i].prev_delta_sum = layers[i].delta_sum;
		layers[i].prev_grad_sum = layers[i].grad_sum;
	}

	double err = 0.0;
	for (int i = 0; i < tests.size(); ++i) {
		Running(tests[i]);
		err += CalcError(tests[i]);
	}

	return err;
}
double NeuroNet::RPropLearningOffline(queue<Test> tests) {
	vector<Test> vtests;
	queue<Test> qt = tests;
	while (!qt.empty()) {
		vtests.push_back(qt.front());
		qt.pop();
	}
	return RPropLearningOffline(vtests);
}

void NeuroNet::PrintWeightsAndBiases(bool print_null) {
	cout << "----------Weights------------" << endl;
	for (int i = 1; i < layers.size() - 1; ++i) {
		Matrix2d m = layers[i].weights.Transpose();
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
		layers[i].delta = (layers[i + 1].delta*layers[i + 1].weights).MultElByEl(layers[i].CalcDiffs());
	}

	for (int i = 1; i < layers.size() - 1; ++i) {
		layers[i].grad = layers[i].delta.Transpose() * layers[i - 1].axons;
	}
}
double NeuroNet::CalcError(Test& test) {
	double res = (test.outputs - layers.back().axons).SumAllSqr() / 2.0;
	return res;
}
void NeuroNet::CorrectWeightsAndBiases(vector<Matrix2d>& _gradient, vector<Matrix2d>& _delta) {
	for (int i = 1; i < layers.size() - 1;++i) {
		layers[i].weights -= _gradient[i] * LearningRate;
		layers[i].biases -= _delta[i] * LearningRate;
	}
}

void NeuroNet::SetWeights(vector<Matrix2d> _w) {
	for (int i = 1; i < layers.size() - 1; ++i) {
		Matrix2d m = _w[i - 1].Transpose();
		layers[i].weights = m;
	}
}
void NeuroNet::SetBiases(vector<Matrix2d> _b) {
	for (int i = 1; i < layers.size() - 1; ++i) {
		layers[i].biases = _b[i - 1];

	}
}
ostream& operator << (ostream& out, NeuroNet& _nnet) {
	for (int i = 0; i < _nnet.num_outputs; ++i) {
		out << fixed << setprecision(6) << _nnet.outputs(0, i) << " ";
	}
	return out;
}