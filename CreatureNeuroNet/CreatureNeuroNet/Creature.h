#pragma once
#define _USE_MATH_DEFINES
#include "Common.h"
#include "NeuroNet.h"
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

class Creature {
private:
	double fall_unit_angle = M_PI / 30; // единичный угол падения
	int num_turn_states = 11; // на какое количество секторов будут разбиты углы поворота для отрезков
	//int ground_height = 0;
	double start_pos = 0.0;
	double start_max_x = 0.0;
	double cur_delta_distance = 0.0;
	vector<pair<double, double>> joints; // суставы (точки соединения)
	vector<pair<int, int>> lines; // отрезки, из которых состоит модель (две точки и длина)
	vector<double> lines_length;

	vector<pair<int, int>> movable_lines; //{номер отрезка; номер сустава, в котором он поворачивается}

	vector<pair<double, double>> turn_intervals; // левая и правая границы интервалов поворота отрезков 
	vector<int> states_mvlines; // текущие состояния подвижных отрезков
	vector<vector<int>> refs; //какие отрезки повернутся, если повернуть текущий
	
    //vector<vector<pair<int, double>>> graph; // {(точка из joints, c которой соединена текущая точка), (Длина отрезка)}
public:
	Creature() {};
	void InitCreature(vector<pair<double, double>> _joints, 
					vector<pair<int, int>> _lines, 
					vector<pair<int, int>> _mvlines, 
					vector<pair<double, double>> _turnint, 
					vector<int> states,
					vector<vector<int>> _refs);

	void SetFallUnitAngle(double a) { fall_unit_angle = a; };
	void SetTurnUnitAngle(int a) { num_turn_states = a; };
	//void SetGroundHeight(double y) { ground_height = y; };

	int GetNumActions() { return 2*movable_lines.size(); } //поворот каждого отрезка в двух направлениях
	int GetNumStates() { return num_turn_states; }
	vector<int> GetCurLinesStates() { return states_mvlines; }
	vector<pair<double, double>> GetJoints() { return joints; }
	double GetStartPos() { return start_pos; }


	vector<Line> GetLines();
	double GetCenterOfGravity();
	double GetCurDeltaDistance();
	double GetTraveledDistance();


	pair<int, int> GetAction(int action_num);
	bool CanDoAction(int action);
	bool CanDoFullAction(int action);
	int Rotate(int line, int tdir);
	void CorrectPos(int line, int tdir);
	void CorrectPos(int line, int tdir, int point);
	void Falling();
	void UpdatePos(int action_num); // номер действия

	void PrintCreatureJoints() {
		cout << "--------------------------Creature Joints----------------------------" << endl;
		for (int i = 0; i < joints.size(); ++i) {
			cout <<  fixed <<setprecision(8) << joints[i].first << " " << fixed << setprecision(8) << joints[i].second << endl;
		}
		cout << "---------------------------------------------------------------------" << endl;

	}


	double GetCenterOfGravityY();

};
