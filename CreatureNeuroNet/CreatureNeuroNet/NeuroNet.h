#pragma once
#include "Layer.h"
#include "Matrix2d.h"
#include <vector>
#include <queue>
using namespace std;

extern int TOTAL_TESTS_NUMBER;
extern int CUR_TESTS_NUMBER;

enum TrainingTypes { RMS };
extern TrainingTypes TRAINING_TYPE;

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

extern double LearningRate;

extern int NUM_HIDDEN_NEURONS;
extern int NUM_HIDDEN_LAYERS;
extern ActFuncTypes ACT_FUNC;

//For RMS
extern double RMS_GAMMA;
extern double RMS_LEARN_RATE;
extern double RMS_EPS;


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

	void AddTest(deque<Test>& ts, vector<vector<double>> _in, vector<vector<double>> _out);
	void AddTest(deque<Test>& ts, Matrix2d _in, Matrix2d _out);

	void Running(Test& test);
	void Running(vector<vector<double>>& inps);
	double RunningLearningOffline(deque<Test> & tests, vector<int>& tests_pos);
	//double RunningLearningOffline(queue<Test> tests);
	void ResilientPropagation();
	double RPropLearningOffline(deque<Test> & tests, vector<int>& tests_pos);
	//double RPropLearningOffline(queue<Test> tests);
	void RMSPropagation();
	double RMSLearningOffline(deque<Test> & tests, vector<int>& tests_pos);
	//double RMSLearningOffline(queue<Test> tests);

	void PrintWeightsAndBiases(ostream& fout, bool print_null);

	Matrix2d GetOutput();
	void CalcDeltaAndGrad(Test& test);
	double CalcError(Test& test);
	void CorrectWeightsAndBiases(vector<Matrix2d>& _gradient, vector<Matrix2d>& _delta);

	void SetWeights(vector<Matrix2d> _w);
	void SetBiases(vector<Matrix2d> _b);

	friend ostream& operator << (ostream& out, NeuroNet& _nnet);
};