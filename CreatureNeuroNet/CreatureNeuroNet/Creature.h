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
	double turn_unit_angle = M_PI / 30; // единичный угол поворота
	//int ground_height = 0;
	double start_pos = 0.0;
	double start_max_x = 0.0;
	double cur_delta_distance = 0.0;

	double falling = 0.0;

	vector<pair<double, double>> joints; // суставы (точки соединения)
	vector<pair<int, int>> lines; // отрезки, из которых состоит модель (две точки и длина)
	vector<double> lines_length;

	vector<pair<int, int>> movable_lines; //{номер отрезка; номер сустава, в котором он поворачивается}

	vector<pair<double, double>> turn_intervals; // левая и правая границы интервалов поворота отрезков 
	vector<pair<int, int>> states_mvlines; // текущие состояния подвижных отрезков, количество состояний отрезка
	vector<vector<int>> refs; //какие отрезки повернутся, если повернуть текущий
	
    //vector<vector<pair<int, double>>> graph; // {(точка из joints, c которой соединена текущая точка), (Длина отрезка)}
public:
	Creature() {};
	void InitCreature(vector<pair<double, double>> _joints, 
					vector<pair<int, int>> _lines, 
					vector<pair<int, int>> _mvlines, 
					vector<pair<double, double>> _turnint, 
					vector<pair<int, int>> states,
					vector<vector<int>> _refs);

	//void SetGroundHeight(double y) { ground_height = y; };

	int GetNumActions() { return 2*movable_lines.size(); } //поворот каждого отрезка в двух направлениях
	vector<pair<double, double>> GetJoints() { return joints; }
	double GetStartPos() { return start_pos; }
	vector<pair<int, int>> GetCurLinesStates() { return states_mvlines; }
	int GetNumJoints() { return joints.size(); }


	vector<Line> GetLines();
	double GetCenterOfGravityX();
	double GetCenterOfGravityY();
	double GetCurDeltaDistance();
	double GetTraveledDistance();

	double GetFalling() { return falling; }

	void SetFallUnitAngle(double val) { fall_unit_angle = val; }
	void SetTurnUnitAngle(double val) { turn_unit_angle = val; }

	void SetJoints(vector<pair<double, double>> new_joints);
	void SetStates(vector<int> new_states);

	pair<int, int> GetAction(int action_num);
	bool CanDoAction(int action);
	bool CanDoFullAction(int action);
	int Rotate(int line, int tdir);
	void CorrectPos(int line, int tdir);
	void CorrectPos(int line, int tdir, int point);
	void Falling();
	void UpdatePos(int action_num); // номер действия

	void PrintCreatureJoints(ostream& fout) {
		fout << "--------------------------Creature Joints----------------------------" << endl;
		for (int i = 0; i < joints.size(); ++i) {
			fout <<  fixed <<setprecision(8) << joints[i].first << " " << fixed << setprecision(8) << joints[i].second << endl;
		}
		fout << "--------------------------Creature States----------------------------" << endl;
		for (int i = 0; i < states_mvlines.size(); ++i) {
			fout << states_mvlines[i].first << " ";
		}
		fout << endl << "---------------------------------------------------------------------" << endl;

	}

};
