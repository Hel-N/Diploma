#pragma once
#define _USE_MATH_DEFINES
#include "Common.h"
#include "NeuroNet.h"
#include <vector>
using namespace std;

class Creature {
private:
	double fall_unit_angle = M_PI / 30; // единичный угол падения
	int num_turn_units = 10; // на какое количество секторов будут разбиты углы поворота для отрезков
	//int ground_height = 0;
	double start_pos = 0.0;
	double cur_delta_distance = 0.0;
	vector<pair<int, int>> joints; // суставы (точки соединения)
	vector<pair<int, int>> lines; // отрезки, из которых состоит модель (две точки и длина)
	vector<double> lines_length;

	vector<pair<int, int>> movable_lines; //{номер отрезка; номер сустава, в котором он поворачивается}
	vector<pair<double, double>> turn_intervals; // левая и правая границы интервалов поворота отрезков 
	vector<int> states_mvlines; // текущие состояния подвижных отрезков
	vector<vector<int>> refs; //какие отрезки повернутся, если повернуть текущий
	
    //vector<vector<pair<int, double>>> graph; // {(точка из joints, c которой соединена текущая точка), (Длина отрезка)}
public:
	Creature() {};
	void InitCreature(vector<pair<int, int>> _joints, 
					vector<pair<int, int>> _lines, 
					vector<pair<int, int>> _mvlines, 
					vector<pair<double, double>> _turnint, 
					vector<int> states,
					vector<vector<int>> _refs);

	void SetFallUnitAngle(double a) { fall_unit_angle = a; };
	void SetTurnUnitAngle(int a) { num_turn_units = a; };
	//void SetGroundHeight(double y) { ground_height = y; };

	int GetNumActions() { return 2*movable_lines.size(); } //поворот каждого отрезка в двух направлениях
	vector<pair<int, int>> GetJoints() { return joints; }


	vector<Line> GetLines();
	double GetCenterOfGravity();
	double GetCurDeltaDistance();


	pair<int, int> GetAction(int action_num);
	bool CanDoAction(int action);
	bool CanDoFullAction(int action);
	void Rotate(int line, int tdir);
	void CorrectPos(int line, int tdir);
	void CorrectPos(int line, int tdir, int point);
	void Falling();
	void UpdatePos(int action_num); // номер действия
};
