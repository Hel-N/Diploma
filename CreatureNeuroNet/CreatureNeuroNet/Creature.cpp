#pragma once
#include "Creature.h"
#include "NeuroNet.h"
#include "Common.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

void Creature::InitCreature(vector<pair<int, int>> _joints, vector<pair<int, int>> _lines, vector<pair<int, int>> _mvlines,
	vector<pair<double, double>> _turnint, vector<int> states, vector<vector<int>> _refs) {
	joints = _joints;
	lines = _lines;

	for (int i = 0; i < _lines.size(); ++i) {
		double d = GetDistance(joints[lines[i].first].first, joints[lines[i].first].second, joints[lines[i].second].first, joints[lines[i].second].second);
		lines_length.push_back(d);
	}

	movable_lines = _mvlines;
	turn_intervals = _turnint;
	states_mvlines = states;
	refs = _refs;
}
//void Creature::Init();

vector<Line> Creature::GetLines() {
	vector<Line> res;

	for (int i = 0; i < lines.size(); ++i) {
		Point p1 = { joints[lines[i].first].first, joints[lines[i].first].second };
		Point p2 = { joints[lines[i].second].first, joints[lines[i].second].second };
		res.push_back({ p1, p2, lines_length[i] });
	}
	return res;
}

bool Creature::CanDoAction(int action) {
	pair<int, int> line_and_dir = GetAction(action);

	if (states_mvlines[line_and_dir.first] == 0 && line_and_dir.second == 1)
		return false;
	if (states_mvlines[line_and_dir.first] == num_turn_units - 1 && line_and_dir.second == -1)
		return false;

	int line = line_and_dir.first;
	int tdir = line_and_dir.second;
	int angsign = 0;

	// Направление поворота
	if (tdir == 1)
		angsign = -1;
	if (tdir == -1)
		angsign = 1;

	double unit_angle = (turn_intervals[line].second - turn_intervals[line].first) / num_turn_units;

	// Перемещение
	set<int> points;
	int os = movable_lines[line].second;
	// концы отрезка, который поворачивается
	if (lines[movable_lines[line].first].first != os)
		points.insert(lines[movable_lines[line].first].first);
	if (lines[movable_lines[line].first].second != os)
		points.insert(lines[movable_lines[line].first].second);

	for (int i = 0; i < refs[movable_lines[line].first].size(); ++i) {
		points.insert(lines[refs[movable_lines[line].first][i]].first);
		points.insert(lines[refs[movable_lines[line].first][i]].second);
	}

	for (auto it = points.begin(); it != points.end(); ++it) {
		double d = GetDistance(joints[os].first, joints[os].second, joints[*it].first, joints[*it].second);
		double angle = GetAngle(joints[os].first, joints[os].second, joints[*it].first, joints[*it].second) + angsign*unit_angle;
		int new_y = joints[os].second + d*sin(angle);
		if (new_y < 0)
			return false;
	}

	return true;
}

double Creature::GetCenterOfGravity() {
	double sum_momets = 0.0;
	double sum_mass = 0.0;
	double res = 0.0;

	for (int i = 0; i < lines.size(); ++i) {
		double cx = 1.0*(joints[lines[i].first].first + joints[lines[i].second].first) / 2; // координата x центра тяжести
		sum_mass += lines_length[i]; // lines_length[i] - длина отрезка, и т.к. 1 ед. длины = 1 ед. массы, то используем длину
		sum_momets += cx*lines_length[i]; // плечо на массу
	}
	return res = sum_momets / sum_mass;
}

double Creature::GetCurDeltaDistance() {
	double cx = GetCenterOfGravity();
	return cx - start_pos;
}

pair<int, int> Creature::GetAction(int action_num) {
	int line = action_num / 2;
	int turn_dir;

	if (action_num % 2 == 0)
		turn_dir = 1;
	else
		turn_dir = -1;

	return make_pair(line, turn_dir);
}

void Creature::UpdatePos(int action_num) {  
	pair<int, int> p = GetAction(action_num);// номер отрезка и направление поворота (1 - по ч.с., 2 - против ч.с.)
	int line = p.first;
	int tdir = p.second;
	int angsign = 0;

	// Обновление состояний
	if (tdir == 1) {
		states_mvlines[line]--;
		angsign = -1;
	}
	if (tdir == -1) {
		states_mvlines[line]++;
		angsign = 1;
	}

	double unit_angle = (turn_intervals[line].second - turn_intervals[line].first) / num_turn_units;

	// Перемещение
	set<int> points;
	int os = movable_lines[line].second;
	// концы отрезка, который поворачивается
	if (lines[movable_lines[line].first].first != os) 
		points.insert(lines[movable_lines[line].first].first);
	if (lines[movable_lines[line].first].second != os)
		points.insert(lines[movable_lines[line].first].second);

	for (int i = 0; i < refs[movable_lines[line].first].size(); ++i) {
		points.insert(lines[refs[movable_lines[line].first][i]].first);
		points.insert(lines[refs[movable_lines[line].first][i]].second);
	}

	for (auto it = points.begin(); it != points.end(); ++it) {
		double d = GetDistance(joints[os].first, joints[os].second, joints[*it].first, joints[*it].second);
		double angle = GetAngle(joints[os].first, joints[os].second, joints[*it].first, joints[*it].second) + angsign*unit_angle;
		joints[*it].first = joints[os].first + d*cos(angle);
		joints[*it].second = joints[os].second + d*sin(angle);
	}

	// Падение
	double cg = GetCenterOfGravity();
	vector<pair<pair<int, int>, int>> sup_points; // точки опоры
	int err_y = 0; // допустимое расстояние от земли, при котором касание еще существует

	for (int i = 0; i < joints.size(); ++i) {
		if (joints[i].second <= err_y && joints[i].second >= 0) {
			sup_points.push_back(make_pair(joints[i], i));
		}
	}

	if (sup_points.size() == 0) {
		int ymn = 1e9;
		for (int i = 0;i < joints.size(); ++i) {
			if (joints[i].second < ymn) {
				ymn = joints[i].second;
			}
		}

		for (int i = 0;i < joints.size(); ++i) {
			joints[i].second -= ymn;
		}

		for (int i = 0; i < joints.size(); ++i) {
			if (joints[i].second <= err_y && joints[i].second >= 0) {
				sup_points.push_back(make_pair(joints[i], i));
			}
		}
	}

	sort(sup_points.begin(), sup_points.end());

	int fall_flag = 0; // balance
	int turn_point;

	if (sup_points[0].first.first > cg) { // left
		turn_point = sup_points[0].second;
		fall_flag = -1;
	}
	else if (sup_points[sup_points.size() - 1].first.first < cg) { //right
		turn_point = sup_points[0].second;
		fall_flag = 1;
	}

	if (fall_flag != 0) {
		double angle_sign;
		if (fall_flag == 1) angle_sign = -1.0;
		else angle_sign = 1.0;

		vector<pair<int, int>> new_pos;
		vector<double> err_angles;
		for (int i = 0; i < joints.size(); ++i) {
			if (i == turn_point) continue;
			double d = GetDistance(joints[turn_point].first, joints[turn_point].second, joints[i].first, joints[i].second);
			double angle = GetAngle(joints[turn_point].first, joints[turn_point].second, joints[i].first, joints[i].second);
			//joints[i].first = joints[turn_point].first + d*cos(angle);
			//joints[i].second = joints[turn_point].second + d*sin(angle);
			int x = joints[turn_point].first + d*cos(angle + angle_sign*fall_unit_angle);
			int y = joints[turn_point].second + d*sin(angle + angle_sign*fall_unit_angle);
			if (y < 0) {
				double tmp_a;
				if (fall_flag == 1)
					tmp_a = GetAngle(joints[turn_point].first, joints[turn_point].second, joints[i].first + d, 0);
				else
					tmp_a = GetAngle(joints[turn_point].first, joints[turn_point].second, joints[i].first - d, 0);
				err_angles.push_back(abs(angle - tmp_a));
			}
			new_pos.push_back(make_pair(x, y));
		}

		if (!err_angles.size()) {
			for (int i = 0, j = 0; i < joints.size(); ++i) {
				if (i == turn_point) continue;
				joints[i].first = new_pos[j].first;
				joints[i].second = new_pos[j].second;
				j++;
			}
		}
		else {
			sort(err_angles.begin(), err_angles.end());
			for (int i = 0; i < joints.size(); ++i) {
				if (i == turn_point) continue;
				double d = GetDistance(joints[turn_point].first, joints[turn_point].second, joints[i].first, joints[i].second);
				double angle = GetAngle(joints[turn_point].first, joints[turn_point].second, joints[i].first, joints[i].second) + angle_sign*err_angles[0];
				joints[i].first = joints[turn_point].first + d*cos(angle);
				joints[i].second = joints[turn_point].second + d*sin(angle);
			}
		}
	}
}
