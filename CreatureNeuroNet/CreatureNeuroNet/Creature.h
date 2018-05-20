#pragma once
#define _USE_MATH_DEFINES
#include "Common.h"
#include "NeuroNet.h"
#include <vector>
using namespace std;

class Creature {
private:
	double fall_unit_angle = M_PI / 30; // ��������� ���� �������
	int num_turn_units = 10; // �� ����� ���������� �������� ����� ������� ���� �������� ��� ��������
	//int ground_height = 0;
	double start_pos = 0.0;
	double cur_delta_distance = 0.0;
	vector<pair<int, int>> joints; // ������� (����� ����������)
	vector<pair<int, int>> lines; // �������, �� ������� ������� ������ (��� ����� � �����)
	vector<double> lines_length;

	vector<pair<int, int>> movable_lines; //{����� �������; ����� �������, � ������� �� ��������������}
	vector<pair<double, double>> turn_intervals; // ����� � ������ ������� ���������� �������� �������� 
	vector<int> states_mvlines; // ������� ��������� ��������� ��������
	vector<vector<int>> refs; //����� ������� ����������, ���� ��������� �������
	
    //vector<vector<pair<int, double>>> graph; // {(����� �� joints, c ������� ��������� ������� �����), (����� �������)}
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

	int GetNumActions() { return 2*movable_lines.size(); } //������� ������� ������� � ���� ������������
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
	void UpdatePos(int action_num); // ����� ��������
};
