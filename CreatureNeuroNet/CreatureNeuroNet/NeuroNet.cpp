#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <deque>
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
}
void NeuroNet::AddTest(deque<Test>& ts, vector<vector<double>> _in, vector<vector<double>> _out) {
	Matrix2d test_in;
	Matrix2d test_out;
	test_in = _in;
	test_out = _out;
	if (ts.size() >= TOTAL_TESTS_NUMBER)
		ts.pop_front();
	Test new_test(test_in, test_out);
	ts.push_back(new_test);
}
void NeuroNet::AddTest(deque<Test>& ts, Matrix2d _in, Matrix2d _out) {
	if (ts.size() >= TOTAL_TESTS_NUMBER)
		ts.pop_front();
	Test new_test(_in, _out);
	ts.push_back(new_test);
}
void NeuroNet::Running(Test& test) {
	int n = layers[0].states.GetNumRows();
	int m = layers[0].states.GetNumCols();
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			layers[0].states.at(i, j) = test.inputs.at(i, j);
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

double NeuroNet::RunningLearningOffline(deque<Test> & tests, vector<int>& tests_pos) {
	vector<Matrix2d> _delta(layers.size());
	vector<Matrix2d> _grad(layers.size());

	for (int i = 0; i < layers.size(); ++i) {
		_delta[i] = Matrix2d(layers[i].delta.GetNumRows(), layers[i].delta.GetNumCols());
		_grad[i] = Matrix2d(layers[i].grad.GetNumRows(), layers[i].grad.GetNumCols());
	}

	for (int i = 0; i < tests_pos.size(); ++i) {
		Running(tests[tests_pos[i]]);
		CalcDeltaAndGrad(tests[tests_pos[i]]);

		for (int j = 1; j < layers.size(); ++j) {
			_delta[j] += layers[j].delta;
			_grad[j] += layers[j].grad;
		}
	}

	// ���������� ����� ��������� ����������
	double norm = 0.0;
	for (int i = 1; i < layers.size(); ++i) {
		norm += _delta[i].SumAllSqr();
		norm += _grad[i].SumAllSqr();
	}

	if (fabs(norm) < 1e-7) {
		return 0.0;
	}

	// ���������� ����������
	norm = sqrt(fabs(norm));

	for (int i = 1; i < layers.size(); ++i) {
		_delta[i] /= norm;
		_grad[i] /= norm;
	}

	CorrectWeightsAndBiases(_grad, _delta);

	return norm;
}
//double NeuroNet::RunningLearningOffline(queue<Test> tests) {
//	vector<Test> vtests;
//	queue<Test> qt = tests;
//	while (!qt.empty()) {
//		vtests.push_back(qt.front());
//		qt.pop();
//	}
//	return RunningLearningOffline(vtests);
//}

void NeuroNet::ResilientPropagation() {
	double EttaPlus = 1.2;
	double EttaMinus = 0.5;
	double MinCorrectVal = 1e-6;
	double MaxCorrectVal = 50.0;
	for (int i = 1; i < layers.size(); ++i)
	{
		for (int j = 0; j < layers[i].grad_sum.GetNumRows(); ++j)
		{
			for (int k = 0; k < layers[i].grad_sum.GetNumCols(); ++k)
			{
				double correct_val = 0.0;
				double curmatrixult = layers[i].grad_sum.at(j, k) * layers[i].prev_grad_sum.at(j, k);
				if (curmatrixult == 0.0)
					correct_val = rand() / RAND_MAX;
				else if (curmatrixult > 0.0)
					correct_val = min(EttaPlus * layers[i].weights_correct.at(j, k), MaxCorrectVal);
				else if (curmatrixult < 0.0)
					correct_val = max(EttaMinus * layers[i].weights_correct.at(j, k), MinCorrectVal);

				layers[i].weights_correct.at(j, k) = correct_val;

				if (layers[i].grad_sum.at(j, k) == 0.0)
					continue;

				if (layers[i].grad_sum.at(j, k) > 0.0)
					layers[i].weights.at(j, k) -= correct_val;
				else
					layers[i].weights.at(j, k) += correct_val;
			}
		}

		for (int j = 0; j < layers[i].delta_sum.GetNumRows(); ++j)
		{
			double cur_correct = 0.0;
			double curmatrixult = layers[i].delta_sum.at(0, j) * layers[i].prev_delta_sum.at(0, j);
			if (curmatrixult == 0.0)
				cur_correct = rand() / RAND_MAX;
			else if (curmatrixult > 0.0)
				cur_correct = min(EttaPlus * layers[i].biases_correct.at(0, j), MaxCorrectVal);
			else if (curmatrixult < 0.0)
				cur_correct = max(EttaMinus * layers[i].biases_correct.at(0, j), MinCorrectVal);

			layers[i].biases_correct.at(0, j) = cur_correct;

			if (layers[i].delta_sum.at(0, j) == 0.0)
				continue;

			if (layers[i].delta_sum.at(0, j) > 0.0)
				layers[i].biases.at(0, j) -= cur_correct;
			else
				layers[i].biases.at(0, j) += cur_correct;
		}
	}
}
double NeuroNet::RPropLearningOffline(deque<Test> & tests, vector<int>& tests_pos) {
	for (int i = 0; i < layers.size(); ++i) {
		layers[i].delta_sum.InitValue(0.0);
		layers[i].grad_sum.InitValue(0.0);
	}

	for (int i = 0; i < tests_pos.size(); ++i) {
		Running(tests[tests_pos[i]]);
		CalcDeltaAndGrad(tests[tests_pos[i]]);

		for (int j = 1; j < layers.size(); ++j) {
			layers[j].delta_sum += layers[j].delta;
			layers[j].grad_sum += layers[j].grad;
		}
	}

	// ���������� ����� ��������� ����������
	double norm = 0.0;
	for (int i = 1; i < layers.size(); ++i) {
		norm += layers[i].delta_sum.SumAllSqr();
		norm += layers[i].grad_sum.SumAllSqr();
	}

	if (norm < 1e-6) {
		return 0.0;
	}

	ResilientPropagation();

	for (int i = 1; i < layers.size(); ++i) {
		layers[i].prev_delta_sum = layers[i].delta_sum;
		layers[i].prev_grad_sum = layers[i].grad_sum;
	}

	double err = 0.0;
	for (int i = 0; i < tests_pos.size(); ++i) {
		Running(tests[tests_pos[i]]);
		err += CalcError(tests[tests_pos[i]]);
	}

	return err;
}
//double NeuroNet::RPropLearningOffline(queue<Test> tests) {
//	vector<Test> vtests;
//	queue<Test> qt = tests;
//	while (!qt.empty()) {
//		vtests.push_back(qt.front());
//		qt.pop();
//	}
//	return RPropLearningOffline(vtests);
//}

void NeuroNet::RMSPropagation()
{
	for (int i = 1; i < layers.size(); ++i)
	{
		layers[i].weights -= (RMS_LEARN_RATE / (layers[i].rms - layers[i].rmsn.MultElByEl(layers[i].rmsn) + RMS_EPS).Sqrt()).MultElByEl(layers[i].grad_sum);
		layers[i].biases -= (RMS_LEARN_RATE / (layers[i].rms_biases - layers[i].rmsn_biases.MultElByEl(layers[i].rmsn_biases) + RMS_EPS).Sqrt()).MultElByEl(layers[i].delta_sum);
	}
}
double NeuroNet::RMSLearningOffline(deque<Test> & tests, vector<int>& tests_pos)
{
	for (int i = 0; i < layers.size(); ++i)
	{
		layers[i].grad_sum.InitValue(0.0);
		layers[i].delta_sum.InitValue(0.0);
	}

	for (int i = 0; i < tests_pos.size(); ++i)
	{
		Running(tests[tests_pos[i]]);
		CalcDeltaAndGrad(tests[tests_pos[i]]);

		for (int j = 1; j < layers.size(); ++j) {
			layers[j].delta_sum += layers[j].delta;
			layers[j].grad_sum += layers[j].grad;
		}
	}

	for (int i = 1; i < layers.size(); ++i)
	{
		layers[i].rms = layers[i].rms * RMS_GAMMA + layers[i].grad_sum.MultElByEl(layers[i].grad_sum) * (1.0 - RMS_GAMMA);
		layers[i].rms_biases = layers[i].rms_biases * RMS_GAMMA + layers[i].delta_sum.MultElByEl(layers[i].delta_sum) * (1.0 - RMS_GAMMA);
		layers[i].rmsn = layers[i].rmsn * RMS_GAMMA + layers[i].grad_sum * (1.0 - RMS_GAMMA);
		layers[i].rmsn_biases = layers[i].rmsn_biases * RMS_GAMMA + layers[i].delta_sum * (1.0 - RMS_GAMMA);
	}


	RMSPropagation();
	for (int i = 0; i < layers.size(); ++i)
	{
		layers[i].prev_grad_sum = layers[i].grad_sum;
		layers[i].prev_delta_sum = layers[i].delta_sum;
	}

	double err = 0.0;
	for (int i = 0; i < tests_pos.size(); ++i) {
		Running(tests[tests_pos[i]]);
		err += CalcError(tests[tests_pos[i]]);
	}

	return err;
}
//double NeuroNet::RMSLearningOffline(queue<Test> tests) {
//	vector<Test> vtests;
//	queue<Test> qt = tests;
//	while (!qt.empty()) {
//		vtests.push_back(qt.front());
//		qt.pop();
//	}
//	return RMSLearningOffline(vtests);
//}

void NeuroNet::PrintWeightsAndBiases(ostream& fout, bool print_null) {
	fout << "----------Weights------------" << endl;
	for (int i = 1; i < layers.size(); ++i) {
		Matrix2d m = layers[i].weights.Transpose();
		for (int j = 0; j < m.GetNumRows(); ++j) {
			for (int k = 0; k < m.GetNumCols(); ++k) {
				if (!print_null)
					fout << fixed << setprecision(7) << m.at(j, k) << " ";
				else
					fout << fixed << setprecision(7) << 0.0 << " ";
			}
			fout << endl;
		}
	}
	fout << "----------Biases------------" << endl;
	for (int i = 1; i < layers.size(); ++i) {
		Matrix2d m = layers[i].biases;
		for (int j = 0; j < m.GetNumRows(); ++j) {
			for (int k = 0; k < m.GetNumCols(); ++k) {
				if (!print_null)
					fout << fixed << setprecision(7) << m.at(j, k) << " ";
				else
					fout << fixed << setprecision(7) << 0.0 << " ";
			}
			fout << endl;
		}
	}
}
Matrix2d NeuroNet::GetOutput() {
	return outputs;
}
void NeuroNet::CalcDeltaAndGrad(Test& test) {
	layers[layers.size() - 1].delta = (layers[layers.size() - 1].axons - test.outputs).MultElByEl(layers[layers.size() - 1].CalcDiffs());
	for (int i = layers.size() - 2; i > 0; --i) {
		layers[i].delta = (layers[i + 1].delta*layers[i + 1].weights).MultElByEl(layers[i].CalcDiffs());
	}

	for (int i = 1; i < layers.size(); ++i) {
		layers[i].grad = layers[i].delta.Transpose() * layers[i - 1].axons;
	}
}
double NeuroNet::CalcError(Test& test) {
	double res = (test.outputs - layers.back().axons).SumAllSqr() / 2.0;
	return res;
}
void NeuroNet::CorrectWeightsAndBiases(vector<Matrix2d>& _gradient, vector<Matrix2d>& _delta) {
	for (int i = 1; i < layers.size();++i) {
		layers[i].weights -= _gradient[i] * LearningRate;
		layers[i].biases -= _delta[i] * LearningRate;
	}
}

void NeuroNet::SetWeights(vector<Matrix2d> _w) {
	for (int i = 1; i < layers.size(); ++i) {
		Matrix2d m = _w[i - 1].Transpose();
		layers[i].weights = m;
	}
}
void NeuroNet::SetBiases(vector<Matrix2d> _b) {
	for (int i = 1; i < layers.size(); ++i) {
		layers[i].biases = _b[i - 1];

	}
}
ostream& operator << (ostream& out, NeuroNet& _nnet) {
	for (int i = 0; i < _nnet.num_outputs; ++i) {
		out << fixed << setprecision(6) << _nnet.outputs.at(0, i) << " ";
	}
	return out;
}