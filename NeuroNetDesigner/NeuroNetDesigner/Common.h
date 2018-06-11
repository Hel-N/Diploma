#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <math.h>
#include <stdio.h>
#include <windows.h>
#include <msclr\marshal_cppstd.h>

enum ActFuncTypes { LINE, TANH, SGMD };
enum TrainingTypes { RMS };

struct NNet {
	std::string name;
	std::string creature_name = "";
	int inputs_num;
	int hidden_layers_num;
	int hidden_layer_neurons;
	int outputs_num;
	ActFuncTypes act_func;
	int tests_total_num;
	int epoch_tests_num;
	int epoch_num;
	TrainingTypes training_type;
	double rms_gamma;
	double rms_learning_rate;
	double rms_accuracy;
	double qlearn_rate;
	int training_period;
	double training_accuracy;
	bool deleted = false;
};

struct Creature {
	std::string name;
	double fall_unit_angle; // единичный угол падения
	double turn_unit_angle; // единичный угол поворота
	std::vector<std::pair<double, double>> joints; // суставы (точки соединения)
	std::vector<std::pair<int, int>> lines; // отрезки, из которых состоит модель (две точки и длина)
	std::vector<std::pair<int, int>> movable_lines; //{номер отрезка; номер сустава, в котором он поворачивается}
	std::vector<std::pair<double, double>> turn_intervals; // левая и правая границы интервалов поворота отрезков 
	std::vector<std::pair<int, int>> states_mvlines; // текущие состояния подвижных отрезков, количество состояний отрезка
	std::vector<std::vector<int>> refs; //какие отрезки повернутся, если повернуть текущий
};

extern std::vector<NNet> nnets;
extern std::map<std::string, int> nnets_names;

extern std::vector<Creature> creatures;
extern std::map<std::string, int> creatures_names;

extern LPCWSTR nnets_dir;
extern LPCWSTR creatures_dir;
extern std::string nnets_dir_str;
extern std::string creatures_dir_str;
extern std::string nnet_finame_end;
extern std::string creature_finame_end;
extern std::string img_finame_end;

extern int edit_nnet_pos;

//for MonsterCreator
extern std::vector<std::pair<double, double>> joints;
extern std::vector<std::pair<double, double>> new_joints;
extern std::vector<std::pair<int, int>> lines;
extern std::vector<std::pair<int, int>> movable_lines; // номер отрезка, сустав поворота
extern std::vector<std::pair<double, double>> turn_ints; // границы углов поворота
extern std::vector<std::pair<int, int>> mvstates; // начальные состояниe, количество состояний
extern std::vector<std::vector<int>> refs; // зависимости отрезков

extern double unit_turn_angle;
extern double unit_fall_angle;

extern std::vector<std::pair<double, double>> points;
extern std::set<std::pair<int, int>> drlines;
 
extern int start_point;
extern int finish_point;
 
extern std::vector<std::vector<int>> graph;
extern std::vector<int> used;