#pragma once
#include "Creature.h"
#include "NeuroNet.h"
#include "Common.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

void Creature::InitCreature(vector<pair<double, double>> _joints, vector<pair<int, int>> _lines, vector<pair<int, int>> _mvlines,
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

	start_pos = GetCenterOfGravity();
}

vector<Line> Creature::GetLines() {
	vector<Line> res;

	for (int i = 0; i < lines.size(); ++i) {
		Point p1 = { joints[lines[i].first].first, joints[lines[i].first].second };
		Point p2 = { joints[lines[i].second].first, joints[lines[i].second].second };
		res.push_back({ p1, p2, lines_length[i] });
	}
	return res;
}

double Creature::GetCenterOfGravity() {
	double sum_momets = 0.0;
	double sum_mass = 0.0;
	double res = 0.0;

	for (int i = 0; i < lines.size(); ++i) {
		double cx = 1.0*(joints[lines[i].first].first + joints[lines[i].second].first) / 2; // координата x центра т€жести
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

bool Creature::CanDoAction(int action) {
	pair<int, int> line_and_dir = GetAction(action);

	//≈сли отрезок находитс€ в одном из крайних состо€ний
	if (states_mvlines[movable_lines[line_and_dir.first].first] == 0 && line_and_dir.second == 1)
		return false;
	if (states_mvlines[movable_lines[line_and_dir.first].first] == (num_turn_states - 1) && line_and_dir.second == -1)
		return false;

	return true;
}

bool Creature::CanDoFullAction(int action) {
	pair<int, int> line_and_dir = GetAction(action);

	int line = line_and_dir.first;
	int tdir = line_and_dir.second;
	double angsign = 0.0;

	// Ќаправление поворота
	if (tdir == 1)
		angsign = -1.0;
	if (tdir == -1)
		angsign = 1.0;

	int mvline = movable_lines[line].first;
	double unit_angle = (turn_intervals[mvline].second - turn_intervals[mvline].first) / (num_turn_states - 1);

	// ѕеремещение
	set<int> points;
	int os = movable_lines[line].second;

	// концы отрезка, который поворачиваетс€
	if (lines[mvline].first != os)
		points.insert(lines[mvline].first);
	if (lines[mvline].second != os)
		points.insert(lines[movable_lines[line].first].second);

	for (int i = 0; i < refs[mvline].size(); ++i) {
		points.insert(lines[refs[mvline][i]].first);
		points.insert(lines[refs[mvline][i]].second);
	}

	for (auto it = points.begin(); it != points.end(); ++it) {
		double d = GetDistance(joints[os].first, joints[os].second, joints[*it].first, joints[*it].second);
		double angle = GetAngle(joints[os].first, joints[os].second, joints[*it].first, joints[*it].second) + angsign*unit_angle;
		double new_y = joints[os].second + d*sin(angle);
		if (new_y < 0.0)
			return false;
	}

	return true;
}

void Creature::Falling() {
	double cg = GetCenterOfGravity();
	vector<pair<pair<double, double>, int>> sup_points; // точки опоры
	double err_y = 0.0; // допустимое рассто€ние от земли, при котором касание еще существует

	for (int i = 0; i < joints.size(); ++i) {
		if (joints[i].second <= err_y /*&& joints[i].second >= 0.0*/) {
			sup_points.push_back(make_pair(joints[i], i));
		}
	}

	// ≈сли после поворота некоторго отрезка, существо оказалось в воздухе
	if (sup_points.size() == 0) {
		double ymn = 1.0*1e9;
		for (int i = 0;i < joints.size(); ++i) {
			if (joints[i].second < ymn) {
				ymn = joints[i].second;
			}
		}

		for (int i = 0; i < joints.size(); ++i) {
			joints[i].second -= ymn;
		}

		for (int i = 0; i < joints.size(); ++i) {
			if (joints[i].second <= err_y /*&& joints[i].second >= 0*/) {
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
		double angle_sign = 0.0;
		if (fall_flag == 1) angle_sign = -1.0;
		else angle_sign = 1.0;

		vector<pair<double, double>> new_pos;
		vector<double> err_angles;
		for (int i = 0; i < joints.size(); ++i) {
			if (i == turn_point) continue;
			double d = GetDistance(joints[turn_point].first, joints[turn_point].second, joints[i].first, joints[i].second);
			double angle = GetAngle(joints[turn_point].first, joints[turn_point].second, joints[i].first, joints[i].second);
			double x = joints[turn_point].first + d*cos(angle + angle_sign*fall_unit_angle);
			double y = joints[turn_point].second + d*sin(angle + angle_sign*fall_unit_angle);
			if (y < 0.0) {
				double tmp_a = GetAngle(joints[turn_point].first, joints[turn_point].second, joints[i].first + 1.0*fall_flag*d, 0.0);

				angle = GetEquivPositiveAngle(angle);
				tmp_a = GetEquivPositiveAngle(tmp_a);

				err_angles.push_back(fabs(angle - tmp_a));
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

int Creature::Rotate(int line, int tdir) {
	double angsign = 0.0;
	int mvline = movable_lines[line].first;
	// ќбновление состо€ний
	if (tdir == 1) {
		states_mvlines[mvline]--;
		angsign = -1.0;
	}
	if (tdir == -1) {
		states_mvlines[mvline]++;
		angsign = 1.0;
	}

	double unit_angle = (turn_intervals[mvline].second - turn_intervals[mvline].first) / (num_turn_states - 1);

	set<int> points;
	int os = movable_lines[line].second;
	// концы отрезка, который поворачиваетс€
	if (lines[mvline].first != os)
		points.insert(lines[mvline].first);
	if (lines[mvline].second != os)
		points.insert(lines[mvline].second);

	for (int i = 0; i < refs[mvline].size(); ++i) {
		points.insert(lines[refs[mvline][i]].first);
		points.insert(lines[refs[mvline][i]].second);
	}

	double ymn = DBL_MAX;
	int minpoint = -1;
	for (auto it = points.begin(); it != points.end(); ++it) {
		double d = GetDistance(joints[os].first, joints[os].second, joints[*it].first, joints[*it].second);
		double angle = GetAngle(joints[os].first, joints[os].second, joints[*it].first, joints[*it].second) + angsign*unit_angle;
		joints[*it].first = joints[os].first + d*cos(angle);
		joints[*it].second = joints[os].second + d*sin(angle);
		if (joints[*it].second < ymn) {
			ymn = joints[*it].second;
			minpoint = *it;
		}
	}

	return minpoint;
}

// ќбъединить CorrectPos в одну!!!
void Creature::CorrectPos(int line, int tdir) {
	int mvline = movable_lines[line].first;
	int os = movable_lines[line].second;
	int nos;
	if (lines[mvline].first != os) // находим точку отрезка, котора€ Ќ≈ €вл€етс€ суставом поворота
		nos = lines[mvline].first;
	else
		nos = lines[mvline].second;

	double dy = fabs(joints[nos].second);
	double dx = 0.0;
	double x1 = joints[os].first - sqrt(lines_length[mvline] * lines_length[mvline] - joints[os].second*joints[os].second);
	double x2 = joints[os].first + sqrt(lines_length[mvline] * lines_length[mvline] - joints[os].second*joints[os].second);

	if (tdir == 1) {
		dx = fabs(max(x1, x2) - joints[nos].first);
	}
	else if (tdir == -1) {
		dx = fabs(min(x1, x2) - joints[nos].first);
	}

	for (int i = 0; i < joints.size(); ++i) {
		joints[i].first += 1.0*tdir*dx;
		joints[i].second += dy;
	}
}

void Creature::CorrectPos(int line, int tdir, int point) {
	int mvline = movable_lines[line].first;
	int os = movable_lines[line].second;

	double dy = fabs(joints[point].second);
	double dx = 0.0;
	double dd = GetDistance(joints[os].first, joints[os].second, joints[point].first, joints[point].second);
	double x1 = joints[os].first - sqrt(dd * dd - joints[os].second*joints[os].second);
	double x2 = joints[os].first + sqrt(dd * dd - joints[os].second*joints[os].second);

	if (tdir == 1) {
		dx = fabs(max(x1, x2) - joints[point].first);
	}
	else if (tdir == -1) {
		dx = fabs(min(x1, x2) - joints[point].first);
	}

	for (int i = 0; i < joints.size(); ++i) {
		joints[i].first += tdir*dx;
		joints[i].second += dy;
	}
}

void Creature::UpdatePos(int action_num) {
	pair<int, int> p = GetAction(action_num);// номер отрезка и направление поворота (1 - по ч.с., 2 - против ч.с.)
	int line = p.first;
	int mvline = movable_lines[line].first;
	int tdir = p.second;
	int angsign = 0;

	// ѕеремещение
	if (CanDoFullAction(action_num)) { // ≈сли можно совершить полный поворот отрезком
		Rotate(line, tdir);
	}
	else {
		if (refs[mvline].size() == 0) { // ≈сли у текущего отрезка нет зависимых отрезков
			Rotate(line, tdir);
			CorrectPos(line, tdir); // ћожно немного изменить, чтобы добавл€ть точку поворота
		}
		else {
			/*set<int> tmp;
			tmp.insert(lines[mvline].first);
			tmp.insert(lines[mvline].second);
			for (int i = 0; i < refs[line].size(); ++i) {
				tmp.insert(lines[movable_lines[refs[mvline][i]].first].first);
				tmp.insert(lines[movable_lines[refs[mvline][i]].first].second);
			}

			double ymn = 1.0*1e9;
			int p = 0;
			for (auto it = tmp.begin(); it != tmp.end(); ++it) {
				if (joints[*it].second < ymn) {
					ymn = joints[*it].second;
					p = *it;
				}
			}*/

			int point = Rotate(line, tdir);
			CorrectPos(line, tdir, point);
		}
	}

	// ѕадение
	Falling();
}

double Creature::GetCenterOfGravity2() {
	/*double sum_momets = 0.0;
	double sum_mass = 0.0;
	double res = 0.0;

	for (int i = 0; i < lines.size(); ++i) {
		bool fl = true;
		for (int j = 0; j < movable_lines.size(); ++j) {
			if (i == movable_lines[j].first)
				fl = false;
		}
		if (fl) {
			double cx = 1.0*(joints[lines[i].first].first + joints[lines[i].second].first) / 2; // координата x центра т€жести
			sum_mass += lines_length[i]; // lines_length[i] - длина отрезка, и т.к. 1 ед. длины = 1 ед. массы, то используем длину
			sum_momets += cx*lines_length[i]; // плечо на массу
		}
	}
	return res = sum_momets / sum_mass;*/
	//double tmp = -DBL_MAX;
	//for (int i = 0; i < joints.size(); ++i) {
	//	if (joints[i].first > tmp) {
	//		tmp = joints[i].first;
	//	}
	//}

	double tmp = (joints[0].first + joints[3].first) / 2 - start_pos;

	return tmp;
}