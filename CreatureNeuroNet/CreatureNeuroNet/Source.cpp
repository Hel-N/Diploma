#pragma comment(lib, "glut32.lib")
#define _USE_MATH_DEFINES
#include "glut.h"
#include "Creature.h"
#include "NeuroNet.h"
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

const int WinWidth = 840;
const int WinHeight = 500;

int ground_height = 200;

const double ALPHA = 0.5;
const double GAMMA = 0.5;
//const double LAMBDA = 0.5;

const int EPOCH = 10;
const int TRAIN_EPS = 0.01;

double Q;
double prevQ = 0.0;
int prevAction;
bool firstStep = true;

Creature monster;
vector<NeuroNet> nnets;

queue<Test> tests;
vector<vector<double>> best_res(1, vector<double>(1, 0.0));

void Timer(int val = 0);
void Draw();
void Display();
void DoNextStep();
void CreatureInitialization();

int main(int argc, char** ardv) {

	//Инициализация существа
	CreatureInitialization();
	nnets.resize(monster.GetNumActions());

	for (int i = 0; i < nnets.size(); ++i) {
		vector<int> num_neurons = { NUM_HIDDEN_NEURONS, NUM_HIDDEN_NEURONS, 1};
		vector<ActFuncTypes> aft = {TANH, TANH, LINE};
		nnets[i] = NeuroNet(NumInputsNeurons, NUM_HIDDEN_LAYERS, num_neurons, aft, NumOutputsNeurons);
	}

	glutInit(&argc, ardv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WinWidth, WinHeight);
	glutInitWindowPosition(20, 20);
	glutCreateWindow("Test_1");
	glClearColor(0, 0, 0, 1.0); // цвет очистки экрана RGBAlpha

	glMatrixMode(GL_PROJECTION);//????
	glLoadIdentity(); //????
	gluOrtho2D(0, WinWidth, 0, WinHeight); // Ортогональная система координат (3D декартова система координат)


	glutDisplayFunc(Display);
	glutTimerFunc(50, Timer, 0);

	glutMainLoop(); // Запуск основного цикла OpenGL
}

void CreatureInitialization() {
	vector<pair<int, int>> joints = {
		make_pair(50, 150), make_pair(100, 150),
		make_pair(50, 100), make_pair(100, 100),
		make_pair(0, 50), make_pair(150, 50),
		make_pair(50, 0), make_pair(100, 0)
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
		make_pair(5.0*M_PI / 4.0, 7.0*M_PI / 4.0)
	};

	vector<int> mvstates = {3, 3, 6, 0};

	vector<vector<int>> refs(10);
	refs[0].push_back(2);
	refs[1].push_back(3);

	monster.InitCreature(joints, lines, mvlines, turnint, mvstates, refs);
}

void Draw() {
	glBegin(GL_LINES);
	// ground
	glVertex2f(0.0, ground_height);
	glVertex2f(WinWidth, ground_height);
	
	vector<Line> lines = monster.GetLines();
	for (int i = 0; i < lines.size(); ++i) {
		glVertex2f(lines[i].a.x + 100, lines[i].a.y + ground_height);
		glVertex2f(lines[i].b.x + 100, lines[i].b.y + ground_height);
	}
	glEnd();
}

void Display() {
	glClear(GL_COLOR_BUFFER_BIT); // Очищает экран
	Draw();

	glFlush(); // Выводит на экран буфер
	glutSwapBuffers();
}

void SetInputs(vector<vector<double>>& _in) {
	vector<pair<int, int>> cur_pos = monster.GetJoints();
	for (int i = 0; i < cur_pos.size(); ++i) {
		_in[0].push_back(1.0*cur_pos[i].first);
		_in[0].push_back(1.0*cur_pos[i].second);
	}
}

void DoNextStep() {
	vector<vector<double>> inputs(1);
	SetInputs(inputs);
	int action = -1;
	best_res[0][0] = monster.GetCurDeltaDistance();

	if (!firstStep) {
		nnets[prevAction].AddTest(tests, best_res);
		int epoch = EPOCH;
		while (epoch--) {
			if (nnets[prevAction].RunningLearningOffline(tests) == 0.0 /*< TRAIN_EPS*/) //Добавить расчет ошибки 
				break;
		}

		Q = -DBL_MAX;
		for (int i = 0; i < nnets.size(); ++i) {
			nnets[i].Running(tests.back());
			double q = nnets[i].GetOutput().SumAll();
			if (Q < q && monster.CanDoAction(i)) {
				Q = q;
				action = i;
			}
		}
	}
	else {
		Q = best_res[0][0];
		action = monster.GetNumActions()*(rand() / RAND_MAX);
	}

	monster.UpdatePos(action);
	firstStep = false;
	prevAction = action;
	prevQ = Q;

	//Вывод текущей информации
}

void Timer(int val) // Таймер(промежуток времени, в котором будет производится все процессы) 
{
	Display();
	DoNextStep();
	glutTimerFunc(100, Timer, 0); // новый вызов таймера( 100 - промежуток времени(в милисекундах), через который он будет вызыватся, timer - вызываемый паблик) 
}
