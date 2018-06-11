#pragma once
#pragma comment(lib, "glaux.lib")
#define _USE_MATH_DEFINES
#include "glaux.h"
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
#include "NeuroNetEditor.h"

std::vector<NNet> nnets;
std::map<std::string, int> nnets_names;

std::vector<Creature> creatures;
std::map<std::string, int> creatures_names;

LPCWSTR nnets_dir = L"NNets\\*.txt";
LPCWSTR creatures_dir = L"Creatures\\*.txt";
std::string nnets_dir_str = "NNets\\";
std::string creatures_dir_str = "Creatures\\";
std::string nnet_finame_end = "_nnet.txt";
std::string creature_finame_end = "_creature.txt";
std::string img_finame_end = "_img.jpg";

int edit_nnet_pos = -1;

//For MonsterCreator------------------------------------------------------------------------------
std::vector<std::pair<double, double>> joints;
std::vector<std::pair<double, double>> new_joints;
std::vector<std::pair<int, int>> lines;
std::vector<std::pair<int, int>> movable_lines; // номер отрезка, сустав поворота
std::vector<std::pair<double, double>> turn_ints; // границы углов поворота
std::vector<std::pair<int, int>> mvstates; // начальные состояниe, количество состояний
std::vector<std::vector<int>> refs; // зависимости отрезков

double unit_turn_angle = 0.0;
double unit_fall_angle = 0.0;

std::vector<std::pair<double, double>> points;
std::set<std::pair<int, int>> drlines;

int start_point = -1;
int finish_point = -1;

std::vector<std::vector<int>> graph;
std::vector<int> used;
//------------------------------------------------------------------------------------------------

namespace NeuroNetDesigner {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	NNet nnetFileParser(std::string filename) {
		std::ifstream fin(filename.c_str());
		NNet res;
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
						res.creature_name = info[1];
					}
					if (info[0] == "HIDDEN_LAYERS_NUM") {
						res.hidden_layers_num = std::atoi(info[1].c_str());
					}
					if (info[0] == "HIDDEN_LAYER_NEURONS_NUM") {
						res.hidden_layer_neurons = std::atoi(info[1].c_str());
					}
					if (info[0] == "ACTIVATION_FUNC") {
						if (info[1] == "TANH") res.act_func = TANH;
						if (info[1] == "SGMD") res.act_func = SGMD;
						if (info[1] == "LINE") res.act_func = LINE;
					}
					if (info[0] == "TEST_TOTAL_NUMBER") {
						res.tests_total_num = std::atoi(info[1].c_str());
					}
					if (info[0] == "EPOCH_TESTS_NUM") {
						res.epoch_tests_num = std::atoi(info[1].c_str());
					}
					if (info[0] == "EPOCH_NUM") {
						res.epoch_num = std::atoi(info[1].c_str());
					}
					if (info[0] == "TRAINING_TYPE") {
						if (info[1] == "RMS") res.training_type = RMS;
					}
					if (info[0] == "RMS_GAMMA") {
						res.rms_gamma = std::stod(info[1]);
					}
					if (info[0] == "RMS_LEARN_RATE") {
						res.rms_learning_rate = std::stod(info[1]);
					}
					if (info[0] == "RMS_ACCURACY") {
						res.rms_accuracy = std::stod(info[1]);
					}
					if (info[0] == "QLEARN_RATE") {
						res.qlearn_rate = std::stod(info[1]);
					}
					if (info[0] == "TRAINING_PERIOD") {
						res.training_period = std::atoi(info[1].c_str());
					}
					if (info[0] == "TRAINING_ACCURACY") {
						res.training_accuracy = std::stod(info[1]);
					}
				}
				else {
					std::string mess = "Некорректные данные в файле " + filename;
					String^ mes = gcnew String(mess.c_str());
					MessageBox::Show(mes);
					delete mes;

					NNet null_res;
					return null_res;
				}
			}
			fin.close();
		}
		else {
			std::string mess = "Ошибка при открытии файла " + filename;
			String^ mes = gcnew String(mess.c_str());
			MessageBox::Show(mes);
			delete mes;
		}

		return res;
	}

	Creature creatureFileParser(std::string filename) {
		std::ifstream fin(filename.c_str());
		Creature res;
		if (fin.is_open()) {
			std::string s;
			getline(fin, s);
			int joint_count;
			fin >> joint_count;
			res.joints.resize(joint_count);
			for (int i = 0; i < res.joints.size(); ++i) {
				fin >> res.joints[i].first >> res.joints[i].second;
			}

			getline(fin, s);
			if (s == "") getline(fin, s);
			int line_count;
			fin >> line_count;
			res.lines.resize(line_count);
			for (int i = 0; i < res.lines.size(); ++i) {
				fin >> res.lines[i].first >> res.lines[i].second;
			}

			getline(fin, s);
			if (s == "") getline(fin, s);
			int mvline_count;
			fin >> mvline_count;
			res.movable_lines.resize(mvline_count);
			for (int i = 0; i < res.movable_lines.size(); ++i) {
				fin >> res.movable_lines[i].first >> res.movable_lines[i].second;
			}

			getline(fin, s);
			if (s == "") getline(fin, s);
			fin >> res.fall_unit_angle;
			getline(fin, s);
			if (s == "") getline(fin, s);
			fin >> res.turn_unit_angle;

			getline(fin, s);
			if (s == "") getline(fin, s);
			int turnint_count;
			fin >> turnint_count;
			res.turn_intervals.resize(turnint_count);
			for (int i = 0; i < res.turn_intervals.size(); ++i) {
				fin >> res.turn_intervals[i].first >> res.turn_intervals[i].second;
			}

			getline(fin, s);
			if (s == "") getline(fin, s);
			int mvstate_count;
			fin >> mvstate_count;
			res.states_mvlines.resize(mvstate_count);
			for (int i = 0; i < res.states_mvlines.size(); ++i) {
				fin >> res.states_mvlines[i].first >> res.states_mvlines[i].second;
			}

			getline(fin, s);
			if (s == "") getline(fin, s);
			int refs_count;
			fin >> refs_count;
			res.refs.resize(refs_count);
			for (int i = 0; i < res.refs.size(); ++i) {
				int rcou;
				fin >> rcou;
				res.refs[i].resize(rcou);
				for (int j = 0; j < res.refs[i].size(); ++j) {
					fin >> res.refs[i][j];
				}
			}

			fin.close();
		}
		else {
			std::string mess = "Ошибка при открытии файла " + filename;
			String^ mes = gcnew String(mess.c_str());
			MessageBox::Show(mes);
			delete mes;
		}

		return res;
	}

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MenuStrip^  MenuStripMain;
	protected:

	protected:
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  выходToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  helpToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  aboutProgramToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  neuralNetToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  creatureModelToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;
	private: System::Windows::Forms::Panel^  PanelMain;
	private: System::Windows::Forms::GroupBox^  GrBoxNNList;


	private: System::Windows::Forms::Button^  BtnNewNN;
	private: System::Windows::Forms::ListBox^  ListBoxNN;
	private: System::Windows::Forms::Button^  BtnDeleteNNet;


	private: System::Windows::Forms::GroupBox^  GrBoxSelectedNN;
	private: System::Windows::Forms::PictureBox^  PBoxNNCreature;
	private: System::Windows::Forms::Button^  BtnRunNNet;

	private: System::Windows::Forms::Button^  BtnTrainNNet;


	private: System::Windows::Forms::Button^  BtnEditNNet;
	private: System::Windows::Forms::GroupBox^  GrBoxNNetSettings;
	private: System::Windows::Forms::Label^  LActFunc;
	private: System::Windows::Forms::Label^  LTrAccuracy;


	private: System::Windows::Forms::Label^  LTrPeriod;

	private: System::Windows::Forms::Label^  Epoches;

	private: System::Windows::Forms::Label^  EpochTests;

	private: System::Windows::Forms::Label^  TotalTestsNumber;

	private: System::Windows::Forms::Label^  LHLNeurons;

	private: System::Windows::Forms::Label^  LHLayers;

	private: System::Windows::Forms::Label^  LInputs;
	private: System::Windows::Forms::Label^  LLearningRate;


	private: System::Windows::Forms::Label^  LRMSAccuracy;

	private: System::Windows::Forms::Label^  LRMSLearnRate;

	private: System::Windows::Forms::Label^  LRMSGamma;

	private: System::Windows::Forms::Label^  LTrType;

	private: System::Windows::Forms::TextBox^  TBoxEpoches;
	private: System::Windows::Forms::TextBox^  TBoxTrAccuracy;


	private: System::Windows::Forms::TextBox^  TBoxTrPeriod;

	private: System::Windows::Forms::TextBox^  TBoxEpochTests;

	private: System::Windows::Forms::TextBox^  TBoxTotalTestsNumber;

	private: System::Windows::Forms::TextBox^  TBoxActFunc;

	private: System::Windows::Forms::TextBox^  TBoxHLNeurons;

	private: System::Windows::Forms::TextBox^  TBoxHLayers;


	private: System::Windows::Forms::TextBox^  TBoxInputs;
	private: System::Windows::Forms::TextBox^  TBoxQLearningRate;




	private: System::Windows::Forms::TextBox^  TBoxRMSAccuracy;

	private: System::Windows::Forms::TextBox^  TBoxRMSLearnRate;


	private: System::Windows::Forms::TextBox^  TBoxRMSGamma;

	private: System::Windows::Forms::TextBox^  TBoxTrType;



	private: System::Windows::Forms::TextBox^  TBoxOutputs;
	private: System::Windows::Forms::Label^  LOutputs;



	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->MenuStripMain = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->выходToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->neuralNetToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->creatureModelToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->helpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aboutProgramToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->PanelMain = (gcnew System::Windows::Forms::Panel());
			this->GrBoxSelectedNN = (gcnew System::Windows::Forms::GroupBox());
			this->GrBoxNNetSettings = (gcnew System::Windows::Forms::GroupBox());
			this->TBoxOutputs = (gcnew System::Windows::Forms::TextBox());
			this->LOutputs = (gcnew System::Windows::Forms::Label());
			this->TBoxQLearningRate = (gcnew System::Windows::Forms::TextBox());
			this->TBoxRMSAccuracy = (gcnew System::Windows::Forms::TextBox());
			this->TBoxRMSLearnRate = (gcnew System::Windows::Forms::TextBox());
			this->TBoxRMSGamma = (gcnew System::Windows::Forms::TextBox());
			this->TBoxTrType = (gcnew System::Windows::Forms::TextBox());
			this->TBoxEpoches = (gcnew System::Windows::Forms::TextBox());
			this->TBoxTrAccuracy = (gcnew System::Windows::Forms::TextBox());
			this->TBoxTrPeriod = (gcnew System::Windows::Forms::TextBox());
			this->TBoxEpochTests = (gcnew System::Windows::Forms::TextBox());
			this->TBoxTotalTestsNumber = (gcnew System::Windows::Forms::TextBox());
			this->TBoxActFunc = (gcnew System::Windows::Forms::TextBox());
			this->TBoxHLNeurons = (gcnew System::Windows::Forms::TextBox());
			this->TBoxHLayers = (gcnew System::Windows::Forms::TextBox());
			this->TBoxInputs = (gcnew System::Windows::Forms::TextBox());
			this->LLearningRate = (gcnew System::Windows::Forms::Label());
			this->LRMSAccuracy = (gcnew System::Windows::Forms::Label());
			this->LRMSLearnRate = (gcnew System::Windows::Forms::Label());
			this->LRMSGamma = (gcnew System::Windows::Forms::Label());
			this->LTrType = (gcnew System::Windows::Forms::Label());
			this->LActFunc = (gcnew System::Windows::Forms::Label());
			this->LTrAccuracy = (gcnew System::Windows::Forms::Label());
			this->LTrPeriod = (gcnew System::Windows::Forms::Label());
			this->Epoches = (gcnew System::Windows::Forms::Label());
			this->EpochTests = (gcnew System::Windows::Forms::Label());
			this->TotalTestsNumber = (gcnew System::Windows::Forms::Label());
			this->LHLNeurons = (gcnew System::Windows::Forms::Label());
			this->LHLayers = (gcnew System::Windows::Forms::Label());
			this->LInputs = (gcnew System::Windows::Forms::Label());
			this->BtnRunNNet = (gcnew System::Windows::Forms::Button());
			this->BtnTrainNNet = (gcnew System::Windows::Forms::Button());
			this->BtnEditNNet = (gcnew System::Windows::Forms::Button());
			this->PBoxNNCreature = (gcnew System::Windows::Forms::PictureBox());
			this->BtnDeleteNNet = (gcnew System::Windows::Forms::Button());
			this->GrBoxNNList = (gcnew System::Windows::Forms::GroupBox());
			this->ListBoxNN = (gcnew System::Windows::Forms::ListBox());
			this->BtnNewNN = (gcnew System::Windows::Forms::Button());
			this->MenuStripMain->SuspendLayout();
			this->PanelMain->SuspendLayout();
			this->GrBoxSelectedNN->SuspendLayout();
			this->GrBoxNNetSettings->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PBoxNNCreature))->BeginInit();
			this->GrBoxNNList->SuspendLayout();
			this->SuspendLayout();
			// 
			// MenuStripMain
			// 
			this->MenuStripMain->ImageScalingSize = System::Drawing::Size(20, 20);
			this->MenuStripMain->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->fileToolStripMenuItem,
					this->helpToolStripMenuItem
			});
			this->MenuStripMain->Location = System::Drawing::Point(0, 0);
			this->MenuStripMain->Name = L"MenuStripMain";
			this->MenuStripMain->Size = System::Drawing::Size(1027, 28);
			this->MenuStripMain->TabIndex = 0;
			this->MenuStripMain->Text = L"MenuStripMain";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->выходToolStripMenuItem,
					this->exitToolStripMenuItem
			});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(44, 24);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// выходToolStripMenuItem
			// 
			this->выходToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->neuralNetToolStripMenuItem,
					this->creatureModelToolStripMenuItem
			});
			this->выходToolStripMenuItem->Name = L"выходToolStripMenuItem";
			this->выходToolStripMenuItem->Size = System::Drawing::Size(114, 26);
			this->выходToolStripMenuItem->Text = L"New";
			// 
			// neuralNetToolStripMenuItem
			// 
			this->neuralNetToolStripMenuItem->Name = L"neuralNetToolStripMenuItem";
			this->neuralNetToolStripMenuItem->Size = System::Drawing::Size(187, 26);
			this->neuralNetToolStripMenuItem->Text = L"Neural Net";
			// 
			// creatureModelToolStripMenuItem
			// 
			this->creatureModelToolStripMenuItem->Name = L"creatureModelToolStripMenuItem";
			this->creatureModelToolStripMenuItem->Size = System::Drawing::Size(187, 26);
			this->creatureModelToolStripMenuItem->Text = L"Creature Model";
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(114, 26);
			this->exitToolStripMenuItem->Text = L"Exit";
			// 
			// helpToolStripMenuItem
			// 
			this->helpToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->aboutProgramToolStripMenuItem });
			this->helpToolStripMenuItem->Name = L"helpToolStripMenuItem";
			this->helpToolStripMenuItem->Size = System::Drawing::Size(53, 24);
			this->helpToolStripMenuItem->Text = L"Help";
			// 
			// aboutProgramToolStripMenuItem
			// 
			this->aboutProgramToolStripMenuItem->Name = L"aboutProgramToolStripMenuItem";
			this->aboutProgramToolStripMenuItem->Size = System::Drawing::Size(196, 26);
			this->aboutProgramToolStripMenuItem->Text = L"About program...";
			// 
			// PanelMain
			// 
			this->PanelMain->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->PanelMain->Controls->Add(this->GrBoxSelectedNN);
			this->PanelMain->Controls->Add(this->GrBoxNNList);
			this->PanelMain->Dock = System::Windows::Forms::DockStyle::Fill;
			this->PanelMain->Location = System::Drawing::Point(0, 28);
			this->PanelMain->Name = L"PanelMain";
			this->PanelMain->Size = System::Drawing::Size(1027, 649);
			this->PanelMain->TabIndex = 1;
			// 
			// GrBoxSelectedNN
			// 
			this->GrBoxSelectedNN->Controls->Add(this->GrBoxNNetSettings);
			this->GrBoxSelectedNN->Controls->Add(this->BtnRunNNet);
			this->GrBoxSelectedNN->Controls->Add(this->BtnTrainNNet);
			this->GrBoxSelectedNN->Controls->Add(this->BtnEditNNet);
			this->GrBoxSelectedNN->Controls->Add(this->PBoxNNCreature);
			this->GrBoxSelectedNN->Controls->Add(this->BtnDeleteNNet);
			this->GrBoxSelectedNN->Location = System::Drawing::Point(342, 24);
			this->GrBoxSelectedNN->Name = L"GrBoxSelectedNN";
			this->GrBoxSelectedNN->Size = System::Drawing::Size(674, 616);
			this->GrBoxSelectedNN->TabIndex = 1;
			this->GrBoxSelectedNN->TabStop = false;
			this->GrBoxSelectedNN->Text = L"Selected NeuroNet";
			// 
			// GrBoxNNetSettings
			// 
			this->GrBoxNNetSettings->Controls->Add(this->TBoxOutputs);
			this->GrBoxNNetSettings->Controls->Add(this->LOutputs);
			this->GrBoxNNetSettings->Controls->Add(this->TBoxQLearningRate);
			this->GrBoxNNetSettings->Controls->Add(this->TBoxRMSAccuracy);
			this->GrBoxNNetSettings->Controls->Add(this->TBoxRMSLearnRate);
			this->GrBoxNNetSettings->Controls->Add(this->TBoxRMSGamma);
			this->GrBoxNNetSettings->Controls->Add(this->TBoxTrType);
			this->GrBoxNNetSettings->Controls->Add(this->TBoxEpoches);
			this->GrBoxNNetSettings->Controls->Add(this->TBoxTrAccuracy);
			this->GrBoxNNetSettings->Controls->Add(this->TBoxTrPeriod);
			this->GrBoxNNetSettings->Controls->Add(this->TBoxEpochTests);
			this->GrBoxNNetSettings->Controls->Add(this->TBoxTotalTestsNumber);
			this->GrBoxNNetSettings->Controls->Add(this->TBoxActFunc);
			this->GrBoxNNetSettings->Controls->Add(this->TBoxHLNeurons);
			this->GrBoxNNetSettings->Controls->Add(this->TBoxHLayers);
			this->GrBoxNNetSettings->Controls->Add(this->TBoxInputs);
			this->GrBoxNNetSettings->Controls->Add(this->LLearningRate);
			this->GrBoxNNetSettings->Controls->Add(this->LRMSAccuracy);
			this->GrBoxNNetSettings->Controls->Add(this->LRMSLearnRate);
			this->GrBoxNNetSettings->Controls->Add(this->LRMSGamma);
			this->GrBoxNNetSettings->Controls->Add(this->LTrType);
			this->GrBoxNNetSettings->Controls->Add(this->LActFunc);
			this->GrBoxNNetSettings->Controls->Add(this->LTrAccuracy);
			this->GrBoxNNetSettings->Controls->Add(this->LTrPeriod);
			this->GrBoxNNetSettings->Controls->Add(this->Epoches);
			this->GrBoxNNetSettings->Controls->Add(this->EpochTests);
			this->GrBoxNNetSettings->Controls->Add(this->TotalTestsNumber);
			this->GrBoxNNetSettings->Controls->Add(this->LHLNeurons);
			this->GrBoxNNetSettings->Controls->Add(this->LHLayers);
			this->GrBoxNNetSettings->Controls->Add(this->LInputs);
			this->GrBoxNNetSettings->Location = System::Drawing::Point(6, 338);
			this->GrBoxNNetSettings->Name = L"GrBoxNNetSettings";
			this->GrBoxNNetSettings->Size = System::Drawing::Size(662, 267);
			this->GrBoxNNetSettings->TabIndex = 6;
			this->GrBoxNNetSettings->TabStop = false;
			this->GrBoxNNetSettings->Text = L"Settings";
			// 
			// TBoxOutputs
			// 
			this->TBoxOutputs->Location = System::Drawing::Point(164, 110);
			this->TBoxOutputs->Name = L"TBoxOutputs";
			this->TBoxOutputs->ReadOnly = true;
			this->TBoxOutputs->Size = System::Drawing::Size(131, 22);
			this->TBoxOutputs->TabIndex = 29;
			// 
			// LOutputs
			// 
			this->LOutputs->AutoSize = true;
			this->LOutputs->Location = System::Drawing::Point(6, 115);
			this->LOutputs->Name = L"LOutputs";
			this->LOutputs->Size = System::Drawing::Size(129, 17);
			this->LOutputs->TabIndex = 28;
			this->LOutputs->Text = L"Number of outputs:";
			// 
			// TBoxQLearningRate
			// 
			this->TBoxQLearningRate->Location = System::Drawing::Point(480, 151);
			this->TBoxQLearningRate->Name = L"TBoxQLearningRate";
			this->TBoxQLearningRate->ReadOnly = true;
			this->TBoxQLearningRate->Size = System::Drawing::Size(146, 22);
			this->TBoxQLearningRate->TabIndex = 27;
			// 
			// TBoxRMSAccuracy
			// 
			this->TBoxRMSAccuracy->Location = System::Drawing::Point(480, 111);
			this->TBoxRMSAccuracy->Name = L"TBoxRMSAccuracy";
			this->TBoxRMSAccuracy->ReadOnly = true;
			this->TBoxRMSAccuracy->Size = System::Drawing::Size(146, 22);
			this->TBoxRMSAccuracy->TabIndex = 26;
			// 
			// TBoxRMSLearnRate
			// 
			this->TBoxRMSLearnRate->Location = System::Drawing::Point(480, 83);
			this->TBoxRMSLearnRate->Name = L"TBoxRMSLearnRate";
			this->TBoxRMSLearnRate->ReadOnly = true;
			this->TBoxRMSLearnRate->Size = System::Drawing::Size(146, 22);
			this->TBoxRMSLearnRate->TabIndex = 25;
			// 
			// TBoxRMSGamma
			// 
			this->TBoxRMSGamma->Location = System::Drawing::Point(480, 55);
			this->TBoxRMSGamma->Name = L"TBoxRMSGamma";
			this->TBoxRMSGamma->ReadOnly = true;
			this->TBoxRMSGamma->Size = System::Drawing::Size(146, 22);
			this->TBoxRMSGamma->TabIndex = 24;
			// 
			// TBoxTrType
			// 
			this->TBoxTrType->Location = System::Drawing::Point(480, 27);
			this->TBoxTrType->Name = L"TBoxTrType";
			this->TBoxTrType->ReadOnly = true;
			this->TBoxTrType->Size = System::Drawing::Size(146, 22);
			this->TBoxTrType->TabIndex = 23;
			// 
			// TBoxEpoches
			// 
			this->TBoxEpoches->Location = System::Drawing::Point(164, 221);
			this->TBoxEpoches->Name = L"TBoxEpoches";
			this->TBoxEpoches->ReadOnly = true;
			this->TBoxEpoches->Size = System::Drawing::Size(131, 22);
			this->TBoxEpoches->TabIndex = 22;
			// 
			// TBoxTrAccuracy
			// 
			this->TBoxTrAccuracy->Location = System::Drawing::Point(480, 223);
			this->TBoxTrAccuracy->Name = L"TBoxTrAccuracy";
			this->TBoxTrAccuracy->ReadOnly = true;
			this->TBoxTrAccuracy->Size = System::Drawing::Size(146, 22);
			this->TBoxTrAccuracy->TabIndex = 21;
			// 
			// TBoxTrPeriod
			// 
			this->TBoxTrPeriod->Location = System::Drawing::Point(480, 195);
			this->TBoxTrPeriod->Name = L"TBoxTrPeriod";
			this->TBoxTrPeriod->ReadOnly = true;
			this->TBoxTrPeriod->Size = System::Drawing::Size(146, 22);
			this->TBoxTrPeriod->TabIndex = 20;
			// 
			// TBoxEpochTests
			// 
			this->TBoxEpochTests->Location = System::Drawing::Point(164, 193);
			this->TBoxEpochTests->Name = L"TBoxEpochTests";
			this->TBoxEpochTests->ReadOnly = true;
			this->TBoxEpochTests->Size = System::Drawing::Size(131, 22);
			this->TBoxEpochTests->TabIndex = 19;
			// 
			// TBoxTotalTestsNumber
			// 
			this->TBoxTotalTestsNumber->Location = System::Drawing::Point(164, 166);
			this->TBoxTotalTestsNumber->Name = L"TBoxTotalTestsNumber";
			this->TBoxTotalTestsNumber->ReadOnly = true;
			this->TBoxTotalTestsNumber->Size = System::Drawing::Size(131, 22);
			this->TBoxTotalTestsNumber->TabIndex = 18;
			// 
			// TBoxActFunc
			// 
			this->TBoxActFunc->Location = System::Drawing::Point(164, 138);
			this->TBoxActFunc->Name = L"TBoxActFunc";
			this->TBoxActFunc->ReadOnly = true;
			this->TBoxActFunc->Size = System::Drawing::Size(131, 22);
			this->TBoxActFunc->TabIndex = 17;
			// 
			// TBoxHLNeurons
			// 
			this->TBoxHLNeurons->Location = System::Drawing::Point(164, 82);
			this->TBoxHLNeurons->Name = L"TBoxHLNeurons";
			this->TBoxHLNeurons->ReadOnly = true;
			this->TBoxHLNeurons->Size = System::Drawing::Size(131, 22);
			this->TBoxHLNeurons->TabIndex = 16;
			// 
			// TBoxHLayers
			// 
			this->TBoxHLayers->Location = System::Drawing::Point(164, 54);
			this->TBoxHLayers->Name = L"TBoxHLayers";
			this->TBoxHLayers->ReadOnly = true;
			this->TBoxHLayers->Size = System::Drawing::Size(131, 22);
			this->TBoxHLayers->TabIndex = 15;
			// 
			// TBoxInputs
			// 
			this->TBoxInputs->Location = System::Drawing::Point(164, 27);
			this->TBoxInputs->Name = L"TBoxInputs";
			this->TBoxInputs->ReadOnly = true;
			this->TBoxInputs->Size = System::Drawing::Size(131, 22);
			this->TBoxInputs->TabIndex = 14;
			// 
			// LLearningRate
			// 
			this->LLearningRate->AutoSize = true;
			this->LLearningRate->Location = System::Drawing::Point(349, 154);
			this->LLearningRate->Name = L"LLearningRate";
			this->LLearningRate->Size = System::Drawing::Size(113, 17);
			this->LLearningRate->TabIndex = 13;
			this->LLearningRate->Text = L"Q-Learning rate:";
			// 
			// LRMSAccuracy
			// 
			this->LRMSAccuracy->AutoSize = true;
			this->LRMSAccuracy->Location = System::Drawing::Point(349, 114);
			this->LRMSAccuracy->Name = L"LRMSAccuracy";
			this->LRMSAccuracy->Size = System::Drawing::Size(104, 17);
			this->LRMSAccuracy->TabIndex = 12;
			this->LRMSAccuracy->Text = L"RMS Accuracy:";
			// 
			// LRMSLearnRate
			// 
			this->LRMSLearnRate->AutoSize = true;
			this->LRMSLearnRate->Location = System::Drawing::Point(349, 86);
			this->LRMSLearnRate->Name = L"LRMSLearnRate";
			this->LRMSLearnRate->Size = System::Drawing::Size(131, 17);
			this->LRMSLearnRate->TabIndex = 11;
			this->LRMSLearnRate->Text = L"RMS Learning rate:";
			// 
			// LRMSGamma
			// 
			this->LRMSGamma->AutoSize = true;
			this->LRMSGamma->Location = System::Drawing::Point(349, 58);
			this->LRMSGamma->Name = L"LRMSGamma";
			this->LRMSGamma->Size = System::Drawing::Size(95, 17);
			this->LRMSGamma->TabIndex = 10;
			this->LRMSGamma->Text = L"RMS Gamma:";
			// 
			// LTrType
			// 
			this->LTrType->AutoSize = true;
			this->LTrType->Location = System::Drawing::Point(349, 30);
			this->LTrType->Name = L"LTrType";
			this->LTrType->Size = System::Drawing::Size(95, 17);
			this->LTrType->TabIndex = 9;
			this->LTrType->Text = L"Training type:";
			// 
			// LActFunc
			// 
			this->LActFunc->AutoSize = true;
			this->LActFunc->Location = System::Drawing::Point(6, 144);
			this->LActFunc->Name = L"LActFunc";
			this->LActFunc->Size = System::Drawing::Size(127, 17);
			this->LActFunc->TabIndex = 8;
			this->LActFunc->Text = L"Activation function:";
			// 
			// LTrAccuracy
			// 
			this->LTrAccuracy->AutoSize = true;
			this->LTrAccuracy->Location = System::Drawing::Point(329, 226);
			this->LTrAccuracy->Name = L"LTrAccuracy";
			this->LTrAccuracy->Size = System::Drawing::Size(125, 17);
			this->LTrAccuracy->TabIndex = 7;
			this->LTrAccuracy->Text = L"Training accuracy:";
			// 
			// LTrPeriod
			// 
			this->LTrPeriod->AutoSize = true;
			this->LTrPeriod->Location = System::Drawing::Point(329, 198);
			this->LTrPeriod->Name = L"LTrPeriod";
			this->LTrPeriod->Size = System::Drawing::Size(108, 17);
			this->LTrPeriod->TabIndex = 6;
			this->LTrPeriod->Text = L"Training period:";
			// 
			// Epoches
			// 
			this->Epoches->AutoSize = true;
			this->Epoches->Location = System::Drawing::Point(6, 226);
			this->Epoches->Name = L"Epoches";
			this->Epoches->Size = System::Drawing::Size(59, 17);
			this->Epoches->TabIndex = 5;
			this->Epoches->Text = L"Epochs:";
			// 
			// EpochTests
			// 
			this->EpochTests->AutoSize = true;
			this->EpochTests->Location = System::Drawing::Point(6, 196);
			this->EpochTests->Name = L"EpochTests";
			this->EpochTests->Size = System::Drawing::Size(111, 17);
			this->EpochTests->TabIndex = 4;
			this->EpochTests->Text = L"Tests for epoch:";
			// 
			// TotalTestsNumber
			// 
			this->TotalTestsNumber->AutoSize = true;
			this->TotalTestsNumber->Location = System::Drawing::Point(6, 169);
			this->TotalTestsNumber->Name = L"TotalTestsNumber";
			this->TotalTestsNumber->Size = System::Drawing::Size(146, 17);
			this->TotalTestsNumber->TabIndex = 3;
			this->TotalTestsNumber->Text = L"Total number of tests:";
			// 
			// LHLNeurons
			// 
			this->LHLNeurons->AutoSize = true;
			this->LHLNeurons->Location = System::Drawing::Point(6, 85);
			this->LHLNeurons->Name = L"LHLNeurons";
			this->LHLNeurons->Size = System::Drawing::Size(148, 17);
			this->LHLNeurons->TabIndex = 2;
			this->LHLNeurons->Text = L"Hidden layer neurons:";
			// 
			// LHLayers
			// 
			this->LHLayers->AutoSize = true;
			this->LHLayers->Location = System::Drawing::Point(6, 58);
			this->LHLayers->Name = L"LHLayers";
			this->LHLayers->Size = System::Drawing::Size(99, 17);
			this->LHLayers->TabIndex = 1;
			this->LHLayers->Text = L"Hidden layers:";
			// 
			// LInputs
			// 
			this->LInputs->AutoSize = true;
			this->LInputs->Location = System::Drawing::Point(6, 30);
			this->LInputs->Name = L"LInputs";
			this->LInputs->Size = System::Drawing::Size(120, 17);
			this->LInputs->TabIndex = 0;
			this->LInputs->Text = L"Number of inputs:";
			// 
			// BtnRunNNet
			// 
			this->BtnRunNNet->Location = System::Drawing::Point(489, 272);
			this->BtnRunNNet->Name = L"BtnRunNNet";
			this->BtnRunNNet->Size = System::Drawing::Size(152, 40);
			this->BtnRunNNet->TabIndex = 5;
			this->BtnRunNNet->Text = L"Run";
			this->BtnRunNNet->UseVisualStyleBackColor = true;
			this->BtnRunNNet->Click += gcnew System::EventHandler(this, &MainForm::BtnRunNNet_Click);
			// 
			// BtnTrainNNet
			// 
			this->BtnTrainNNet->Location = System::Drawing::Point(489, 216);
			this->BtnTrainNNet->Name = L"BtnTrainNNet";
			this->BtnTrainNNet->Size = System::Drawing::Size(152, 40);
			this->BtnTrainNNet->TabIndex = 4;
			this->BtnTrainNNet->Text = L"Train";
			this->BtnTrainNNet->UseVisualStyleBackColor = true;
			this->BtnTrainNNet->Click += gcnew System::EventHandler(this, &MainForm::BtnTrainNNet_Click);
			// 
			// BtnEditNNet
			// 
			this->BtnEditNNet->Location = System::Drawing::Point(489, 33);
			this->BtnEditNNet->Name = L"BtnEditNNet";
			this->BtnEditNNet->Size = System::Drawing::Size(152, 40);
			this->BtnEditNNet->TabIndex = 3;
			this->BtnEditNNet->Text = L"Edit";
			this->BtnEditNNet->UseVisualStyleBackColor = true;
			this->BtnEditNNet->Click += gcnew System::EventHandler(this, &MainForm::BtnEditNNet_Click);
			// 
			// PBoxNNCreature
			// 
			this->PBoxNNCreature->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->PBoxNNCreature->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->PBoxNNCreature->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->PBoxNNCreature->Location = System::Drawing::Point(6, 33);
			this->PBoxNNCreature->Name = L"PBoxNNCreature";
			this->PBoxNNCreature->Size = System::Drawing::Size(448, 279);
			this->PBoxNNCreature->TabIndex = 0;
			this->PBoxNNCreature->TabStop = false;
			// 
			// BtnDeleteNNet
			// 
			this->BtnDeleteNNet->Location = System::Drawing::Point(489, 96);
			this->BtnDeleteNNet->Name = L"BtnDeleteNNet";
			this->BtnDeleteNNet->Size = System::Drawing::Size(152, 40);
			this->BtnDeleteNNet->TabIndex = 2;
			this->BtnDeleteNNet->Text = L"Delete";
			this->BtnDeleteNNet->UseVisualStyleBackColor = true;
			this->BtnDeleteNNet->Click += gcnew System::EventHandler(this, &MainForm::BtnDeleteNNet_Click);
			// 
			// GrBoxNNList
			// 
			this->GrBoxNNList->Controls->Add(this->ListBoxNN);
			this->GrBoxNNList->Controls->Add(this->BtnNewNN);
			this->GrBoxNNList->Location = System::Drawing::Point(11, 24);
			this->GrBoxNNList->Name = L"GrBoxNNList";
			this->GrBoxNNList->Size = System::Drawing::Size(314, 616);
			this->GrBoxNNList->TabIndex = 0;
			this->GrBoxNNList->TabStop = false;
			this->GrBoxNNList->Text = L"Neural Network List";
			// 
			// ListBoxNN
			// 
			this->ListBoxNN->FormattingEnabled = true;
			this->ListBoxNN->ItemHeight = 16;
			this->ListBoxNN->Location = System::Drawing::Point(17, 33);
			this->ListBoxNN->Name = L"ListBoxNN";
			this->ListBoxNN->Size = System::Drawing::Size(280, 500);
			this->ListBoxNN->TabIndex = 3;
			this->ListBoxNN->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::ListBoxNN_SelectedIndexChanged);
			// 
			// BtnNewNN
			// 
			this->BtnNewNN->Location = System::Drawing::Point(89, 559);
			this->BtnNewNN->Name = L"BtnNewNN";
			this->BtnNewNN->Size = System::Drawing::Size(132, 40);
			this->BtnNewNN->TabIndex = 1;
			this->BtnNewNN->Text = L"New NeuroNet";
			this->BtnNewNN->UseVisualStyleBackColor = true;
			this->BtnNewNN->Click += gcnew System::EventHandler(this, &MainForm::BtnNewNN_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1027, 677);
			this->Controls->Add(this->PanelMain);
			this->Controls->Add(this->MenuStripMain);
			this->MainMenuStrip = this->MenuStripMain;
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(1045, 724);
			this->MinimumSize = System::Drawing::Size(1045, 724);
			this->Name = L"MainForm";
			this->Text = L"NeuroNet Editor";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MainForm::MainForm_FormClosing);
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->MenuStripMain->ResumeLayout(false);
			this->MenuStripMain->PerformLayout();
			this->PanelMain->ResumeLayout(false);
			this->GrBoxSelectedNN->ResumeLayout(false);
			this->GrBoxNNetSettings->ResumeLayout(false);
			this->GrBoxNNetSettings->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PBoxNNCreature))->EndInit();
			this->GrBoxNNList->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


	private: System::Void MainForm_Load(System::Object^  sender, System::EventArgs^  e) {
		// Чтение информации о моделях объектов
		WIN32_FIND_DATA cFindFileData;
		HANDLE chf = FindFirstFile(creatures_dir, &cFindFileData);
		std::vector<std::string> cfilenames;
		if (chf != INVALID_HANDLE_VALUE)
		{
			do
			{
				std::basic_string<TCHAR> ws(cFindFileData.cFileName);
				std::string fname(ws.begin(), ws.end());
				cfilenames.push_back(fname);
			} while (FindNextFile(chf, &cFindFileData) != 0);
			FindClose(chf);
		}
		else {
			MessageBox::Show("Директории \"Creatures\" не содержит файлов или не существует");
		}

		for (int i = 0; i < cfilenames.size(); ++i) {
			Creature next_creature = creatureFileParser(creatures_dir_str + cfilenames[i]);
			std::string creaturename = cfilenames[i].substr(0, cfilenames[i].size() - creature_finame_end.size());
			next_creature.name = creaturename;
			creatures_names[creaturename] = i;
			creatures.push_back(next_creature);
		}

		// Чтение информации о нейронках
		WIN32_FIND_DATA nnFindFileData;
		HANDLE nnhf = FindFirstFile(nnets_dir, &nnFindFileData);
		std::vector<std::string> nnfilenames;
		if (nnhf != INVALID_HANDLE_VALUE)
		{
			do
			{
				std::basic_string<TCHAR> ws(nnFindFileData.cFileName);
				std::string fname(ws.begin(), ws.end());
				nnfilenames.push_back(fname);
			} while (FindNextFile(nnhf, &nnFindFileData) != 0);
			FindClose(nnhf);
		}
		else {
			MessageBox::Show("Директории \"NNets\" не содержит файлов или не существует");
		}

		for (int i = 0; i < nnfilenames.size(); ++i) {
			NNet next_nnet = nnetFileParser(nnets_dir_str + nnfilenames[i]);
			if (next_nnet.creature_name != "") { // провкрка, что данные являются корректными
				std::string nnetname = nnfilenames[i].substr(0, nnfilenames[i].size() - nnet_finame_end.size());
				next_nnet.name = nnetname;
				if (creatures_names.count(next_nnet.creature_name) != 0) { // наличие такого существа
					int crpos = creatures_names[next_nnet.creature_name];
					next_nnet.inputs_num = creatures[crpos].joints.size() * 2;
					next_nnet.outputs_num = creatures[crpos].movable_lines.size() * 2;
					nnets_names[nnetname] = i;
					nnets.push_back(next_nnet);
				}
			}
		}

		for (int i = 0; i < nnets.size(); ++i) {
			String^ s = gcnew String(nnets[i].name.c_str());
			ListBoxNN->Items->Add(s);
			delete s;
		}

		BtnEditNNet->Enabled = false;
		BtnDeleteNNet->Enabled = false;
		BtnRunNNet->Enabled = false;
		BtnTrainNNet->Enabled = false;
	}

	private: System::Void BtnNewNN_Click(System::Object^  sender, System::EventArgs^  e) {
		NeuroNetEditor^ nnet_editor_form = gcnew NeuroNetEditor();
		edit_nnet_pos = -1;
		nnet_editor_form->ShowDialog();
		delete nnet_editor_form;

		ListBoxNN->SelectedIndex = -1;
		ListBoxNN->Items->Clear();
		for (int i = 0; i < nnets.size(); ++i) {
			if (!nnets[i].deleted) {
				String^ s = gcnew String(nnets[i].name.c_str());
				ListBoxNN->Items->Add(s);
				delete s;
			}
		}
	}

	private: System::Void BtnTrainNNet_Click(System::Object^  sender, System::EventArgs^  e) {
		//WinExec("Test_Graphics.exe", SW_SHOW);
		std::string nnname = msclr::interop::marshal_as<std::string>(ListBoxNN->SelectedItem->ToString());
		nnname += " 1";
		std::wstring wstr(nnname.begin(), nnname.end());
		LPCWSTR paramstr = wstr.c_str();
		ShellExecute(0, L"open", L"CreatureNeuroNet.exe", paramstr, 0, SW_SHOW);
	}

	private: System::Void MainForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
		if (MessageBox::Show(this, "Закрыть программу?", "Form Closing", MessageBoxButtons::YesNo) == System::Windows::Forms::DialogResult::Yes)
		{
			//HWND hWnd = FindWindow(NULL, L"Test_1");
			//if (IsWindow(hWnd)) SendMessage(hWnd, WM_SYSCOMMAND, SC_CLOSE, 0);
		}
		else {
			e->Cancel = true;
		}
	}
	private: System::Void BtnRunNNet_Click(System::Object^  sender, System::EventArgs^  e) {

	}

	private: System::Void ListBoxNN_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		if (ListBoxNN->SelectedIndex != -1) {
			std::string nnname = msclr::interop::marshal_as<std::string>(ListBoxNN->SelectedItem->ToString());
			int nnpos = nnets_names[nnname];

			std::string imgname = creatures_dir_str + nnets[nnpos].creature_name + img_finame_end;
			String^ simgfile = gcnew String(imgname.c_str());
			PBoxNNCreature->BackgroundImage = Image::FromFile(simgfile);
			PBoxNNCreature->BackgroundImageLayout = ImageLayout::Zoom;
			delete simgfile;

			TBoxInputs->Text = Convert::ToString(nnets[nnpos].inputs_num);
			TBoxHLayers->Text = Convert::ToString(nnets[nnpos].hidden_layers_num);
			TBoxHLNeurons->Text = Convert::ToString(nnets[nnpos].hidden_layer_neurons);
			TBoxOutputs->Text = Convert::ToString(nnets[nnpos].outputs_num);

			String^ afstr;
			switch (nnets[nnpos].act_func) {
			case LINE: afstr = gcnew String("LINE"); break;
			case TANH: afstr = gcnew String("TANH"); break;
			case SGMD: afstr = gcnew String("SGMD"); break;
			default: break;
			}
			TBoxActFunc->Text = afstr;
			delete afstr;

			TBoxTotalTestsNumber->Text = Convert::ToString(nnets[nnpos].tests_total_num);
			TBoxEpochTests->Text = Convert::ToString(nnets[nnpos].epoch_tests_num);
			TBoxEpoches->Text = Convert::ToString(nnets[nnpos].epoch_num);

			String^ trtstr;
			switch (nnets[nnpos].training_type) {
			case RMS: trtstr = gcnew String("RMS"); break;
			default: break;
			}
			TBoxTrType->Text = trtstr;
			delete trtstr;

			TBoxRMSGamma->Text = Convert::ToString(nnets[nnpos].rms_gamma);
			TBoxRMSLearnRate->Text = Convert::ToString(nnets[nnpos].rms_learning_rate);
			TBoxRMSAccuracy->Text = Convert::ToString(nnets[nnpos].rms_accuracy);
			TBoxQLearningRate->Text = Convert::ToString(nnets[nnpos].qlearn_rate);
			TBoxTrPeriod->Text = Convert::ToString(nnets[nnpos].training_period);
			TBoxTrAccuracy->Text = Convert::ToString(nnets[nnpos].training_accuracy);

			BtnEditNNet->Enabled = true;
			BtnDeleteNNet->Enabled = true;
			BtnRunNNet->Enabled = true;
			BtnTrainNNet->Enabled = true;
		}
		else {
			Image^ tmping = PBoxNNCreature->BackgroundImage;
			PBoxNNCreature->BackgroundImage = nullptr;
			delete tmping;
			TBoxInputs->Text = L"";
			TBoxHLayers->Text = L"";
			TBoxHLNeurons->Text = L"";
			TBoxOutputs->Text = L"";
			TBoxActFunc->Text = L"";
			TBoxTotalTestsNumber->Text = L"";
			TBoxEpochTests->Text = L"";
			TBoxEpoches->Text = L"";
			TBoxTrType->Text = L"";
			TBoxRMSGamma->Text = L"";
			TBoxRMSLearnRate->Text = L"";
			TBoxRMSAccuracy->Text = L"";
			TBoxQLearningRate->Text = L"";
			TBoxTrPeriod->Text = L"";
			TBoxTrAccuracy->Text = L"";

			BtnEditNNet->Enabled = false;
			BtnDeleteNNet->Enabled = false;
			BtnRunNNet->Enabled = false;
			BtnTrainNNet->Enabled = false;
		}
	}

	private: System::Void BtnEditNNet_Click(System::Object^  sender, System::EventArgs^  e) {
		NeuroNetEditor^ nnet_editor_form = gcnew NeuroNetEditor();
		std::string nnname = msclr::interop::marshal_as<std::string>(ListBoxNN->SelectedItem->ToString());
		edit_nnet_pos = nnets_names[nnname];
		int tmppos = edit_nnet_pos;
		nnet_editor_form->ShowDialog();
		ListBoxNN->SelectedIndex = -1;
		ListBoxNN->SelectedIndex = tmppos;
		delete nnet_editor_form;
	}
	private: System::Void BtnDeleteNNet_Click(System::Object^  sender, System::EventArgs^  e) {
		std::string nnname = msclr::interop::marshal_as<std::string>(ListBoxNN->SelectedItem->ToString());
		int nnpos = nnets_names[nnname];

		if (MessageBox::Show(this, "Удалить нейронную сеть?", "NNet Deleting", MessageBoxButtons::YesNo) == System::Windows::Forms::DialogResult::Yes)
		{
			std::string nnfname = nnets_dir_str + nnname + nnet_finame_end;
			if (!remove(nnfname.c_str())) {
				nnets[nnpos].deleted = true;
				int selected_ind = ListBoxNN->SelectedIndex;
				ListBoxNN->SelectedIndex = -1;
				ListBoxNN->Items->RemoveAt(selected_ind);
				//удаление файлов при закрытии приложения (убрать из этого события)
				MessageBox::Show("Нейронная сеть удалена");
			}
			else {
				MessageBox::Show("Ошибка удаления нейронной сети");
			}
		}
	}

	};
}
