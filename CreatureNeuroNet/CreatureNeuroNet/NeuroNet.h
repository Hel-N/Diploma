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

const int NUM_HIDDEN_NEURONS = 100;
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

	void Init(int ninputs, int nlayers, vector<int> nlneurons, vector<ActFuncTypes> _aft, int noutputs, vector<Matrix2d> _biases, vector<Matrix2d> _weights);

	void AddTest(queue<Test>& ts, vector<vector<double>> _in, vector<vector<double>> _out);
	void AddTest(queue<Test>& ts, Matrix2d _in, Matrix2d _out);

	void Running(Test& test);
	void Running(vector<vector<double>>& inps);
	double RunningLearningOffline(vector<Test> & tests);
	double RunningLearningOffline(queue<Test> tests);
	void ResilientPropagation();
	double RPropLearningOffline(vector<Test> & tests);
	double RPropLearningOffline(queue<Test> tests);
	void PrintWeightsAndBiases(bool print_null);

	Matrix2d GetOutput();
	void CalcDeltaAndGrad(Test& test);
	double CalcError(Test& test);
	void CorrectWeightsAndBiases(vector<Matrix2d>& _gradient, vector<Matrix2d>& _delta);

	void SetWeights(vector<Matrix2d> _w);
	void SetBiases(vector<Matrix2d> _b);

	friend ostream& operator << (ostream& out, NeuroNet& _nnet);
};