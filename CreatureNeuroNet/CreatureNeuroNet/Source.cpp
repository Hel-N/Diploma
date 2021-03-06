#pragma comment(lib, "glut32.lib")
#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
#include "glut.h"
#include "Creature.h"
#include "NeuroNet.h"
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <string>
#include <ctime>

using namespace std;
int cou = 0;
const int WinWidth = 840;
const int WinHeight = 500;

int ground_height = 200;

//const double ALPHA = 0.5;
//const double GAMMA = 0.5;
//const double LAMBDA = 0.5;

const int EPOCH = 50;
const double TRAIN_EPS = 0.01;
const double QGAMMA = 0.9; // ����������� �������
Matrix2d Q;
Matrix2d prevQ;
int prevAction;
bool firstStep = true;

double prev_dist = 0.0;

vector<vector<double>> inputs;
Matrix2d prev_inputs;

Creature monster;
NeuroNet nnet;

queue<Test> tests;
vector<vector<double>> best_res(1, vector<double>(1, 0.0));

void Timer(int val = 0);
void Draw();
void Display();
void DoNextStep();
void CreatureInitialization();

//=====================
void glEnter2D(void);
void glLeave2D(void);
void glWrite(float x, float y, int *font, string s);

//=====================

int main(int argc, char** ardv) {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	srand(time(NULL));
	//������������� ��������
	CreatureInitialization();

	vector<int> num_neurons = { NUM_HIDDEN_NEURONS, NUM_HIDDEN_NEURONS, monster.GetNumActions() };
	vector<ActFuncTypes> aft = { TANH, TANH, LINE };
	nnet = NeuroNet(NumInputsNeurons, NUM_HIDDEN_LAYERS, num_neurons, aft, monster.GetNumActions());

	// ���������� ����� � ��������
	vector<Matrix2d> weights;
	for (int i = 0; i < NUM_HIDDEN_LAYERS; ++i) {
		Matrix2d _w;
		if (i == 0)
			_w = Matrix2d(NumInputsNeurons, num_neurons[i]);
		else
			_w = Matrix2d(num_neurons[i - 1], num_neurons[i]);
		for (int j = 0; j < _w.GetNumRows(); ++j) {
			for (int k = 0; k < _w.GetNumCols(); ++k) {
				double tmp;
				cin >> tmp;
				_w(j, k) = tmp;
			}
		}
		weights.push_back(_w);
	}

	vector<Matrix2d> biases;
	for (int i = 0; i < NUM_HIDDEN_LAYERS; ++i) {
		Matrix2d _b;

		_b = Matrix2d(1, num_neurons[i]);
		for (int j = 0; j < _b.GetNumRows(); ++j) {
			for (int k = 0; k < _b.GetNumCols(); ++k) {
				double tmp;
				cin >> tmp;
				_b(j, k) = tmp;
			}
		}
		biases.push_back(_b);
	}

	//��������� ����� � ��������---------------------------------------------------
	//nnet.SetWeights(weights);
	//nnet.SetBiases(biases);
	//-------------------------------------------------------------------

	int num_inp = 2 * monster.GetJoints().size();
	inputs.resize(1, vector<double>(num_inp));

	glutInit(&argc, ardv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WinWidth, WinHeight);
	glutInitWindowPosition(20, 20);
	glutCreateWindow("Test_1");
	glClearColor(0, 0, 0, 1.0); // ���� ������� ������ RGBAlpha

	glMatrixMode(GL_PROJECTION);//????
	glLoadIdentity(); //????
	gluOrtho2D(0, WinWidth, 0, WinHeight); // ������������� ������� ��������� (3D ��������� ������� ���������)


	glutDisplayFunc(Display);
	glutTimerFunc(50, Timer, 0);

	glutMainLoop(); // ������ ��������� ����� OpenGL
}

void CreatureInitialization() {
	vector<pair<double, double>> joints = {
		make_pair(50.0, 150.0), make_pair(100.0, 150.0),
		make_pair(50.0, 100.0), make_pair(100.0, 100.0),
		make_pair(0.0, 50.0), make_pair(150.0, 50.0),
		make_pair(50.0, 0.0), make_pair(100.0, 0.0)
	};

	vector<pair<int, int>> lines = {
		make_pair(2, 4), make_pair(3, 5),
		make_pair(4, 6), make_pair(5, 7),
		make_pair(0, 1), make_pair(1, 3),
		make_pair(2, 3), make_pair(0, 2),
		make_pair(1, 2), make_pair(0, 3)
	};

	vector<pair<int, int>> mvlines = {
		make_pair(0, 2), make_pair(1, 3),
		make_pair(2, 4), make_pair(3, 5)
	};

	vector<pair<double, double>> turnint = {
		make_pair(3.0*M_PI / 4.0, 7.0*M_PI / 4.0),
		make_pair(5.0*M_PI / 4.0, 9.0*M_PI / 4.0),
		make_pair(5.0*M_PI / 4.0, 7.0*M_PI / 4.0),
		make_pair(5.0*M_PI / 4.0, 7.0*M_PI / 4.0),
		make_pair(0.0, 0.0),
		make_pair(0.0, 0.0),
		make_pair(0.0, 0.0),
		make_pair(0.0, 0.0),
		make_pair(0.0, 0.0),
		make_pair(0.0, 0.0)
	};

	vector<int> mvstates = { monster.GetNumStates() / 2, monster.GetNumStates() / 2, monster.GetNumStates() - 1, 0, -1, -1, -1, -1, -1, -1 };

	vector<vector<int>> refs(10);
	refs[0].push_back(2);
	refs[1].push_back(3);

	monster.InitCreature(joints, lines, mvlines, turnint, mvstates, refs);
}

void Draw() {

	// ������ ����������
	glEnter2D();
	string tmps = to_string(cou) + "  dist: " + to_string(monster.GetCurDeltaDistance());
	glWrite(20, 20, (int*)GLUT_BITMAP_8_BY_13, tmps);
	string spos = "XPos: " + to_string(monster.GetCenterOfGravity());
	glWrite(20, 40, (int*)GLUT_BITMAP_8_BY_13, spos);
	//glLeave2D();

	glBegin(GL_LINES);
	// ground
	glVertex2f(0.0, ground_height);
	glVertex2f(WinWidth, ground_height);

	double dx = 0.0;
	vector<double> xx;
	vector<Line> lines = monster.GetLines();

	for (int i = 0; i < lines.size(); ++i) {
		xx.push_back(lines[i].a.x);
		xx.push_back(lines[i].b.x);
	}
	sort(xx.begin(), xx.end());

	if (xx[0] + 100 < 0) {
		dx = fabs(xx[0] + 100);
	}
	else if (xx[xx.size() - 1] + 100 > WinWidth) {
		dx = -((int)(xx[xx.size() - 1] + 100) / WinWidth* WinWidth);
	}

	for (int i = 0; i < lines.size(); ++i) {
		glVertex2d(lines[i].a.x + 100 + dx, lines[i].a.y + ground_height);
		glVertex2d(lines[i].b.x + 100 + dx, lines[i].b.y + ground_height);
	}
	glEnd();
}

void Display() {
	glClear(GL_COLOR_BUFFER_BIT); // ������� �����
	Draw();

	glFlush(); // ������� �� ����� �����
	glutSwapBuffers();
}

void SetInputs(vector<vector<double>>& _in) {
	vector<pair<double, double>> cur_pos = monster.GetJoints();
	for (int i = 0, j = 0; i < cur_pos.size(); ++i, j += 2) {
		_in[0][j] = 1.0*cur_pos[i].first;
		_in[0][j + 1] = 1.0*cur_pos[i].second;
	}
}

void DoNextStep() {
	prev_inputs = inputs;
	SetInputs(inputs);
	int action = -1;
	//best_res[0][0] = monster.GetCurDeltaDistance();
	double reward = monster.GetCurDeltaDistance();
	prev_dist = monster.GetCurDeltaDistance();
	cou++;

	if (!firstStep) {

		nnet.Running(inputs);
		Q = nnet.GetOutput();

		double tmpQ = -DBL_MAX;
		for (int i = 0; i < Q.GetNumCols(); ++i) {
			if (tmpQ < Q(0, i) && monster.CanDoAction(i)) {
				tmpQ = Q(0, i);
				action = i;
			}
		}
		Q(0, prevAction) = reward + QGAMMA*tmpQ;

		nnet.AddTest(tests, prev_inputs, Q);
		int epoch = EPOCH;
		while (epoch--) {
			//if (nnet.RunningLearningOffline(tests) == 0.0)
			//	break;
			if (nnet.RPropLearningOffline(tests) < TRAIN_EPS) //�������� ������ ������ 
				break;
		}

	}
	else {  
		nnet.Running(inputs);
		Q = nnet.GetOutput();

		double tmpQ = -DBL_MAX;
		for (int i = 0; i < Q.GetNumCols(); ++i) {
			if (tmpQ < Q(0, i) && monster.CanDoAction(i)) {
				tmpQ = Q(0, i);
				action = i;
			}
		}

		firstStep = false;
	}

	monster.UpdatePos(action);
	if (fabs(prev_dist - monster.GetCurDeltaDistance()) < 0.01) {
		do {
			action = monster.GetNumActions()*rand() / RAND_MAX;
			if (monster.CanDoAction(action))
				break;
		} while (true);
		monster.UpdatePos(action);
	}
	prevAction = action;
	prevQ = Q;

	//����� ������� ����������
	cout << cou << "Current Delta Distance:  " << monster.GetCurDeltaDistance() << endl;

	if (cou % 50 == 0) {
		cout << "==================================================================================" << endl;
		nnet.PrintWeightsAndBiases(false);
		cout << "==================================================================================" << endl;
		monster.PrintCreatureJoints();
		cout << endl << endl;
	}
}

void Timer(int val) // ������(���������� �������, � ������� ����� ������������ ��� ��������) 
{
	Display();
	DoNextStep();
	glutTimerFunc(50, Timer, 0); // ����� ����� �������( 100 - ���������� �������(� ������������), ����� ������� �� ����� ���������, timer - ���������� ������) 
}

//===============================================
//��� ������ ������
void glEnter2D(void) {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST);
}

void glLeave2D(void) {
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glEnable(GL_DEPTH_TEST);
}

void glWrite(float x, float y, int *font, string s) {
	int i;
	glRasterPos2f(x, y);
	for (i = 0; i < s.length(); i++)
		glutBitmapCharacter(font, s[i]);
}