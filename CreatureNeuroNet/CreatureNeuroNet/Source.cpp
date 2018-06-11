#pragma comment(lib, "glut32.lib")
#pragma comment(lib, "glaux.lib")
#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
#include "glut.h"
#include "glaux.h"
#include "Creature.h"
#include "NeuroNet.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <cmath>
#include <string>
#include <ctime>

#define FILENAME "Creature.txt"

ofstream fout("weights_and_biases.txt");
ofstream cfout("cur_creature.txt");

using namespace std;

//��� ��������� ����-------
double DeltaX = 0.0;
GLuint texture;
//-------------------------


double reward = 0.0;
double prev_pos = 0.0;
int side = 0.0;
int change_side_count = 0;

int cur_tick = 0;
const int WinWidth = 1200;
const int WinHeight = 450;

double ground_height = 40.0;

const int EPOCH = 10;
const double TRAIN_EPS = 0.001;
const double QGAMMA = 0.9; // ����������� �������
const double TICK_COUNT = 10000;

Matrix2d Q;
Matrix2d prevQ;
int prevAction;
bool firstStep = true;

double prev_dist = 0.0;

vector<vector<double>> inputs;
Matrix2d prev_inputs;

Creature monster;
NeuroNet nnet;

deque<Test> tests;
vector<vector<double>> best_res(1, vector<double>(1, 0.0));

void Timer(int val = 0);
void Draw();
void Display();
void DoNextStep();
void CreatureInitialization();
void CreatureInitializationFromFile();

//=====================
void glEnter2D(void);
void glLeave2D(void);
void glWrite(float x, float y, int *font, string s);

void LoadTexture();
void DrawBackground();

//=====================

int main(int argc, char** ardv) {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	ios::sync_with_stdio(false);

	srand(time(NULL));
	//������������� ��������
	CreatureInitializationFromFile();
	//CreatureInitialization();

	vector<int> num_neurons = { NUM_HIDDEN_NEURONS, NUM_HIDDEN_NEURONS, monster.GetNumActions() };
	vector<ActFuncTypes> aft = { TANH, TANH, LINE };
	nnet = NeuroNet(2*monster.GetNumJoints(), NUM_HIDDEN_LAYERS, num_neurons, aft, monster.GetNumActions());

	// ���������� ����� � ��������
	vector<Matrix2d> weights;
	for (int i = 0; i < NUM_HIDDEN_LAYERS; ++i) {
		Matrix2d _w;
		if (i == 0)
			_w = Matrix2d(2*monster.GetNumJoints(), num_neurons[i]);
		else
			_w = Matrix2d(num_neurons[i - 1], num_neurons[i]);
		for (int j = 0; j < _w.GetNumRows(); ++j) {
			for (int k = 0; k < _w.GetNumCols(); ++k) {
				double tmp;
				cin >> tmp;
				_w.at(j, k) = tmp;
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
				_b.at(j, k) = tmp;
			}
		}
		biases.push_back(_b);
	}

	//��������� ����� � ��������---------------------------------------------------
	//nnet.SetWeights(weights);
	//nnet.SetBiases(biases);
	//-------------------------------------------------------------------

	//nnet.PrintWeightsAndBiases(fout, false);

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
	glutTimerFunc(70, Timer, 0);

	LoadTexture();

	glutMainLoop(); // ������ ��������� ����� OpenGL
}

void CreatureInitialization() {
	vector<pair<double, double>> joints = {
		make_pair(50.0, 150.0), make_pair(100.0, 150.0),
		make_pair(50.0, 100.0), make_pair(100.0, 100.0),
		make_pair(0.0, 50.0), make_pair(150.0, 50.0),
		make_pair(50.0, 0.0), make_pair(100.0, 0.0),
		make_pair(0.0, 200.0), make_pair(150.0, 200.0),
		make_pair(0.0, 150.0), make_pair(150.0, 150.0),

		//������ ������ �����������!!!!!!!!!!!!!!!!����� ��� ��������
		make_pair(60.0, 150.0), make_pair(90.0, 150.0),
		make_pair(60.0, 180.0), make_pair(90.0, 180.0),
	};

	vector<pair<int, int>> lines = {
		make_pair(2, 4), make_pair(3, 5),
		make_pair(4, 6), make_pair(5, 7),
		make_pair(0, 1), make_pair(1, 3),
		make_pair(2, 3), make_pair(0, 2),
		make_pair(1, 2), make_pair(0, 3),
		make_pair(0, 8), make_pair(1, 9),
		make_pair(8, 10), make_pair(9, 11),

		//������
		make_pair(12, 14), make_pair(13, 15), make_pair(14, 15)
	};

	vector<pair<int, int>> mvlines = {
		make_pair(0, 2), make_pair(1, 3),
		make_pair(2, 4), make_pair(3, 5),
		make_pair(10, 0), make_pair(11, 1),
		make_pair(12, 8), make_pair(13, 9)
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
		make_pair(0.0, 0.0),
		make_pair(2.0*M_PI / 4.0, 6.0*M_PI / 4.0),
		make_pair(6.0*M_PI / 4.0, 10.0*M_PI / 4.0),
		make_pair(2.0*M_PI / 4.0, 6.0*M_PI / 4.0),
		make_pair(6.0*M_PI / 4.0, 10.0*M_PI / 4.0),

		// ������
		make_pair(0.0, 0.0),
		make_pair(0.0, 0.0),
		make_pair(0.0, 0.0)
	};

	vector<pair<int, int>> mvstates = {
		make_pair(9, 19),
		make_pair(9, 19),
		make_pair(9, 10),
		make_pair(0, 10),
		make_pair(-1, 0), make_pair(-1, 0), make_pair(-1, 0), make_pair(-1, 0), make_pair(-1, 0), make_pair(-1, 0),
		make_pair(9, 19),
		make_pair(9, 19),
		make_pair(9, 19),
		make_pair(0, 19),
		// ������
		make_pair(-1, 0), make_pair(-1, 0), make_pair(-1, 0)
	};

	vector<vector<int>> refs(16);
	refs[0].push_back(2);
	refs[1].push_back(3);
	refs[10].push_back(12);
	refs[11].push_back(13);

	monster.InitCreature(joints, lines, mvlines, turnint, mvstates, refs);
	monster.SetFallUnitAngle(M_PI / 18.0);
	monster.SetTurnUnitAngle(M_PI / 18.0);
}

void CreatureInitializationFromFile() {
	ifstream fin(FILENAME);
	if (fin.is_open()) {
		vector<pair<double, double>> joints;
		string s;
		getline(fin, s);
		int joint_count;
		fin >> joint_count;
		joints.resize(joint_count);
		for (int i = 0; i < joints.size(); ++i) {
			fin >> joints[i].first >> joints[i].second;
		}

		vector<pair<int, int>> lines;
		getline(fin, s);
		if (s == "") getline(fin, s);
		int line_count;
		fin >> line_count;
		lines.resize(line_count);
		for (int i = 0; i < lines.size(); ++i) {
			fin >> lines[i].first >> lines[i].second;
		}

		vector<pair<int, int>> mvlines;
		getline(fin, s);
		if (s == "") getline(fin, s);
		int mvline_count;
		fin >> mvline_count;
		mvlines.resize(mvline_count);
		for (int i = 0; i < mvlines.size(); ++i) {
			fin >> mvlines[i].first >> mvlines[i].second;
		}

		double fall_unit_angle;
		double turn_unit_angle;
		getline(fin, s);
		if (s == "") getline(fin, s);
		fin >> fall_unit_angle;
		getline(fin, s);
		if (s == "") getline(fin, s);
		fin >> turn_unit_angle;

		vector<pair<double, double>> turnints;
		getline(fin, s);
		if (s == "") getline(fin, s);
		int turnint_count;
		fin >> turnint_count;
		turnints.resize(turnint_count);
		for (int i = 0; i < turnints.size(); ++i) {
			fin >> turnints[i].first >> turnints[i].second;
		}

		vector<pair<int, int>> mvstates;
		getline(fin, s);
		if (s == "") getline(fin, s);
		int mvstate_count;
		fin >> mvstate_count;
		mvstates.resize(mvstate_count);
		for (int i = 0; i < mvstates.size(); ++i) {
			fin >> mvstates[i].first >> mvstates[i].second;
		}

		vector<vector<int>> refs;
		getline(fin, s);
		if (s == "") getline(fin, s);
		int refs_count;
		fin >> refs_count;
		refs.resize(refs_count);
		for (int i = 0; i < refs.size(); ++i) {
			int rcou;
			fin >> rcou;
			refs[i].resize(rcou);
			for (int j = 0; j < refs[i].size(); ++j) {
				fin >> refs[i][j];
			}
		}

		monster.InitCreature(joints, lines, mvlines, turnints, mvstates, refs);
		monster.SetFallUnitAngle(fall_unit_angle);
		monster.SetTurnUnitAngle(turn_unit_angle);

		prev_pos = monster.GetCenterOfGravity();

		fin.close();
	}
	else {
		exit(0);
	}
}

void DrawBackground() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);

	glBegin(GL_QUADS);
	glTexCoord2f(DeltaX / WinWidth, 0.0); // �� 0 �� 1
	glVertex2f(0, 0);

	glTexCoord2f(1.0, 0.0); // �� 0 �� 1
	glVertex2f(WinWidth - DeltaX, 0);

	glTexCoord2f(1.0, 1.0); // �� 0 �� 1
	glVertex2f(WinWidth - DeltaX, WinHeight);

	glTexCoord2f(DeltaX / WinWidth, 1.0); // �� 0 �� 1
	glVertex2f(0, WinHeight);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); // �� 0 �� 1
	glVertex2f(WinWidth - DeltaX, 0);

	glTexCoord2f(DeltaX / WinWidth, 0.0); // �� 0 �� 1
	glVertex2f(WinWidth, 0);

	glTexCoord2f(DeltaX / WinWidth, 1.0); // �� 0 �� 1
	glVertex2f(WinWidth, WinHeight);

	glTexCoord2f(0.0, 1.0); // �� 0 �� 1
	glVertex2f(WinWidth - DeltaX, WinHeight);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void Draw() {
	int tmp = monster.GetCenterOfGravity() / WinWidth;
	DeltaX = monster.GetCenterOfGravity() - tmp*WinWidth;
	DrawBackground();

	DeltaX = monster.GetCurDeltaDistance();

	// ������ ����������
	glColor3d(0.0, 0.0, 0.0);
	glEnter2D();
	string tmps = to_string(cur_tick) + "  dist: " + to_string(monster.GetCurDeltaDistance());
	glWrite(20, WinHeight - 80, (int*)GLUT_BITMAP_8_BY_13, tmps);
	string spos = "XPos: " + to_string(monster.GetCenterOfGravity()) + " YPos: " + to_string(monster.GetCenterOfGravityY());
	glWrite(20, WinHeight - 60, (int*)GLUT_BITMAP_8_BY_13, spos);


	vector<pair<int, int>> line_states = monster.GetCurLinesStates();
	string sstates = "";
	for (int i = 0; i < line_states.size(); ++i) {
		sstates += to_string(line_states[i].first) + "/" + to_string(line_states[i].second - 1) + " ";
	}
	glWrite(20, WinHeight - 40, (int*)GLUT_BITMAP_8_BY_13, sstates);

	string rewstr = "Rew: " + to_string(reward);
	glWrite(20, WinHeight - 20, (int*)GLUT_BITMAP_8_BY_13, rewstr);

	glBegin(GL_LINES);
	// ground
	glColor3d(0.02, 0.39, 0.176);
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

	//if (xx[0] + 100 < 0) {
	//	dx = fabs(xx[0] + 100);
	//}
	//else if (xx[xx.size() - 1] + 100 > WinWidth) {
	//	dx = -xx[0];
	//}
	glEnd();

	glLineWidth(2);
	glColor3d(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	// center of gravity
	double cgy = monster.GetCenterOfGravityY();
	double cg = monster.GetCenterOfGravity();
	glVertex2f(cg + 100.0 + dx - DeltaX, cgy + ground_height - 10);
	glVertex2f(cg + 100.0 + dx - DeltaX, cgy + ground_height + 10);

	glVertex2f(cg + 100.0 + dx - 10.0 - DeltaX, cgy + ground_height);
	glVertex2f(cg + 100.0 + dx + 10.0 - DeltaX, cgy + ground_height);
	glEnd();

	glColor3d(0.0, 0.0, 0.0);
	glEnable(GL_LINE_SMOOTH);
	glLineWidth(2);
	glBegin(GL_LINES);
	for (int i = 0; i < lines.size(); ++i) {
		glVertex2d(lines[i].a.x + 100 + dx - DeltaX, lines[i].a.y + ground_height);
		glVertex2d(lines[i].b.x + 100 + dx - DeltaX, lines[i].b.y + ground_height);
	}
	glEnd();
	glDisable(GL_LINE_SMOOTH);
	glLineWidth(1);

	glEnable(GL_POINT_SMOOTH);
	glPointSize(7);
	glBegin(GL_POINTS);
	for (int i = 0; i < lines.size(); ++i) {
		glVertex2d(lines[i].a.x + 100 + dx - DeltaX, lines[i].a.y + ground_height);
		glVertex2d(lines[i].b.x + 100 + dx - DeltaX, lines[i].b.y + ground_height);
	}
	glEnd();
	glPointSize(1);
	glColor3d(1.0, 1.0, 1.0);

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
	reward = 0.0;
	reward = fabs(prev_dist - monster.GetCurDeltaDistance());
	//reward = monster.GetCurDeltaDistance() - prev_dist;
	//reward = fabs(fabs(prev_dist) - fabs(monster.GetCurDeltaDistance())) /*- 10.0 / monster.GetCenterOfGravityY()*/;
	//reward = fabs(monster.GetCurDeltaDistance()) - monster.GetFalling()*10.0/* - 50.0/monster.GetCenterOfGravityY()*/;
	prev_dist = monster.GetCurDeltaDistance();
	//double reward = monster.GetTraveledDistance();
	//prev_dist = reward;
	cur_tick++;

	double delta_rew_side = 0.0;
	double cg = monster.GetCenterOfGravity();

	if (side == 1) {
		if ((cg - prev_dist) < 0) {
			//delta_rew_side = 5.0; 
			change_side_count++;
		}
	}
	else if (side == -1) {
		if ((cg - prev_dist) > 0) {
			//delta_rew_side = 5.0; 
			change_side_count++;
		}
	}

	reward -= 1000.0*(change_side_count / cur_tick);

	prev_pos = monster.GetCenterOfGravity();

	bool fl = false;
	if (!firstStep) {
		fl = true;
		nnet.Running(inputs);
		Q = nnet.GetOutput();

		double tmpQ = -DBL_MAX;
		for (int i = 0; i < Q.GetNumCols(); ++i) {
			if (tmpQ < Q.at(0, i) && monster.CanDoAction(i)) {
				tmpQ = Q.at(0, i);
				action = i;
			}
		}
		Q.at(0, prevAction) = reward + QGAMMA*tmpQ;

		nnet.AddTest(tests, prev_inputs, Q);
		int epoch = EPOCH;
		vector<int> tests_pos;
		for (int i = 0; i < CUR_TESTS_NUMBER; ++i) {
			int pos = max(0, (tests.size() - 1))*(double)rand() / RAND_MAX;
			tests_pos.push_back(pos);
		}
		while (epoch--) {
			//if (nnet.RunningLearningOffline(tests) == 0.0)
			//	break;
			//if (nnet.RPropLearningOffline(tests) < TRAIN_EPS) //�������� ������ ������ 
			//	break;
			if (nnet.RMSLearningOffline(tests, tests_pos) < TRAIN_EPS) //�������� ������ ������ 
				break;
		}

	}
	else {
		nnet.Running(inputs);
		Q = nnet.GetOutput();

		double tmpQ = -DBL_MAX;
		for (int i = 0; i < Q.GetNumCols(); ++i) {
			if ((tmpQ < Q.at(0, i)) && monster.CanDoAction(i)) {
				tmpQ = Q.at(0, i);
				action = i;
			}
		}

		firstStep = false;
	}

	monster.UpdatePos(action);
	if (fabs(prev_dist - /*monster.GetTraveledDistance()*/monster.GetCurDeltaDistance()) < 7.0) {
		do {
			action = monster.GetNumActions()*rand() / RAND_MAX;
			if (monster.CanDoAction(action))
				break;
		} while (true);
		monster.UpdatePos(action);
	}
	prevAction = action;
	prevQ = Q;

	if (side == 0) {
		if (cg - prev_dist > 0) {
			side = 1;
		}
		else {
			side = -1;
		}
	}

	//����� ������� ����������
	cout << cur_tick << "  " << monster.GetCurDeltaDistance() << endl;
	//cout << cou << "Current Delta Distance:  " << (monster.GetTraveledDistance()) << endl;

	if (cur_tick % 100 == 0) {
		fout << "==================================================================================" << endl;
		nnet.PrintWeightsAndBiases(fout, false);
		fout << "==================================================================================" << endl;
		fout << endl << endl;
		cfout << "==================================================================================" << endl;
		monster.PrintCreatureJoints(cfout);
		cfout << "==================================================================================" << endl;
		cfout << endl << endl;
	}

	fflush(stdout);
	fout.flush();
}

void Timer(int val) // ������(���������� �������, � ������� ����� ������������ ��� ��������) 
{
	Display();
	DoNextStep();

	if (cur_tick < TICK_COUNT)
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

//��� ����
void LoadTexture() {
	AUX_RGBImageRec *texture1 = auxDIBImageLoadA("4.bmp");
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->sizeX, texture1->sizeY,
		0, GL_RGB, GL_UNSIGNED_BYTE, texture1->data);
}