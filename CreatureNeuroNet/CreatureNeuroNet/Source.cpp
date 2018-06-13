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
#include <direct.h>

#define INIT_TRAIN		1
#define CONTINUE_TRAIN	2
#define RUN				3

using namespace std;

//ofstream fout;
//ofstream cfout;
ofstream logout("log.txt");

string res_dir_str = "Res\\";
string wb_finame_end = "_weights_and_biases.txt";
string curcr_finame_end = "_cur_creature.txt";
string dist_finame_end = "_dist.txt";
string run_dist_finame_end = "_run_dist.txt";

string nnets_dir_str = "NNets\\";
string creatures_dir_str = "Creatures\\";
string nnet_finame_end = "_nnet.txt";
string creature_finame_end = "_creature.txt";

//NNet Config------------------------------------------------------
string nnet_name = "";
string creature_name = "";
int run_type = INIT_TRAIN; //1 - InitTrain, 2 - ContinueTrain, 3 - Run
int NUM_HIDDEN_LAYERS = 3;
int NUM_HIDDEN_NEURONS = 100;
ActFuncTypes ACT_FUNC = TANH;
int TOTAL_TESTS_NUMBER = 10000;
int CUR_TESTS_NUMBER = 20;
int EPOCH = 10;
TrainingTypes TRAINING_TYPE = RMS;

//For RMS
double RMS_GAMMA = 0.95;
double RMS_LEARN_RATE = 0.001;
double RMS_EPS = 1e-8;

double QGAMMA = 0.9; // Коэффициент доверия
double TICK_COUNT = 10000;
double TRAIN_EPS = 0.001;

double LearningRate = 0.01; // Для алгоритма обратного распространения

int T = 100; //Период печати весов
//-----------------------------------------------------------------

//Для отрисовки окна и фона-----------------------------------------------
const int WinWidth = 1200;
const int WinHeight = 450;
double ground_height = 40.0;

//Фон
double DeltaX = 0.0;
GLuint texture;
//-----------------------------------------------------------------

double reward = 0.0;
double prev_dist = 0.0;
int cur_tick = 0;

double prev_pos = 0.0;
int side = 0.0;
int change_side_count = 0;

Matrix2d Q;
Matrix2d prevQ;
int prevAction;
bool firstStep = true;

vector<vector<double>> inputs;
Matrix2d prev_inputs;

Creature monster;
NeuroNet nnet;

deque<Test> tests;

void Timer(int val = 0);
void Draw();
void Display();
void DoNextStep();
void CreatureInitialization();
void CreatureInitializationFromFile(string filename);
void NNetInitializationFromFile(string filename);
void SetWeigntsAndBiases(string filename, vector<int> num_neurons);
void SetJointsAndStates(string filename);
void SetCurTick(string filename);

//=====================
//Текст
void glEnter2D(void);
void glLeave2D(void);
void glWrite(float x, float y, int *font, string s);

//Фон
void LoadTexture();
void DrawBackground();

//=====================

int main(int argc, char** ardv) {
	ios::sync_with_stdio(false);
	srand(time(NULL));

	time_t seconds = time(NULL);
	tm* timeinfo = localtime(&seconds);
	if (argc < 3) {
		logout << asctime(timeinfo) << " Недостаточно входных параметров" << endl;
		exit(0);
	}

	seconds = time(NULL);
	timeinfo = localtime(&seconds);
	logout << asctime(timeinfo) << " Arguments: ";
	for (int i = 0; i < argc; ++i) {

		logout << ardv[i] << " ";
	}
	logout << endl;

	// Чтение сети
	nnet_name = ardv[1];
	string nnfilename = nnets_dir_str + nnet_name + nnet_finame_end;
	NNetInitializationFromFile(nnfilename);

	//Инициализация существа
	string crfilename = creatures_dir_str + creature_name + creature_finame_end;
	CreatureInitializationFromFile(crfilename);
	//CreatureInitialization();

	//Создание папки Res
	_mkdir(res_dir_str.c_str());

	//Создание папки для результтов существа
	string dirname = res_dir_str + nnet_name;
	_mkdir(dirname.c_str());

	vector<int> num_neurons = { NUM_HIDDEN_NEURONS, NUM_HIDDEN_NEURONS, monster.GetNumActions() };
	vector<ActFuncTypes> aft = { ACT_FUNC, ACT_FUNC, LINE };
	nnet = NeuroNet(2 * monster.GetNumJoints(), NUM_HIDDEN_LAYERS + 1, num_neurons, aft, monster.GetNumActions());

	run_type = atoi(ardv[2]);
	if (run_type == CONTINUE_TRAIN || run_type == RUN) {
		SetWeigntsAndBiases(dirname + "\\" + nnet_name + wb_finame_end, num_neurons);
	}

	if (run_type == CONTINUE_TRAIN) {
		SetJointsAndStates(dirname + "\\" + nnet_name + curcr_finame_end);
		SetCurTick(dirname + "\\" + nnet_name + dist_finame_end);
	}

	string resdistfname = dirname + "\\" + nnet_name + dist_finame_end;
	string resrundistfname = dirname + "\\" + nnet_name + run_dist_finame_end;
	if (run_type == INIT_TRAIN) {
		freopen(resdistfname.c_str(), "w", stdout);
	}else if (run_type == CONTINUE_TRAIN) {
		freopen(resdistfname.c_str(), "a", stdout);
	}
	else if (run_type == RUN) {
		freopen(resrundistfname.c_str(), "w", stdout);
	}

	//Вывод начального состояния
	ofstream wbfout(dirname + "\\" + nnet_name + wb_finame_end);
	nnet.PrintWeightsAndBiases(wbfout, false);
	wbfout.close();
	ofstream crfout(dirname + "\\" + nnet_name + curcr_finame_end);
	monster.PrintCreatureJoints(crfout);
	crfout.close();

	int num_inp = 2 * monster.GetJoints().size();
	inputs.resize(1, vector<double>(num_inp));

	glutInit(&argc, ardv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WinWidth, WinHeight);
	glutInitWindowPosition(20, 20);
	glutCreateWindow(nnet_name.c_str());
	glClearColor(0, 0, 0, 1.0); // цвет очистки экрана RGBAlpha

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, WinWidth, 0, WinHeight); // Ортогональная система координат

	glutDisplayFunc(Display);
	glutTimerFunc(70, Timer, 0);

	LoadTexture();

	glutMainLoop(); // Запуск основного цикла OpenGL
}

void CreatureInitialization() {
	vector<pair<double, double>> joints = {
		make_pair(50.0, 150.0), make_pair(100.0, 150.0),
		make_pair(50.0, 100.0), make_pair(100.0, 100.0),
		make_pair(0.0, 50.0), make_pair(150.0, 50.0),
		make_pair(50.0, 0.0), make_pair(100.0, 0.0),
		make_pair(0.0, 200.0), make_pair(150.0, 200.0),
		make_pair(0.0, 150.0), make_pair(150.0, 150.0),

		//Голова задана неправильно!!!!!!!!!!!!!!!!Нужна для удобства
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

		//Голова
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

		// Голова
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
		// Голова
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

void CreatureInitializationFromFile(string filename) {
	ifstream fin(filename);
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

		prev_pos = monster.GetCenterOfGravityX();

		fin.close();
	}
	else {
		logout << "CreatureInitializationFromFile" << endl;
		exit(0);
	}
}

void NNetInitializationFromFile(string filename) {
	ifstream fin(filename);
	if (fin.is_open()) {
		while (!fin.eof()) {
			std::string s;
			std::getline(fin, s);
			if (s == "") continue;
			if (s[0] == '/') continue;

			std::vector<std::string> info;
			std::string stmp = "";
			for (int i = 0; i < s.length(); ++i) {
				if (s[i] == ';') { // конец строки
					if (stmp != "") {
						info.push_back(stmp);
						stmp = "";
						break;
					}
				}
				if (s[i] == ' ' || s[i] == '=') {
					if (stmp != "") {
						info.push_back(stmp);
						stmp = "";
					}
					continue;
				}

				stmp += s[i];
			}

			if (info.size() == 2) {
				if (info[0] == "CREATURE_NAME") {
					creature_name = info[1];
				}
				if (info[0] == "HIDDEN_LAYERS_NUM") {
					NUM_HIDDEN_LAYERS = std::atoi(info[1].c_str());
				}
				if (info[0] == "HIDDEN_LAYER_NEURONS_NUM") {
					NUM_HIDDEN_NEURONS = std::atoi(info[1].c_str());
				}
				if (info[0] == "ACTIVATION_FUNC") {
					if (info[1] == "TANH") ACT_FUNC = TANH;
					if (info[1] == "SGMD") ACT_FUNC = SGMD;
					if (info[1] == "LINE") ACT_FUNC = LINE;
				}
				if (info[0] == "TEST_TOTAL_NUMBER") {
					TOTAL_TESTS_NUMBER = std::atoi(info[1].c_str());
				}
				if (info[0] == "EPOCH_TESTS_NUM") {
					CUR_TESTS_NUMBER = std::atoi(info[1].c_str());
				}
				if (info[0] == "EPOCH_NUM") {
					EPOCH = std::atoi(info[1].c_str());
				}
				if (info[0] == "TRAINING_TYPE") {
					if (info[1] == "RMS") TRAINING_TYPE = RMS;
				}
				if (info[0] == "RMS_GAMMA") {
					RMS_GAMMA = std::stod(info[1]);
				}
				if (info[0] == "RMS_LEARN_RATE") {
					RMS_LEARN_RATE = std::stod(info[1]);
				}
				if (info[0] == "RMS_ACCURACY") {
					RMS_EPS = std::stod(info[1]);
				}
				if (info[0] == "QLEARN_RATE") {
					QGAMMA = std::stod(info[1]);
				}
				if (info[0] == "TRAINING_PERIOD") {
					TICK_COUNT = std::atoi(info[1].c_str());
				}
				if (info[0] == "TRAINING_ACCURACY") {
					TRAIN_EPS = std::stod(info[1]);
				}
			}
			else {
				logout << "NNetInitializationFromFile Data Errors" << endl;
				exit(0);
			}
		}
		fin.close();
	}
	else {
		logout << "NNetInitializationFromFile" << endl;
		exit(0);
	}
}

void SetWeigntsAndBiases(string filename, vector<int> num_neurons) {
	ifstream fin(filename);
	if (fin.is_open()) {
		string s;
		getline(fin, s);
		if (s == "") return;

		// Считывание весов и смещений
		vector<Matrix2d> weights;
		for (int i = 0; i < NUM_HIDDEN_LAYERS + 1; ++i) {
			Matrix2d _w;
			if (i == 0)
				_w = Matrix2d(2 * monster.GetNumJoints(), num_neurons[i]);
			else
				_w = Matrix2d(num_neurons[i - 1], num_neurons[i]);
			for (int j = 0; j < _w.GetNumRows(); ++j) {
				for (int k = 0; k < _w.GetNumCols(); ++k) {
					double tmp;
					fin >> tmp;
					_w.at(j, k) = tmp;
				}
			}
			weights.push_back(_w);
		}

		getline(fin, s);
		getline(fin, s);
		vector<Matrix2d> biases;
		for (int i = 0; i < NUM_HIDDEN_LAYERS + 1; ++i) {
			Matrix2d _b;

			_b = Matrix2d(1, num_neurons[i]);
			for (int j = 0; j < _b.GetNumRows(); ++j) {
				for (int k = 0; k < _b.GetNumCols(); ++k) {
					double tmp;
					fin >> tmp;
					_b.at(j, k) = tmp;
				}
			}
			biases.push_back(_b);
		}

		nnet.SetWeights(weights);
		nnet.SetBiases(biases);

		fin.close();
	}
}

void SetJointsAndStates(string filename) {
	ifstream fin(filename);
	if (fin.is_open()) {
		string s;
		getline(fin, s);
		if (s == "") return;

		vector<pair<double, double>> cur_joints(monster.GetNumJoints());
		for (int i = 0; i < cur_joints.size(); ++i) {
			fin >> cur_joints[i].first >> cur_joints[i].second;
		}
		getline(fin, s);
		getline(fin, s);

		vector<int> cur_states(monster.GetCurLinesStates().size());
		for (int i = 0; i < cur_states.size(); ++i) {
			fin >> cur_states[i];
		}

		monster.SetJoints(cur_joints);
		monster.SetStates(cur_states);

		fin.close();
	}
}

void SetCurTick(string filename) {
	ifstream fin(filename);
	if (fin.is_open()) {
		string s;
		int tick = 0;
		double dist = 0.0;

		while (!fin.eof())
		{
			fin >> tick >> dist;
		}

		cur_tick = tick / T*T;

		fin.close();
	}
}

void DrawBackground() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);

	glBegin(GL_QUADS);
	glTexCoord2f(DeltaX / WinWidth, 0.0); // от 0 до 1
	glVertex2f(0, 0);

	glTexCoord2f(1.0, 0.0); // от 0 до 1
	glVertex2f(WinWidth - DeltaX, 0);

	glTexCoord2f(1.0, 1.0); // от 0 до 1
	glVertex2f(WinWidth - DeltaX, WinHeight);

	glTexCoord2f(DeltaX / WinWidth, 1.0); // от 0 до 1
	glVertex2f(0, WinHeight);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); // от 0 до 1
	glVertex2f(WinWidth - DeltaX, 0);

	glTexCoord2f(DeltaX / WinWidth, 0.0); // от 0 до 1
	glVertex2f(WinWidth, 0);

	glTexCoord2f(DeltaX / WinWidth, 1.0); // от 0 до 1
	glVertex2f(WinWidth, WinHeight);

	glTexCoord2f(0.0, 1.0); // от 0 до 1
	glVertex2f(WinWidth - DeltaX, WinHeight);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void Draw() {
	int tmp = monster.GetCenterOfGravityX() / WinWidth;
	DeltaX = monster.GetCenterOfGravityX() - tmp*WinWidth;
	DrawBackground();

	DeltaX = monster.GetCurDeltaDistance();

	// Вывофд информации
	glColor3d(0.0, 0.0, 0.0);
	glEnter2D();
	string tmps = "Tick: " + to_string(cur_tick) + "  Dist: " + to_string(fabs(monster.GetCurDeltaDistance()));
	glWrite(20, WinHeight - 80, (int*)GLUT_BITMAP_8_BY_13, tmps);
	string spos = "XPos: " + to_string(monster.GetCenterOfGravityX()) + " YPos: " + to_string(monster.GetCenterOfGravityY());
	glWrite(20, WinHeight - 60, (int*)GLUT_BITMAP_8_BY_13, spos);

	string rewstr = "Rew: " + to_string(reward);
	glWrite(20, WinHeight - 40, (int*)GLUT_BITMAP_8_BY_13, rewstr);

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
	double cgx = monster.GetCenterOfGravityX();
	glVertex2f(cgx + 100.0 + dx - DeltaX, cgy + ground_height - 10);
	glVertex2f(cgx + 100.0 + dx - DeltaX, cgy + ground_height + 10);

	glVertex2f(cgx + 100.0 + dx - 10.0 - DeltaX, cgy + ground_height);
	glVertex2f(cgx + 100.0 + dx + 10.0 - DeltaX, cgy + ground_height);
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
	glClear(GL_COLOR_BUFFER_BIT); // Очищает экран
	Draw();

	glFlush(); // Выводит на экран буфер
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
	double cg = monster.GetCenterOfGravityX();

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

	prev_pos = monster.GetCenterOfGravityX();

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
			if (run_type != RUN) {
				//if (nnet.RunningLearningOffline(tests) == 0.0)
				//	break;
				//if (nnet.RPropLearningOffline(tests) < TRAIN_EPS) //Добавить расчет ошибки 
				//	break;
				if (nnet.RMSLearningOffline(tests, tests_pos) < TRAIN_EPS) //Добавить расчет ошибки 
					break;
			}
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
			action = (monster.GetNumActions() - 1)*rand() / RAND_MAX;
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

	//Вывод текущей информации
	cout << cur_tick << "  " << monster.GetCurDeltaDistance() << endl;

	if (cur_tick % T == 0) {
		string dirname = res_dir_str + nnet_name;
		ofstream wbfout(dirname + "\\" + nnet_name + wb_finame_end);
		//fout << "==================================================================================" << endl;
		nnet.PrintWeightsAndBiases(wbfout, false);
		//fout << "==================================================================================" << endl;
		//fout << endl << endl;
		wbfout.close();

		ofstream crfout(dirname + "\\" + nnet_name + curcr_finame_end);
		//cfout << "==================================================================================" << endl;
		monster.PrintCreatureJoints(crfout);
		//cfout << "==================================================================================" << endl;
		//cfout << endl << endl;
		crfout.close();
	}

	fflush(stdout);
}

void Timer(int val) // Таймер(промежуток времени, в котором будет производится все процессы) 
{
	Display();
	DoNextStep();

	if (cur_tick < TICK_COUNT) {
		if (run_type != RUN)
			glutTimerFunc(50, Timer, 0); // новый вызов таймера( 100 - промежуток времени(в милисекундах), через который он будет вызыватся, timer - вызываемый паблик) 
		else
			glutTimerFunc(120, Timer, 0);
	}
}

//===============================================
//Для вывода текста
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

//Для фона
void LoadTexture() {
	AUX_RGBImageRec *texture1 = auxDIBImageLoadA("4.bmp");
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->sizeX, texture1->sizeY,
		0, GL_RGB, GL_UNSIGNED_BYTE, texture1->data);
}