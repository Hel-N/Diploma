#pragma once
#include "Layer.h"
#include "Matrix2d.h"
#include <vector>
#include <queue>
using namespace std;

const int NUM_TESTS = 200;

struct Test {
	Matrix2d inputs;
	Matrix2d outputs;
	Test() {};
	Test(vector<vector<double>> _in, vector<vector<double>> _out) {
		inputs = _in;
		outputs = _out;
	}
	Test(Matrix2d _in, Matrix2d _out) {
		inputs = _in;
		outputs = _out;
	}
};

const double LearningRate = 0.01;
const int NumInputsNeurons = 8*2;
const int NumOutputsNeurons = 1;

const int NUM_HIDDEN_NEURONS = 32;
const int NUM_HIDDEN_LAYERS = 3;

class NeuroNet {
protected:
	int num_layers;
	vector<Layer> layers;
	int num_inputs;
	int num_outputs;
	Matrix2d outputs;
public:
	NeuroNet();
	NeuroNet(int ninputs, int nlayers, vector<int> nlneurons, vector<ActFuncTypes> _aft, int noutputs);

	void Init(int ninputs, int nlayers, vector<int> nlneurons, vector<ActFuncTypes> _aft, int noutputs, vector<Matrix2d> _biases, vector<Matrix2d> _waights);

	void AddTest(queue<Test>& ts, vector<vector<double>> exp_out);
	void AddTest(queue<Test>& ts, Matrix2d exp_out);

	void Running(Test& test);
	double RunningLearningOffline(vector<Test> & tests);
	double RunningLearningOffline(queue<Test> tests);
	void PrintWaightsAndBiases(bool print_null);

	Matrix2d GetOutput();
	void CalcDeltaAndGrad(Test& test);
	void CorrectWaightsAndBiases(vector<Matrix2d>& _gradient, vector<Matrix2d>& _delta);

	friend ostream& operator << (ostream& out, NeuroNet& _nnet);
};