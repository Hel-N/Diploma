#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include"Creator.h"

namespace NeuroNetDesigner {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for NeuroNetEditor
	/// </summary>
	public ref class NeuroNetEditor : public System::Windows::Forms::Form
	{
	public:
		NeuroNetEditor(void)
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
		~NeuroNetEditor()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  LNNetName;
	protected:

	private: System::Windows::Forms::TextBox^  TBoxNNetName;
	private: System::Windows::Forms::GroupBox^  GrBoxNNetParam;
	private: System::Windows::Forms::Label^  LOutputsEdit;

	private: System::Windows::Forms::Label^  LActFunc;
	private: System::Windows::Forms::Label^  LEpoch;




	private: System::Windows::Forms::Label^  LEpochTestsNum;

	private: System::Windows::Forms::Label^  LTotalNumTests;

	private: System::Windows::Forms::Label^  LHLNeurons;


	private: System::Windows::Forms::Label^  LHidLayers;
	private: System::Windows::Forms::Label^  LBoxInputsEdit;



	private: System::Windows::Forms::GroupBox^  GrBoxCreatureModel;
	private: System::Windows::Forms::PictureBox^  PBoxCreatureModel;
	private: System::Windows::Forms::Button^  BtnNewModel;















	private: System::Windows::Forms::TextBox^  TBoxOutputsEdit;


	private: System::Windows::Forms::TextBox^  TBoxInputsEdit;
	private: System::Windows::Forms::GroupBox^  GrBoxLearnAlgParam;






	private: System::Windows::Forms::Label^  LTrAccuracy;


	private: System::Windows::Forms::Label^  LTrPeriod;










	private: System::Windows::Forms::Label^  LLearnRate;



	private: System::Windows::Forms::Label^  LRMSAccuracy;

	private: System::Windows::Forms::Label^  LRMSLearnRate;

	private: System::Windows::Forms::Label^  LRMSGamma;

	private: System::Windows::Forms::Label^  LRMSType;

	private: System::Windows::Forms::Button^  BtnSaveNNetParam;
	private: System::Windows::Forms::Button^  BtnCancel;
	private: System::Windows::Forms::ListBox^  ListBoxCreatures;
	private: System::Windows::Forms::ComboBox^  ComBoxActFunc;
	private: System::Windows::Forms::ComboBox^  ComBoxTrType;
	private: System::Windows::Forms::NumericUpDown^  NumUpDownHLNeurons;
	private: System::Windows::Forms::NumericUpDown^  NumUpDownHidLayers;
	private: System::Windows::Forms::NumericUpDown^  NumUpDownTotalNumTests;
	private: System::Windows::Forms::NumericUpDown^  NumUpDownEpochTestsNum;
	private: System::Windows::Forms::NumericUpDown^  NumUpDownEpoch;
	private: System::Windows::Forms::NumericUpDown^  NumUpDownTrPeriod;
	private: System::Windows::Forms::NumericUpDown^  NumUpDownTrAccuracy;
	private: System::Windows::Forms::NumericUpDown^  NumUpDownRMSGamma;
	private: System::Windows::Forms::NumericUpDown^  NumUpDownRMSLearnRate;
	private: System::Windows::Forms::NumericUpDown^  NumUpDownRMSAccuracy;
	private: System::Windows::Forms::NumericUpDown^  NumUpDownQLearnRate;



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
			this->LNNetName = (gcnew System::Windows::Forms::Label());
			this->TBoxNNetName = (gcnew System::Windows::Forms::TextBox());
			this->GrBoxNNetParam = (gcnew System::Windows::Forms::GroupBox());
			this->NumUpDownTrAccuracy = (gcnew System::Windows::Forms::NumericUpDown());
			this->NumUpDownTrPeriod = (gcnew System::Windows::Forms::NumericUpDown());
			this->NumUpDownEpoch = (gcnew System::Windows::Forms::NumericUpDown());
			this->NumUpDownEpochTestsNum = (gcnew System::Windows::Forms::NumericUpDown());
			this->NumUpDownTotalNumTests = (gcnew System::Windows::Forms::NumericUpDown());
			this->NumUpDownHLNeurons = (gcnew System::Windows::Forms::NumericUpDown());
			this->NumUpDownHidLayers = (gcnew System::Windows::Forms::NumericUpDown());
			this->ComBoxActFunc = (gcnew System::Windows::Forms::ComboBox());
			this->LTrAccuracy = (gcnew System::Windows::Forms::Label());
			this->LTrPeriod = (gcnew System::Windows::Forms::Label());
			this->TBoxOutputsEdit = (gcnew System::Windows::Forms::TextBox());
			this->TBoxInputsEdit = (gcnew System::Windows::Forms::TextBox());
			this->LOutputsEdit = (gcnew System::Windows::Forms::Label());
			this->LActFunc = (gcnew System::Windows::Forms::Label());
			this->LEpoch = (gcnew System::Windows::Forms::Label());
			this->LEpochTestsNum = (gcnew System::Windows::Forms::Label());
			this->LTotalNumTests = (gcnew System::Windows::Forms::Label());
			this->LHLNeurons = (gcnew System::Windows::Forms::Label());
			this->LHidLayers = (gcnew System::Windows::Forms::Label());
			this->LBoxInputsEdit = (gcnew System::Windows::Forms::Label());
			this->GrBoxCreatureModel = (gcnew System::Windows::Forms::GroupBox());
			this->ListBoxCreatures = (gcnew System::Windows::Forms::ListBox());
			this->BtnNewModel = (gcnew System::Windows::Forms::Button());
			this->PBoxCreatureModel = (gcnew System::Windows::Forms::PictureBox());
			this->GrBoxLearnAlgParam = (gcnew System::Windows::Forms::GroupBox());
			this->NumUpDownQLearnRate = (gcnew System::Windows::Forms::NumericUpDown());
			this->NumUpDownRMSAccuracy = (gcnew System::Windows::Forms::NumericUpDown());
			this->NumUpDownRMSLearnRate = (gcnew System::Windows::Forms::NumericUpDown());
			this->NumUpDownRMSGamma = (gcnew System::Windows::Forms::NumericUpDown());
			this->ComBoxTrType = (gcnew System::Windows::Forms::ComboBox());
			this->LLearnRate = (gcnew System::Windows::Forms::Label());
			this->LRMSAccuracy = (gcnew System::Windows::Forms::Label());
			this->LRMSLearnRate = (gcnew System::Windows::Forms::Label());
			this->LRMSGamma = (gcnew System::Windows::Forms::Label());
			this->LRMSType = (gcnew System::Windows::Forms::Label());
			this->BtnSaveNNetParam = (gcnew System::Windows::Forms::Button());
			this->BtnCancel = (gcnew System::Windows::Forms::Button());
			this->GrBoxNNetParam->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->NumUpDownTrAccuracy))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->NumUpDownTrPeriod))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->NumUpDownEpoch))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->NumUpDownEpochTestsNum))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->NumUpDownTotalNumTests))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->NumUpDownHLNeurons))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->NumUpDownHidLayers))->BeginInit();
			this->GrBoxCreatureModel->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PBoxCreatureModel))->BeginInit();
			this->GrBoxLearnAlgParam->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->NumUpDownQLearnRate))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->NumUpDownRMSAccuracy))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->NumUpDownRMSLearnRate))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->NumUpDownRMSGamma))->BeginInit();
			this->SuspendLayout();
			// 
			// LNNetName
			// 
			this->LNNetName->AutoSize = true;
			this->LNNetName->Location = System::Drawing::Point(12, 40);
			this->LNNetName->Name = L"LNNetName";
			this->LNNetName->Size = System::Drawing::Size(114, 17);
			this->LNNetName->TabIndex = 0;
			this->LNNetName->Text = L"NeuroNet Name:";
			// 
			// TBoxNNetName
			// 
			this->TBoxNNetName->Location = System::Drawing::Point(132, 40);
			this->TBoxNNetName->Name = L"TBoxNNetName";
			this->TBoxNNetName->Size = System::Drawing::Size(294, 22);
			this->TBoxNNetName->TabIndex = 1;
			// 
			// GrBoxNNetParam
			// 
			this->GrBoxNNetParam->Controls->Add(this->NumUpDownTrAccuracy);
			this->GrBoxNNetParam->Controls->Add(this->NumUpDownTrPeriod);
			this->GrBoxNNetParam->Controls->Add(this->NumUpDownEpoch);
			this->GrBoxNNetParam->Controls->Add(this->NumUpDownEpochTestsNum);
			this->GrBoxNNetParam->Controls->Add(this->NumUpDownTotalNumTests);
			this->GrBoxNNetParam->Controls->Add(this->NumUpDownHLNeurons);
			this->GrBoxNNetParam->Controls->Add(this->NumUpDownHidLayers);
			this->GrBoxNNetParam->Controls->Add(this->ComBoxActFunc);
			this->GrBoxNNetParam->Controls->Add(this->LTrAccuracy);
			this->GrBoxNNetParam->Controls->Add(this->LTrPeriod);
			this->GrBoxNNetParam->Controls->Add(this->TBoxOutputsEdit);
			this->GrBoxNNetParam->Controls->Add(this->TBoxInputsEdit);
			this->GrBoxNNetParam->Controls->Add(this->LOutputsEdit);
			this->GrBoxNNetParam->Controls->Add(this->LActFunc);
			this->GrBoxNNetParam->Controls->Add(this->LEpoch);
			this->GrBoxNNetParam->Controls->Add(this->LEpochTestsNum);
			this->GrBoxNNetParam->Controls->Add(this->LTotalNumTests);
			this->GrBoxNNetParam->Controls->Add(this->LHLNeurons);
			this->GrBoxNNetParam->Controls->Add(this->LHidLayers);
			this->GrBoxNNetParam->Controls->Add(this->LBoxInputsEdit);
			this->GrBoxNNetParam->Location = System::Drawing::Point(311, 79);
			this->GrBoxNNetParam->Name = L"GrBoxNNetParam";
			this->GrBoxNNetParam->Size = System::Drawing::Size(390, 326);
			this->GrBoxNNetParam->TabIndex = 2;
			this->GrBoxNNetParam->TabStop = false;
			this->GrBoxNNetParam->Text = L"Neural Network Parameters";
			// 
			// NumUpDownTrAccuracy
			// 
			this->NumUpDownTrAccuracy->DecimalPlaces = 10;
			this->NumUpDownTrAccuracy->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 196608 });
			this->NumUpDownTrAccuracy->Location = System::Drawing::Point(162, 288);
			this->NumUpDownTrAccuracy->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
			this->NumUpDownTrAccuracy->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 655360 });
			this->NumUpDownTrAccuracy->Name = L"NumUpDownTrAccuracy";
			this->NumUpDownTrAccuracy->Size = System::Drawing::Size(214, 22);
			this->NumUpDownTrAccuracy->TabIndex = 55;
			this->NumUpDownTrAccuracy->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 655360 });
			// 
			// NumUpDownTrPeriod
			// 
			this->NumUpDownTrPeriod->Location = System::Drawing::Point(162, 260);
			this->NumUpDownTrPeriod->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100000, 0, 0, 0 });
			this->NumUpDownTrPeriod->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->NumUpDownTrPeriod->Name = L"NumUpDownTrPeriod";
			this->NumUpDownTrPeriod->Size = System::Drawing::Size(214, 22);
			this->NumUpDownTrPeriod->TabIndex = 7;
			this->NumUpDownTrPeriod->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			// 
			// NumUpDownEpoch
			// 
			this->NumUpDownEpoch->Location = System::Drawing::Point(162, 230);
			this->NumUpDownEpoch->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100000, 0, 0, 0 });
			this->NumUpDownEpoch->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->NumUpDownEpoch->Name = L"NumUpDownEpoch";
			this->NumUpDownEpoch->Size = System::Drawing::Size(214, 22);
			this->NumUpDownEpoch->TabIndex = 54;
			this->NumUpDownEpoch->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			// 
			// NumUpDownEpochTestsNum
			// 
			this->NumUpDownEpochTestsNum->Location = System::Drawing::Point(162, 202);
			this->NumUpDownEpochTestsNum->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100000, 0, 0, 0 });
			this->NumUpDownEpochTestsNum->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->NumUpDownEpochTestsNum->Name = L"NumUpDownEpochTestsNum";
			this->NumUpDownEpochTestsNum->Size = System::Drawing::Size(214, 22);
			this->NumUpDownEpochTestsNum->TabIndex = 53;
			this->NumUpDownEpochTestsNum->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			// 
			// NumUpDownTotalNumTests
			// 
			this->NumUpDownTotalNumTests->Location = System::Drawing::Point(162, 174);
			this->NumUpDownTotalNumTests->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100000, 0, 0, 0 });
			this->NumUpDownTotalNumTests->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->NumUpDownTotalNumTests->Name = L"NumUpDownTotalNumTests";
			this->NumUpDownTotalNumTests->Size = System::Drawing::Size(214, 22);
			this->NumUpDownTotalNumTests->TabIndex = 52;
			this->NumUpDownTotalNumTests->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			// 
			// NumUpDownHLNeurons
			// 
			this->NumUpDownHLNeurons->Location = System::Drawing::Point(162, 91);
			this->NumUpDownHLNeurons->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100000, 0, 0, 0 });
			this->NumUpDownHLNeurons->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->NumUpDownHLNeurons->Name = L"NumUpDownHLNeurons";
			this->NumUpDownHLNeurons->Size = System::Drawing::Size(214, 22);
			this->NumUpDownHLNeurons->TabIndex = 51;
			this->NumUpDownHLNeurons->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			// 
			// NumUpDownHidLayers
			// 
			this->NumUpDownHidLayers->Location = System::Drawing::Point(162, 64);
			this->NumUpDownHidLayers->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100000, 0, 0, 0 });
			this->NumUpDownHidLayers->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->NumUpDownHidLayers->Name = L"NumUpDownHidLayers";
			this->NumUpDownHidLayers->Size = System::Drawing::Size(214, 22);
			this->NumUpDownHidLayers->TabIndex = 50;
			this->NumUpDownHidLayers->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			// 
			// ComBoxActFunc
			// 
			this->ComBoxActFunc->FormattingEnabled = true;
			this->ComBoxActFunc->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"LINE", L"TANH", L"SGMD" });
			this->ComBoxActFunc->Location = System::Drawing::Point(162, 146);
			this->ComBoxActFunc->Name = L"ComBoxActFunc";
			this->ComBoxActFunc->Size = System::Drawing::Size(214, 24);
			this->ComBoxActFunc->TabIndex = 49;
			// 
			// LTrAccuracy
			// 
			this->LTrAccuracy->AutoSize = true;
			this->LTrAccuracy->Location = System::Drawing::Point(6, 290);
			this->LTrAccuracy->Name = L"LTrAccuracy";
			this->LTrAccuracy->Size = System::Drawing::Size(125, 17);
			this->LTrAccuracy->TabIndex = 46;
			this->LTrAccuracy->Text = L"Training accuracy:";
			// 
			// LTrPeriod
			// 
			this->LTrPeriod->AutoSize = true;
			this->LTrPeriod->Location = System::Drawing::Point(7, 262);
			this->LTrPeriod->Name = L"LTrPeriod";
			this->LTrPeriod->Size = System::Drawing::Size(108, 17);
			this->LTrPeriod->TabIndex = 45;
			this->LTrPeriod->Text = L"Training period:";
			// 
			// TBoxOutputsEdit
			// 
			this->TBoxOutputsEdit->Location = System::Drawing::Point(162, 117);
			this->TBoxOutputsEdit->Name = L"TBoxOutputsEdit";
			this->TBoxOutputsEdit->ReadOnly = true;
			this->TBoxOutputsEdit->Size = System::Drawing::Size(214, 22);
			this->TBoxOutputsEdit->TabIndex = 38;
			// 
			// TBoxInputsEdit
			// 
			this->TBoxInputsEdit->Location = System::Drawing::Point(162, 35);
			this->TBoxInputsEdit->Name = L"TBoxInputsEdit";
			this->TBoxInputsEdit->ReadOnly = true;
			this->TBoxInputsEdit->Size = System::Drawing::Size(214, 22);
			this->TBoxInputsEdit->TabIndex = 37;
			// 
			// LOutputsEdit
			// 
			this->LOutputsEdit->AutoSize = true;
			this->LOutputsEdit->Location = System::Drawing::Point(6, 120);
			this->LOutputsEdit->Name = L"LOutputsEdit";
			this->LOutputsEdit->Size = System::Drawing::Size(129, 17);
			this->LOutputsEdit->TabIndex = 36;
			this->LOutputsEdit->Text = L"Number of outputs:";
			// 
			// LActFunc
			// 
			this->LActFunc->AutoSize = true;
			this->LActFunc->Location = System::Drawing::Point(6, 149);
			this->LActFunc->Name = L"LActFunc";
			this->LActFunc->Size = System::Drawing::Size(127, 17);
			this->LActFunc->TabIndex = 35;
			this->LActFunc->Text = L"Activation function:";
			// 
			// LEpoch
			// 
			this->LEpoch->AutoSize = true;
			this->LEpoch->Location = System::Drawing::Point(6, 232);
			this->LEpoch->Name = L"LEpoch";
			this->LEpoch->Size = System::Drawing::Size(59, 17);
			this->LEpoch->TabIndex = 34;
			this->LEpoch->Text = L"Epochs:";
			// 
			// LEpochTestsNum
			// 
			this->LEpochTestsNum->AutoSize = true;
			this->LEpochTestsNum->Location = System::Drawing::Point(6, 204);
			this->LEpochTestsNum->Name = L"LEpochTestsNum";
			this->LEpochTestsNum->Size = System::Drawing::Size(111, 17);
			this->LEpochTestsNum->TabIndex = 33;
			this->LEpochTestsNum->Text = L"Tests for epoch:";
			// 
			// LTotalNumTests
			// 
			this->LTotalNumTests->AutoSize = true;
			this->LTotalNumTests->Location = System::Drawing::Point(6, 177);
			this->LTotalNumTests->Name = L"LTotalNumTests";
			this->LTotalNumTests->Size = System::Drawing::Size(146, 17);
			this->LTotalNumTests->TabIndex = 32;
			this->LTotalNumTests->Text = L"Total number of tests:";
			// 
			// LHLNeurons
			// 
			this->LHLNeurons->AutoSize = true;
			this->LHLNeurons->Location = System::Drawing::Point(6, 93);
			this->LHLNeurons->Name = L"LHLNeurons";
			this->LHLNeurons->Size = System::Drawing::Size(148, 17);
			this->LHLNeurons->TabIndex = 31;
			this->LHLNeurons->Text = L"Hidden layer neurons:";
			// 
			// LHidLayers
			// 
			this->LHidLayers->AutoSize = true;
			this->LHidLayers->Location = System::Drawing::Point(6, 66);
			this->LHidLayers->Name = L"LHidLayers";
			this->LHidLayers->Size = System::Drawing::Size(99, 17);
			this->LHidLayers->TabIndex = 30;
			this->LHidLayers->Text = L"Hidden layers:";
			// 
			// LBoxInputsEdit
			// 
			this->LBoxInputsEdit->AutoSize = true;
			this->LBoxInputsEdit->Location = System::Drawing::Point(6, 38);
			this->LBoxInputsEdit->Name = L"LBoxInputsEdit";
			this->LBoxInputsEdit->Size = System::Drawing::Size(120, 17);
			this->LBoxInputsEdit->TabIndex = 29;
			this->LBoxInputsEdit->Text = L"Number of inputs:";
			// 
			// GrBoxCreatureModel
			// 
			this->GrBoxCreatureModel->Controls->Add(this->ListBoxCreatures);
			this->GrBoxCreatureModel->Controls->Add(this->BtnNewModel);
			this->GrBoxCreatureModel->Controls->Add(this->PBoxCreatureModel);
			this->GrBoxCreatureModel->Location = System::Drawing::Point(12, 79);
			this->GrBoxCreatureModel->Name = L"GrBoxCreatureModel";
			this->GrBoxCreatureModel->Size = System::Drawing::Size(293, 606);
			this->GrBoxCreatureModel->TabIndex = 3;
			this->GrBoxCreatureModel->TabStop = false;
			this->GrBoxCreatureModel->Text = L"Creature Model";
			// 
			// ListBoxCreatures
			// 
			this->ListBoxCreatures->FormattingEnabled = true;
			this->ListBoxCreatures->ItemHeight = 16;
			this->ListBoxCreatures->Location = System::Drawing::Point(6, 232);
			this->ListBoxCreatures->Name = L"ListBoxCreatures";
			this->ListBoxCreatures->Size = System::Drawing::Size(279, 308);
			this->ListBoxCreatures->TabIndex = 3;
			this->ListBoxCreatures->SelectedIndexChanged += gcnew System::EventHandler(this, &NeuroNetEditor::ListBoxCreatures_SelectedIndexChanged);
			// 
			// BtnNewModel
			// 
			this->BtnNewModel->Location = System::Drawing::Point(75, 550);
			this->BtnNewModel->Name = L"BtnNewModel";
			this->BtnNewModel->Size = System::Drawing::Size(132, 48);
			this->BtnNewModel->TabIndex = 2;
			this->BtnNewModel->Text = L"New Model";
			this->BtnNewModel->UseVisualStyleBackColor = true;
			this->BtnNewModel->Click += gcnew System::EventHandler(this, &NeuroNetEditor::BtnNewModel_Click);
			// 
			// PBoxCreatureModel
			// 
			this->PBoxCreatureModel->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->PBoxCreatureModel->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->PBoxCreatureModel->Location = System::Drawing::Point(6, 21);
			this->PBoxCreatureModel->Name = L"PBoxCreatureModel";
			this->PBoxCreatureModel->Size = System::Drawing::Size(279, 201);
			this->PBoxCreatureModel->TabIndex = 0;
			this->PBoxCreatureModel->TabStop = false;
			// 
			// GrBoxLearnAlgParam
			// 
			this->GrBoxLearnAlgParam->Controls->Add(this->NumUpDownQLearnRate);
			this->GrBoxLearnAlgParam->Controls->Add(this->NumUpDownRMSAccuracy);
			this->GrBoxLearnAlgParam->Controls->Add(this->NumUpDownRMSLearnRate);
			this->GrBoxLearnAlgParam->Controls->Add(this->NumUpDownRMSGamma);
			this->GrBoxLearnAlgParam->Controls->Add(this->ComBoxTrType);
			this->GrBoxLearnAlgParam->Controls->Add(this->LLearnRate);
			this->GrBoxLearnAlgParam->Controls->Add(this->LRMSAccuracy);
			this->GrBoxLearnAlgParam->Controls->Add(this->LRMSLearnRate);
			this->GrBoxLearnAlgParam->Controls->Add(this->LRMSGamma);
			this->GrBoxLearnAlgParam->Controls->Add(this->LRMSType);
			this->GrBoxLearnAlgParam->Location = System::Drawing::Point(311, 411);
			this->GrBoxLearnAlgParam->Name = L"GrBoxLearnAlgParam";
			this->GrBoxLearnAlgParam->Size = System::Drawing::Size(390, 191);
			this->GrBoxLearnAlgParam->TabIndex = 4;
			this->GrBoxLearnAlgParam->TabStop = false;
			this->GrBoxLearnAlgParam->Text = L"Learning Algorithm Parameters";
			// 
			// NumUpDownQLearnRate
			// 
			this->NumUpDownQLearnRate->DecimalPlaces = 3;
			this->NumUpDownQLearnRate->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 196608 });
			this->NumUpDownQLearnRate->Location = System::Drawing::Point(162, 155);
			this->NumUpDownQLearnRate->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->NumUpDownQLearnRate->Name = L"NumUpDownQLearnRate";
			this->NumUpDownQLearnRate->Size = System::Drawing::Size(214, 22);
			this->NumUpDownQLearnRate->TabIndex = 28;
			// 
			// NumUpDownRMSAccuracy
			// 
			this->NumUpDownRMSAccuracy->DecimalPlaces = 10;
			this->NumUpDownRMSAccuracy->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 655360 });
			this->NumUpDownRMSAccuracy->Location = System::Drawing::Point(162, 115);
			this->NumUpDownRMSAccuracy->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
			this->NumUpDownRMSAccuracy->Name = L"NumUpDownRMSAccuracy";
			this->NumUpDownRMSAccuracy->Size = System::Drawing::Size(214, 22);
			this->NumUpDownRMSAccuracy->TabIndex = 27;
			// 
			// NumUpDownRMSLearnRate
			// 
			this->NumUpDownRMSLearnRate->DecimalPlaces = 3;
			this->NumUpDownRMSLearnRate->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 196608 });
			this->NumUpDownRMSLearnRate->Location = System::Drawing::Point(162, 87);
			this->NumUpDownRMSLearnRate->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->NumUpDownRMSLearnRate->Name = L"NumUpDownRMSLearnRate";
			this->NumUpDownRMSLearnRate->Size = System::Drawing::Size(214, 22);
			this->NumUpDownRMSLearnRate->TabIndex = 26;
			// 
			// NumUpDownRMSGamma
			// 
			this->NumUpDownRMSGamma->DecimalPlaces = 3;
			this->NumUpDownRMSGamma->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 196608 });
			this->NumUpDownRMSGamma->Location = System::Drawing::Point(162, 59);
			this->NumUpDownRMSGamma->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->NumUpDownRMSGamma->Name = L"NumUpDownRMSGamma";
			this->NumUpDownRMSGamma->Size = System::Drawing::Size(214, 22);
			this->NumUpDownRMSGamma->TabIndex = 25;
			// 
			// ComBoxTrType
			// 
			this->ComBoxTrType->FormattingEnabled = true;
			this->ComBoxTrType->Items->AddRange(gcnew cli::array< System::Object^  >(1) { L"RMS" });
			this->ComBoxTrType->Location = System::Drawing::Point(162, 27);
			this->ComBoxTrType->Name = L"ComBoxTrType";
			this->ComBoxTrType->Size = System::Drawing::Size(214, 24);
			this->ComBoxTrType->TabIndex = 24;
			// 
			// LLearnRate
			// 
			this->LLearnRate->AutoSize = true;
			this->LLearnRate->Location = System::Drawing::Point(6, 157);
			this->LLearnRate->Name = L"LLearnRate";
			this->LLearnRate->Size = System::Drawing::Size(113, 17);
			this->LLearnRate->TabIndex = 18;
			this->LLearnRate->Text = L"Q-Learning rate:";
			// 
			// LRMSAccuracy
			// 
			this->LRMSAccuracy->AutoSize = true;
			this->LRMSAccuracy->Location = System::Drawing::Point(6, 117);
			this->LRMSAccuracy->Name = L"LRMSAccuracy";
			this->LRMSAccuracy->Size = System::Drawing::Size(104, 17);
			this->LRMSAccuracy->TabIndex = 17;
			this->LRMSAccuracy->Text = L"RMS Accuracy:";
			// 
			// LRMSLearnRate
			// 
			this->LRMSLearnRate->AutoSize = true;
			this->LRMSLearnRate->Location = System::Drawing::Point(6, 89);
			this->LRMSLearnRate->Name = L"LRMSLearnRate";
			this->LRMSLearnRate->Size = System::Drawing::Size(131, 17);
			this->LRMSLearnRate->TabIndex = 16;
			this->LRMSLearnRate->Text = L"RMS Learning rate:";
			// 
			// LRMSGamma
			// 
			this->LRMSGamma->AutoSize = true;
			this->LRMSGamma->Location = System::Drawing::Point(6, 61);
			this->LRMSGamma->Name = L"LRMSGamma";
			this->LRMSGamma->Size = System::Drawing::Size(95, 17);
			this->LRMSGamma->TabIndex = 15;
			this->LRMSGamma->Text = L"RMS Gamma:";
			// 
			// LRMSType
			// 
			this->LRMSType->AutoSize = true;
			this->LRMSType->Location = System::Drawing::Point(6, 33);
			this->LRMSType->Name = L"LRMSType";
			this->LRMSType->Size = System::Drawing::Size(95, 17);
			this->LRMSType->TabIndex = 14;
			this->LRMSType->Text = L"Training type:";
			// 
			// BtnSaveNNetParam
			// 
			this->BtnSaveNNetParam->Location = System::Drawing::Point(363, 629);
			this->BtnSaveNNetParam->Name = L"BtnSaveNNetParam";
			this->BtnSaveNNetParam->Size = System::Drawing::Size(132, 48);
			this->BtnSaveNNetParam->TabIndex = 5;
			this->BtnSaveNNetParam->Text = L"Save";
			this->BtnSaveNNetParam->UseVisualStyleBackColor = true;
			this->BtnSaveNNetParam->Click += gcnew System::EventHandler(this, &NeuroNetEditor::BtnSaveNNetParam_Click);
			// 
			// BtnCancel
			// 
			this->BtnCancel->Location = System::Drawing::Point(537, 629);
			this->BtnCancel->Name = L"BtnCancel";
			this->BtnCancel->Size = System::Drawing::Size(132, 48);
			this->BtnCancel->TabIndex = 6;
			this->BtnCancel->Text = L"Cancel";
			this->BtnCancel->UseVisualStyleBackColor = true;
			this->BtnCancel->Click += gcnew System::EventHandler(this, &NeuroNetEditor::BtnCancel_Click);
			// 
			// NeuroNetEditor
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(713, 689);
			this->Controls->Add(this->BtnCancel);
			this->Controls->Add(this->BtnSaveNNetParam);
			this->Controls->Add(this->GrBoxLearnAlgParam);
			this->Controls->Add(this->GrBoxCreatureModel);
			this->Controls->Add(this->GrBoxNNetParam);
			this->Controls->Add(this->TBoxNNetName);
			this->Controls->Add(this->LNNetName);
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(731, 736);
			this->MinimumSize = System::Drawing::Size(731, 736);
			this->Name = L"NeuroNetEditor";
			this->Text = L"NeuroNet Editor";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &NeuroNetEditor::NeuroNetEditor_FormClosing);
			this->Load += gcnew System::EventHandler(this, &NeuroNetEditor::NeuroNetEditor_Load);
			this->GrBoxNNetParam->ResumeLayout(false);
			this->GrBoxNNetParam->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->NumUpDownTrAccuracy))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->NumUpDownTrPeriod))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->NumUpDownEpoch))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->NumUpDownEpochTestsNum))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->NumUpDownTotalNumTests))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->NumUpDownHLNeurons))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->NumUpDownHidLayers))->EndInit();
			this->GrBoxCreatureModel->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PBoxCreatureModel))->EndInit();
			this->GrBoxLearnAlgParam->ResumeLayout(false);
			this->GrBoxLearnAlgParam->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->NumUpDownQLearnRate))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->NumUpDownRMSAccuracy))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->NumUpDownRMSLearnRate))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->NumUpDownRMSGamma))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void NeuroNetEditor_Load(System::Object^  sender, System::EventArgs^  e) {
		for (int i = 0; i < creatures.size(); ++i) {
			String^ s = gcnew String(creatures[i].name.c_str());
			ListBoxCreatures->Items->Add(s);
			delete s;
		}

		if (edit_nnet_pos != -1) {
			String^ snnetname = gcnew String(nnets[edit_nnet_pos].name.c_str());
			TBoxNNetName->Text = snnetname;
			delete snnetname;
			TBoxNNetName->ReadOnly = true;

			//картинка

			for (int i = 0; i < ListBoxCreatures->Items->Count; ++i) {
				std::string s = msclr::interop::marshal_as<std::string>(ListBoxCreatures->Items[i]->ToString());
				if (s == nnets[edit_nnet_pos].creature_name) {
					ListBoxCreatures->SelectedIndex = i;
					break;
				}
			}

			TBoxInputsEdit->Text = Convert::ToString(nnets[edit_nnet_pos].inputs_num);
			NumUpDownHidLayers->Text = Convert::ToString(nnets[edit_nnet_pos].hidden_layers_num);
			NumUpDownHLNeurons->Text = Convert::ToString(nnets[edit_nnet_pos].hidden_layer_neurons);
			TBoxOutputsEdit->Text = Convert::ToString(nnets[edit_nnet_pos].outputs_num);
			ComBoxActFunc->SelectedIndex = nnets[edit_nnet_pos].act_func;
			NumUpDownTotalNumTests->Text = Convert::ToString(nnets[edit_nnet_pos].tests_total_num);
			NumUpDownEpochTestsNum->Text = Convert::ToString(nnets[edit_nnet_pos].epoch_tests_num);
			NumUpDownEpoch->Text = Convert::ToString(nnets[edit_nnet_pos].epoch_num);
			NumUpDownTrPeriod->Text = Convert::ToString(nnets[edit_nnet_pos].training_period);
			NumUpDownTrAccuracy->Text = Convert::ToString(nnets[edit_nnet_pos].training_accuracy);
			ComBoxTrType->SelectedIndex = nnets[edit_nnet_pos].training_type;
			NumUpDownRMSGamma->Text = Convert::ToString(nnets[edit_nnet_pos].rms_gamma);
			NumUpDownRMSLearnRate->Text = Convert::ToString(nnets[edit_nnet_pos].rms_learning_rate);
			std::ostringstream strs;
			strs << std::fixed << std::setprecision(10) << nnets[edit_nnet_pos].rms_accuracy;
			std::string str = strs.str();
			for (int i = 0; i < str.size(); ++i) {
				if (str[i] == '.') str[i] = ',';
			}
			String^ s = gcnew String(str.c_str());
			NumUpDownRMSAccuracy->Text = s;
			delete s;
			NumUpDownQLearnRate->Text = Convert::ToString(nnets[edit_nnet_pos].qlearn_rate);
		}
	}

	private: System::Void BtnCancel_Click(System::Object^  sender, System::EventArgs^  e) {
		this->Close();
	}

	private: System::Void ListBoxCreatures_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		if (ListBoxCreatures->SelectedIndex != -1) {
			std::string crname = msclr::interop::marshal_as<std::string>(ListBoxCreatures->SelectedItem->ToString());
			int crpos = creatures_names[crname];

			std::string imgname = creatures_dir_str + crname + img_finame_end;
			String^ simgfile = gcnew String(imgname.c_str());
			PBoxCreatureModel->BackgroundImage = Image::FromFile(simgfile);
			PBoxCreatureModel->BackgroundImageLayout = ImageLayout::Zoom;
			delete simgfile;

			TBoxInputsEdit->Text = Convert::ToString(creatures[crpos].joints.size() * 2);
			TBoxOutputsEdit->Text = Convert::ToString(creatures[crpos].movable_lines.size() * 2);;
		}
		else {
			Image^ tmping = PBoxCreatureModel->BackgroundImage;
			PBoxCreatureModel->BackgroundImage = nullptr;
			delete tmping;

			TBoxInputsEdit->Text = L"";
			TBoxOutputsEdit->Text = L"";
		}
	}

	private: System::Void BtnSaveNNetParam_Click(System::Object^  sender, System::EventArgs^  e) {
		NNet new_nnet;

		std::string nnetname = msclr::interop::marshal_as<std::string>(TBoxNNetName->Text);
		if (nnetname == "") {
			MessageBox::Show("Enter name of neural network");
			return;
		}
		else {
			if (edit_nnet_pos == -1) { // если добавляем новую сеть
				for (int i = 0; i < nnetname.length(); ++i) {
					if (nnetname[i] == ' ')
						nnetname[i] = '_';
				}

				if (nnets_names.count(nnetname) == 0) {
					new_nnet.name = nnetname;
				}
				else {
					int nnpos = nnets_names[nnetname];
					if (nnets[nnpos].deleted) {
						new_nnet.name = nnetname;
					}
					else {
						MessageBox::Show("Network name already exists");
						return;
					}
				}
			}
			else { // если редактируем есть
				new_nnet.name = nnetname;
			}
		}

		if (ListBoxCreatures->SelectedIndex == -1) {
			MessageBox::Show("Choose creature model");
			return;
		}
		else {
			std::string crname = msclr::interop::marshal_as<std::string>(ListBoxCreatures->SelectedItem->ToString());
			new_nnet.creature_name = crname;
		}

		new_nnet.inputs_num = Convert::ToInt32(TBoxInputsEdit->Text);
		new_nnet.outputs_num = Convert::ToInt32(TBoxOutputsEdit->Text);

		if (NumUpDownHidLayers->Text != L"") {
			new_nnet.hidden_layers_num = Convert::ToInt32(NumUpDownHidLayers->Text);
		}
		else {
			MessageBox::Show("Enter number of hidden layers");
			return;
		}
		if (NumUpDownHLNeurons->Text != L"") {
			new_nnet.hidden_layer_neurons = Convert::ToInt32(NumUpDownHLNeurons->Text);
		}
		else {
			MessageBox::Show("Enter number of hidden layer neurons");
			return;
		}
		if (NumUpDownTotalNumTests->Text != L"") {
			new_nnet.tests_total_num = Convert::ToInt32(NumUpDownTotalNumTests->Text);
		}
		else {
			MessageBox::Show("Enter total number of tests");
			return;
		}
		if (NumUpDownEpochTestsNum->Text != L"") {
			new_nnet.epoch_tests_num = Convert::ToInt32(NumUpDownEpochTestsNum->Text);
		}
		else {
			MessageBox::Show("Enter number of tests for epoch");
			return;
		}
		if (NumUpDownEpoch->Text != L"") {
			new_nnet.epoch_num = Convert::ToInt32(NumUpDownEpoch->Text);
		}
		else {
			MessageBox::Show("Enter number of epochs");
			return;
		}
		if (NumUpDownTrPeriod->Text != L"") {
			new_nnet.training_period = Convert::ToInt32(NumUpDownTrPeriod->Text);
		}
		else {
			MessageBox::Show("Enter training period");
			return;
		}

		if (NumUpDownTrAccuracy->Text != L"") {
			new_nnet.training_accuracy = Convert::ToDouble(NumUpDownTrAccuracy->Text);
		}
		else {
			MessageBox::Show("Enter training accuracy");
			return;
		}
		if (NumUpDownRMSGamma->Text != L"") {
			new_nnet.rms_gamma = Convert::ToDouble(NumUpDownRMSGamma->Text);
		}
		else {
			MessageBox::Show("Enter RMS Gamma");
			return;
		}
		if (NumUpDownRMSLearnRate->Text != L"") {
			new_nnet.rms_learning_rate = Convert::ToDouble(NumUpDownRMSLearnRate->Text);
		}
		else {
			MessageBox::Show("Enter RMS Lerning Rate");
			return;
		}
		if (NumUpDownRMSAccuracy->Text != L"") {
			new_nnet.rms_accuracy = Convert::ToDouble(NumUpDownRMSAccuracy->Text);
		}
		else {
			MessageBox::Show("Enter RMS Accuracy");
			return;
		}
		if (NumUpDownQLearnRate->Text != L"") {
			new_nnet.qlearn_rate = Convert::ToDouble(NumUpDownQLearnRate->Text);
		}
		else {
			MessageBox::Show("Enter RMS QLearning Rate");
			return;
		}

		if (ComBoxActFunc->SelectedIndex == -1) {
			MessageBox::Show("Choose activation function");
			return;
		}
		else {
			std::string actfunc = msclr::interop::marshal_as<std::string>(ComBoxActFunc->SelectedItem->ToString());
			if (actfunc == "LINE") new_nnet.act_func = LINE;
			if (actfunc == "TANH") new_nnet.act_func = TANH;
			if (actfunc == "SGMD") new_nnet.act_func = SGMD;
		}

		if (ComBoxTrType->SelectedIndex == -1) {
			MessageBox::Show("Choose training type");
			return;
		}
		else {
			std::string trtype = msclr::interop::marshal_as<std::string>(ComBoxTrType->SelectedItem->ToString());
			if (trtype == "RMS") new_nnet.training_type = RMS;
		}

		// Запись в файл
		std::string nnfilename = nnets_dir_str + new_nnet.name + nnet_finame_end;
		std::ofstream fout(nnfilename.c_str());

		if (fout.is_open()) {
			fout << "CREATURE_NAME = " << new_nnet.creature_name << ";" << std::endl;
			fout << "HIDDEN_LAYERS_NUM = " << new_nnet.hidden_layers_num << ";" << std::endl;
			fout << "HIDDEN_LAYER_NEURONS_NUM = " << new_nnet.hidden_layer_neurons << ";" << std::endl;
			switch (new_nnet.act_func)
			{
			case TANH: fout << "ACTIVATION_FUNC = TANH;" << std::endl; break;
			case SGMD: fout << "ACTIVATION_FUNC = SGMD;" << std::endl; break;
			case LINE: fout << "ACTIVATION_FUNC = LINE;" << std::endl; break;
			default:
				break;
			}

			fout << "TEST_TOTAL_NUMBER = " << new_nnet.tests_total_num << ";" << std::endl;
			fout << "EPOCH_TESTS_NUM = " << new_nnet.epoch_tests_num << ";" << std::endl;
			fout << "EPOCH_NUM = " << new_nnet.epoch_num << ";" << std::endl;

			switch (new_nnet.training_type)
			{
			case RMS: fout << "TRAINING_TYPE = RMS;" << std::endl << std::endl;
			default:
				break;
			}

			fout << "RMS_GAMMA = " << std::fixed << std::setprecision(6) << new_nnet.rms_gamma << ";" << std::endl;
			fout << "RMS_LEARN_RATE = " << std::fixed << std::setprecision(6) << new_nnet.rms_learning_rate << ";" << std::endl;
			fout << "RMS_ACCURACY = " << std::fixed << std::setprecision(10) << new_nnet.rms_accuracy << ";" << std::endl << std::endl;

			fout << "QLEARN_RATE = " << std::fixed << std::setprecision(6) << new_nnet.qlearn_rate << ";" << std::endl << std::endl;

			fout << "TRAINING_PERIOD = " << new_nnet.training_period << ";" << std::endl;
			fout << "TRAINING_ACCURACY = " << std::fixed << std::setprecision(10) << new_nnet.training_accuracy << ";" << std::endl;

			// Запись в вектор
			if (edit_nnet_pos == -1) {
				nnets.push_back(new_nnet);
				nnets_names[new_nnet.name] = nnets.size() - 1;
				nnets.back().can_continue_training_or_run = false;
			}
			else {
				nnets[edit_nnet_pos] = new_nnet;
				nnets[edit_nnet_pos].can_continue_training_or_run = false;
			}

			std::string messtr = "Data is saved to a file \"" + nnfilename + "\"";
			String^ mes = gcnew String(messtr.c_str());
			MessageBox::Show(mes);
			delete mes;
		}
		else {
			MessageBox::Show("Сreating file error!");
		}

	}

	private: System::Void NeuroNetEditor_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
		if (MessageBox::Show(this, "Do you want to save data?", "Form Closing", MessageBoxButtons::YesNo) == System::Windows::Forms::DialogResult::Yes)
		{
			e->Cancel = true;
		}
		else {
			edit_nnet_pos = -1;
		}
	}
			 
	private: System::Void BtnNewModel_Click(System::Object^  sender, System::EventArgs^  e) {
		Creator^ creator_form = gcnew Creator();
		creator_form->ShowDialog();

		ListBoxCreatures->SelectedIndex = -1;
		ListBoxCreatures->Items->Clear();
		for (int i = 0; i < creatures.size(); ++i) {
			String^ s = gcnew String(creatures[i].name.c_str());
			ListBoxCreatures->Items->Add(s);
			delete s;
		}

		delete creator_form;
	}
};
}
