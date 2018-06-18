#pragma once
#define _USE_MATH_DEFINES
#include <vector>
#include <set>
#include <algorithm>
#include <functional>
#include <string>
#include <fstream>
#include <iostream>
#include <msclr\marshal_cppstd.h>
#include "Common.h"

#define CREATURENAME "creature"

namespace NeuroNetDesigner {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Creator
	/// </summary>
	public ref class Creator : public System::Windows::Forms::Form
	{
	public:
		Creator(void)
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
		~Creator()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TabPage^  TabChooseInitialStates;
	private: System::Windows::Forms::Button^  BtnNextInSt;
	protected:



	private: System::Windows::Forms::PictureBox^  CanvasInSt;
	private: System::Windows::Forms::TabPage^  TabChooseTurnIntervals;
	private: System::Windows::Forms::Button^  BtnNextTInt;


	private: System::Windows::Forms::PictureBox^  CanvasTInt;
	private: System::Windows::Forms::TabPage^  TabChooseMovableLines;
	private: System::Windows::Forms::Button^  BtnNextMvLn;


	private: System::Windows::Forms::PictureBox^  CanvasMvLn;
	private: System::Windows::Forms::TabPage^  TabMakeCreature;
	private: System::Windows::Forms::Button^  BtnMakeCreature;



	private: System::Windows::Forms::GroupBox^  Elemets;
	private: System::Windows::Forms::Button^  BtnClearCanvas;

	private: System::Windows::Forms::RadioButton^  Line;
	private: System::Windows::Forms::RadioButton^  Dot;
	private: System::Windows::Forms::PictureBox^  Canvas;
	private: System::Windows::Forms::TabControl^  CreationProcess;


	private: System::Windows::Forms::TabPage^  TabChooseConnections;
	private: System::Windows::Forms::Button^  BtnNextCon;




	private: System::Windows::Forms::PictureBox^  CanvasCon;
	private: System::Windows::Forms::GroupBox^  GrBoxMvLines;
	private: System::Windows::Forms::CheckedListBox^  CheckListBoxMvLines;
	private: System::Windows::Forms::GroupBox^  GrBoxTInt;
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::Label^  LbDegUAng;
	private: System::Windows::Forms::TextBox^  TBoxUnitAngle;


	private: System::Windows::Forms::Label^  LbUnitAngle;
	private: System::Windows::Forms::ComboBox^  ComBoxLineTInt;


	private: System::Windows::Forms::Label^  LbLine;
	private: System::Windows::Forms::Label^  LbDegMaxAng;

	private: System::Windows::Forms::Label^  LbDegMinAng;
	private: System::Windows::Forms::TextBox^  TBoxMaxAngle;
	private: System::Windows::Forms::TextBox^  TBoxMinAngle;
	private: System::Windows::Forms::Button^  BtnShowTInt;

	private: System::Windows::Forms::Label^  LbMaxAngle;

	private: System::Windows::Forms::Label^  LbMinAngle;
	private: System::Windows::Forms::RichTextBox^  richTextBox1;
	private: System::Windows::Forms::GroupBox^  GrBoxInSt;

	private: System::Windows::Forms::Button^  BtnSaveState;
	private: System::Windows::Forms::ComboBox^  ComBoxLineInSt;

	private: System::Windows::Forms::Label^  LbLine2;
	private: System::Windows::Forms::Label^  LbState;
	private: System::Windows::Forms::ComboBox^  ComBoxStateInSt;
	private: System::Windows::Forms::Label^  LbFallAngle;
	private: System::Windows::Forms::Label^  LbDegFAng;
	private: System::Windows::Forms::TextBox^  TBoxFallAngle;
	private: System::Windows::Forms::GroupBox^  GrBoxCon;

	private: System::Windows::Forms::ComboBox^  ComBoxLineCon;
	private: System::Windows::Forms::Label^  LbLine3;
	private: System::Windows::Forms::Button^  BtnSaveConnections;
	private: System::Windows::Forms::CheckedListBox^  CheckListBoxCon;
	private: System::Windows::Forms::TabPage^  TabSave;

	private: System::Windows::Forms::GroupBox^  GrBoxSave;

	private: System::Windows::Forms::Label^  LbFilename;
	private: System::Windows::Forms::Button^  BtnSaveToFile;


	private: System::Windows::Forms::Button^  BtnClose;
	private: System::Windows::Forms::PictureBox^  CanvasSave;
	private: System::Windows::Forms::TextBox^  TBoxCreatureName;


	private: System::Windows::Forms::ContextMenuStrip^  contextMenuStrip1;
	private: System::Windows::Forms::TrackBar^  TrackBarMaxAng;
	private: System::Windows::Forms::TrackBar^  TrackBarMinAng;
	private: System::ComponentModel::IContainer^  components;




	protected:

	protected:

	protected:

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->TabChooseInitialStates = (gcnew System::Windows::Forms::TabPage());
			this->GrBoxInSt = (gcnew System::Windows::Forms::GroupBox());
			this->LbState = (gcnew System::Windows::Forms::Label());
			this->ComBoxStateInSt = (gcnew System::Windows::Forms::ComboBox());
			this->ComBoxLineInSt = (gcnew System::Windows::Forms::ComboBox());
			this->LbLine2 = (gcnew System::Windows::Forms::Label());
			this->BtnSaveState = (gcnew System::Windows::Forms::Button());
			this->BtnNextInSt = (gcnew System::Windows::Forms::Button());
			this->CanvasInSt = (gcnew System::Windows::Forms::PictureBox());
			this->TabChooseTurnIntervals = (gcnew System::Windows::Forms::TabPage());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->GrBoxTInt = (gcnew System::Windows::Forms::GroupBox());
			this->LbFallAngle = (gcnew System::Windows::Forms::Label());
			this->LbDegFAng = (gcnew System::Windows::Forms::Label());
			this->TBoxFallAngle = (gcnew System::Windows::Forms::TextBox());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->TrackBarMaxAng = (gcnew System::Windows::Forms::TrackBar());
			this->TrackBarMinAng = (gcnew System::Windows::Forms::TrackBar());
			this->LbDegMaxAng = (gcnew System::Windows::Forms::Label());
			this->LbDegMinAng = (gcnew System::Windows::Forms::Label());
			this->TBoxMaxAngle = (gcnew System::Windows::Forms::TextBox());
			this->TBoxMinAngle = (gcnew System::Windows::Forms::TextBox());
			this->BtnShowTInt = (gcnew System::Windows::Forms::Button());
			this->LbMaxAngle = (gcnew System::Windows::Forms::Label());
			this->LbMinAngle = (gcnew System::Windows::Forms::Label());
			this->ComBoxLineTInt = (gcnew System::Windows::Forms::ComboBox());
			this->LbLine = (gcnew System::Windows::Forms::Label());
			this->LbDegUAng = (gcnew System::Windows::Forms::Label());
			this->TBoxUnitAngle = (gcnew System::Windows::Forms::TextBox());
			this->LbUnitAngle = (gcnew System::Windows::Forms::Label());
			this->BtnNextTInt = (gcnew System::Windows::Forms::Button());
			this->CanvasTInt = (gcnew System::Windows::Forms::PictureBox());
			this->TabChooseMovableLines = (gcnew System::Windows::Forms::TabPage());
			this->GrBoxMvLines = (gcnew System::Windows::Forms::GroupBox());
			this->CheckListBoxMvLines = (gcnew System::Windows::Forms::CheckedListBox());
			this->BtnNextMvLn = (gcnew System::Windows::Forms::Button());
			this->CanvasMvLn = (gcnew System::Windows::Forms::PictureBox());
			this->TabMakeCreature = (gcnew System::Windows::Forms::TabPage());
			this->BtnMakeCreature = (gcnew System::Windows::Forms::Button());
			this->Elemets = (gcnew System::Windows::Forms::GroupBox());
			this->BtnClearCanvas = (gcnew System::Windows::Forms::Button());
			this->Line = (gcnew System::Windows::Forms::RadioButton());
			this->Dot = (gcnew System::Windows::Forms::RadioButton());
			this->Canvas = (gcnew System::Windows::Forms::PictureBox());
			this->CreationProcess = (gcnew System::Windows::Forms::TabControl());
			this->TabChooseConnections = (gcnew System::Windows::Forms::TabPage());
			this->GrBoxCon = (gcnew System::Windows::Forms::GroupBox());
			this->CheckListBoxCon = (gcnew System::Windows::Forms::CheckedListBox());
			this->ComBoxLineCon = (gcnew System::Windows::Forms::ComboBox());
			this->LbLine3 = (gcnew System::Windows::Forms::Label());
			this->BtnSaveConnections = (gcnew System::Windows::Forms::Button());
			this->BtnNextCon = (gcnew System::Windows::Forms::Button());
			this->CanvasCon = (gcnew System::Windows::Forms::PictureBox());
			this->TabSave = (gcnew System::Windows::Forms::TabPage());
			this->GrBoxSave = (gcnew System::Windows::Forms::GroupBox());
			this->TBoxCreatureName = (gcnew System::Windows::Forms::TextBox());
			this->LbFilename = (gcnew System::Windows::Forms::Label());
			this->BtnSaveToFile = (gcnew System::Windows::Forms::Button());
			this->BtnClose = (gcnew System::Windows::Forms::Button());
			this->CanvasSave = (gcnew System::Windows::Forms::PictureBox());
			this->contextMenuStrip1 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->TabChooseInitialStates->SuspendLayout();
			this->GrBoxInSt->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->CanvasInSt))->BeginInit();
			this->TabChooseTurnIntervals->SuspendLayout();
			this->GrBoxTInt->SuspendLayout();
			this->panel1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TrackBarMaxAng))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TrackBarMinAng))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->CanvasTInt))->BeginInit();
			this->TabChooseMovableLines->SuspendLayout();
			this->GrBoxMvLines->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->CanvasMvLn))->BeginInit();
			this->TabMakeCreature->SuspendLayout();
			this->Elemets->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Canvas))->BeginInit();
			this->CreationProcess->SuspendLayout();
			this->TabChooseConnections->SuspendLayout();
			this->GrBoxCon->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->CanvasCon))->BeginInit();
			this->TabSave->SuspendLayout();
			this->GrBoxSave->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->CanvasSave))->BeginInit();
			this->SuspendLayout();
			// 
			// TabChooseInitialStates
			// 
			this->TabChooseInitialStates->BackColor = System::Drawing::Color::WhiteSmoke;
			this->TabChooseInitialStates->Controls->Add(this->GrBoxInSt);
			this->TabChooseInitialStates->Controls->Add(this->BtnNextInSt);
			this->TabChooseInitialStates->Controls->Add(this->CanvasInSt);
			this->TabChooseInitialStates->Location = System::Drawing::Point(4, 27);
			this->TabChooseInitialStates->Name = L"TabChooseInitialStates";
			this->TabChooseInitialStates->Padding = System::Windows::Forms::Padding(3);
			this->TabChooseInitialStates->Size = System::Drawing::Size(899, 574);
			this->TabChooseInitialStates->TabIndex = 4;
			this->TabChooseInitialStates->Text = L"Choose Initial States";
			// 
			// GrBoxInSt
			// 
			this->GrBoxInSt->Controls->Add(this->LbState);
			this->GrBoxInSt->Controls->Add(this->ComBoxStateInSt);
			this->GrBoxInSt->Controls->Add(this->ComBoxLineInSt);
			this->GrBoxInSt->Controls->Add(this->LbLine2);
			this->GrBoxInSt->Controls->Add(this->BtnSaveState);
			this->GrBoxInSt->Location = System::Drawing::Point(608, 9);
			this->GrBoxInSt->Name = L"GrBoxInSt";
			this->GrBoxInSt->Size = System::Drawing::Size(285, 306);
			this->GrBoxInSt->TabIndex = 5;
			this->GrBoxInSt->TabStop = false;
			this->GrBoxInSt->Text = L"Enter Initial States";
			// 
			// LbState
			// 
			this->LbState->AutoSize = true;
			this->LbState->Location = System::Drawing::Point(10, 145);
			this->LbState->Name = L"LbState";
			this->LbState->Size = System::Drawing::Size(46, 18);
			this->LbState->TabIndex = 6;
			this->LbState->Text = L"State:";
			// 
			// ComBoxStateInSt
			// 
			this->ComBoxStateInSt->BackColor = System::Drawing::SystemColors::Window;
			this->ComBoxStateInSt->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->ComBoxStateInSt->FormattingEnabled = true;
			this->ComBoxStateInSt->Location = System::Drawing::Point(73, 145);
			this->ComBoxStateInSt->Name = L"ComBoxStateInSt";
			this->ComBoxStateInSt->Size = System::Drawing::Size(190, 26);
			this->ComBoxStateInSt->TabIndex = 5;
			// 
			// ComBoxLineInSt
			// 
			this->ComBoxLineInSt->BackColor = System::Drawing::SystemColors::Window;
			this->ComBoxLineInSt->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->ComBoxLineInSt->FormattingEnabled = true;
			this->ComBoxLineInSt->Location = System::Drawing::Point(73, 86);
			this->ComBoxLineInSt->Name = L"ComBoxLineInSt";
			this->ComBoxLineInSt->Size = System::Drawing::Size(190, 26);
			this->ComBoxLineInSt->TabIndex = 1;
			this->ComBoxLineInSt->SelectedIndexChanged += gcnew System::EventHandler(this, &Creator::ComBoxLineInSt_SelectedIndexChanged);
			// 
			// LbLine2
			// 
			this->LbLine2->AutoSize = true;
			this->LbLine2->Location = System::Drawing::Point(10, 86);
			this->LbLine2->Name = L"LbLine2";
			this->LbLine2->Size = System::Drawing::Size(39, 18);
			this->LbLine2->TabIndex = 0;
			this->LbLine2->Text = L"Line:";
			// 
			// BtnSaveState
			// 
			this->BtnSaveState->Location = System::Drawing::Point(33, 238);
			this->BtnSaveState->Name = L"BtnSaveState";
			this->BtnSaveState->Size = System::Drawing::Size(224, 40);
			this->BtnSaveState->TabIndex = 4;
			this->BtnSaveState->Text = L"Save state";
			this->BtnSaveState->UseVisualStyleBackColor = true;
			this->BtnSaveState->Click += gcnew System::EventHandler(this, &Creator::BtnSaveState_Click);
			// 
			// BtnNextInSt
			// 
			this->BtnNextInSt->Location = System::Drawing::Point(693, 520);
			this->BtnNextInSt->Name = L"BtnNextInSt";
			this->BtnNextInSt->Size = System::Drawing::Size(148, 46);
			this->BtnNextInSt->TabIndex = 3;
			this->BtnNextInSt->Text = L"Next";
			this->BtnNextInSt->UseVisualStyleBackColor = true;
			this->BtnNextInSt->Click += gcnew System::EventHandler(this, &Creator::BtnNextInSt_Click);
			// 
			// CanvasInSt
			// 
			this->CanvasInSt->BackColor = System::Drawing::Color::White;
			this->CanvasInSt->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->CanvasInSt->Location = System::Drawing::Point(8, 9);
			this->CanvasInSt->Name = L"CanvasInSt";
			this->CanvasInSt->Size = System::Drawing::Size(589, 562);
			this->CanvasInSt->TabIndex = 2;
			this->CanvasInSt->TabStop = false;
			// 
			// TabChooseTurnIntervals
			// 
			this->TabChooseTurnIntervals->BackColor = System::Drawing::Color::WhiteSmoke;
			this->TabChooseTurnIntervals->Controls->Add(this->richTextBox1);
			this->TabChooseTurnIntervals->Controls->Add(this->GrBoxTInt);
			this->TabChooseTurnIntervals->Controls->Add(this->BtnNextTInt);
			this->TabChooseTurnIntervals->Controls->Add(this->CanvasTInt);
			this->TabChooseTurnIntervals->Location = System::Drawing::Point(4, 27);
			this->TabChooseTurnIntervals->Name = L"TabChooseTurnIntervals";
			this->TabChooseTurnIntervals->Padding = System::Windows::Forms::Padding(3);
			this->TabChooseTurnIntervals->Size = System::Drawing::Size(899, 574);
			this->TabChooseTurnIntervals->TabIndex = 2;
			this->TabChooseTurnIntervals->Text = L"Choose Turn Intervals";
			// 
			// richTextBox1
			// 
			this->richTextBox1->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->richTextBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->richTextBox1->Location = System::Drawing::Point(608, 447);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->ReadOnly = true;
			this->richTextBox1->Size = System::Drawing::Size(283, 60);
			this->richTextBox1->TabIndex = 5;
			this->richTextBox1->Text = L"Angle values ​​must be positive. \nThe angle is counted from zero \ncounterclockwis"
				L"e along the unit circle.";
			// 
			// GrBoxTInt
			// 
			this->GrBoxTInt->Controls->Add(this->LbFallAngle);
			this->GrBoxTInt->Controls->Add(this->LbDegFAng);
			this->GrBoxTInt->Controls->Add(this->TBoxFallAngle);
			this->GrBoxTInt->Controls->Add(this->panel1);
			this->GrBoxTInt->Controls->Add(this->LbDegUAng);
			this->GrBoxTInt->Controls->Add(this->TBoxUnitAngle);
			this->GrBoxTInt->Controls->Add(this->LbUnitAngle);
			this->GrBoxTInt->Location = System::Drawing::Point(608, 9);
			this->GrBoxTInt->Name = L"GrBoxTInt";
			this->GrBoxTInt->Size = System::Drawing::Size(285, 498);
			this->GrBoxTInt->TabIndex = 4;
			this->GrBoxTInt->TabStop = false;
			this->GrBoxTInt->Text = L"Enter Turn Intervals";
			// 
			// LbFallAngle
			// 
			this->LbFallAngle->AutoSize = true;
			this->LbFallAngle->Location = System::Drawing::Point(10, 90);
			this->LbFallAngle->Name = L"LbFallAngle";
			this->LbFallAngle->Size = System::Drawing::Size(78, 18);
			this->LbFallAngle->TabIndex = 6;
			this->LbFallAngle->Text = L"Fall angle: ";
			// 
			// LbDegFAng
			// 
			this->LbDegFAng->AutoSize = true;
			this->LbDegFAng->Location = System::Drawing::Point(243, 87);
			this->LbDegFAng->Name = L"LbDegFAng";
			this->LbDegFAng->Size = System::Drawing::Size(32, 18);
			this->LbDegFAng->TabIndex = 5;
			this->LbDegFAng->Text = L"deg";
			// 
			// TBoxFallAngle
			// 
			this->TBoxFallAngle->Location = System::Drawing::Point(103, 87);
			this->TBoxFallAngle->Name = L"TBoxFallAngle";
			this->TBoxFallAngle->Size = System::Drawing::Size(130, 24);
			this->TBoxFallAngle->TabIndex = 4;
			// 
			// panel1
			// 
			this->panel1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel1->Controls->Add(this->TrackBarMaxAng);
			this->panel1->Controls->Add(this->TrackBarMinAng);
			this->panel1->Controls->Add(this->LbDegMaxAng);
			this->panel1->Controls->Add(this->LbDegMinAng);
			this->panel1->Controls->Add(this->TBoxMaxAngle);
			this->panel1->Controls->Add(this->TBoxMinAngle);
			this->panel1->Controls->Add(this->BtnShowTInt);
			this->panel1->Controls->Add(this->LbMaxAngle);
			this->panel1->Controls->Add(this->LbMinAngle);
			this->panel1->Controls->Add(this->ComBoxLineTInt);
			this->panel1->Controls->Add(this->LbLine);
			this->panel1->Location = System::Drawing::Point(6, 117);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(273, 321);
			this->panel1->TabIndex = 3;
			// 
			// TrackBarMaxAng
			// 
			this->TrackBarMaxAng->Location = System::Drawing::Point(2, 199);
			this->TrackBarMaxAng->Maximum = 720;
			this->TrackBarMaxAng->Name = L"TrackBarMaxAng";
			this->TrackBarMaxAng->Size = System::Drawing::Size(264, 56);
			this->TrackBarMaxAng->TabIndex = 10;
			this->TrackBarMaxAng->ValueChanged += gcnew System::EventHandler(this, &Creator::TrackBarMaxAng_ValueChanged);
			// 
			// TrackBarMinAng
			// 
			this->TrackBarMinAng->Location = System::Drawing::Point(4, 103);
			this->TrackBarMinAng->Maximum = 720;
			this->TrackBarMinAng->Name = L"TrackBarMinAng";
			this->TrackBarMinAng->Size = System::Drawing::Size(264, 56);
			this->TrackBarMinAng->TabIndex = 9;
			this->TrackBarMinAng->ValueChanged += gcnew System::EventHandler(this, &Creator::TrackBarMinAng_ValueChanged);
			// 
			// LbDegMaxAng
			// 
			this->LbDegMaxAng->AutoSize = true;
			this->LbDegMaxAng->Location = System::Drawing::Point(235, 172);
			this->LbDegMaxAng->Name = L"LbDegMaxAng";
			this->LbDegMaxAng->Size = System::Drawing::Size(32, 18);
			this->LbDegMaxAng->TabIndex = 8;
			this->LbDegMaxAng->Text = L"deg";
			// 
			// LbDegMinAng
			// 
			this->LbDegMinAng->AutoSize = true;
			this->LbDegMinAng->Location = System::Drawing::Point(235, 76);
			this->LbDegMinAng->Name = L"LbDegMinAng";
			this->LbDegMinAng->Size = System::Drawing::Size(32, 18);
			this->LbDegMinAng->TabIndex = 7;
			this->LbDegMinAng->Text = L"deg";
			// 
			// TBoxMaxAngle
			// 
			this->TBoxMaxAngle->Location = System::Drawing::Point(85, 169);
			this->TBoxMaxAngle->Name = L"TBoxMaxAngle";
			this->TBoxMaxAngle->Size = System::Drawing::Size(129, 24);
			this->TBoxMaxAngle->TabIndex = 6;
			this->TBoxMaxAngle->TextChanged += gcnew System::EventHandler(this, &Creator::TBoxMaxAngle_TextChanged);
			// 
			// TBoxMinAngle
			// 
			this->TBoxMinAngle->Location = System::Drawing::Point(85, 73);
			this->TBoxMinAngle->Name = L"TBoxMinAngle";
			this->TBoxMinAngle->Size = System::Drawing::Size(129, 24);
			this->TBoxMinAngle->TabIndex = 5;
			this->TBoxMinAngle->TextChanged += gcnew System::EventHandler(this, &Creator::TBoxMinAngle_TextChanged);
			// 
			// BtnShowTInt
			// 
			this->BtnShowTInt->Location = System::Drawing::Point(32, 274);
			this->BtnShowTInt->Name = L"BtnShowTInt";
			this->BtnShowTInt->Size = System::Drawing::Size(224, 40);
			this->BtnShowTInt->TabIndex = 4;
			this->BtnShowTInt->Text = L"Save and Show";
			this->BtnShowTInt->UseVisualStyleBackColor = true;
			this->BtnShowTInt->Click += gcnew System::EventHandler(this, &Creator::BtnShowTInt_Click);
			// 
			// LbMaxAngle
			// 
			this->LbMaxAngle->AutoSize = true;
			this->LbMaxAngle->Location = System::Drawing::Point(0, 172);
			this->LbMaxAngle->Name = L"LbMaxAngle";
			this->LbMaxAngle->Size = System::Drawing::Size(79, 18);
			this->LbMaxAngle->TabIndex = 3;
			this->LbMaxAngle->Text = L"Max angle:";
			// 
			// LbMinAngle
			// 
			this->LbMinAngle->AutoSize = true;
			this->LbMinAngle->Location = System::Drawing::Point(0, 76);
			this->LbMinAngle->Name = L"LbMinAngle";
			this->LbMinAngle->Size = System::Drawing::Size(75, 18);
			this->LbMinAngle->TabIndex = 2;
			this->LbMinAngle->Text = L"Min angle:";
			// 
			// ComBoxLineTInt
			// 
			this->ComBoxLineTInt->BackColor = System::Drawing::SystemColors::Window;
			this->ComBoxLineTInt->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->ComBoxLineTInt->FormattingEnabled = true;
			this->ComBoxLineTInt->Location = System::Drawing::Point(48, 28);
			this->ComBoxLineTInt->Name = L"ComBoxLineTInt";
			this->ComBoxLineTInt->Size = System::Drawing::Size(208, 26);
			this->ComBoxLineTInt->TabIndex = 1;
			this->ComBoxLineTInt->SelectedIndexChanged += gcnew System::EventHandler(this, &Creator::ComBoxLineTInt_SelectedIndexChanged);
			// 
			// LbLine
			// 
			this->LbLine->AutoSize = true;
			this->LbLine->Location = System::Drawing::Point(3, 31);
			this->LbLine->Name = L"LbLine";
			this->LbLine->Size = System::Drawing::Size(39, 18);
			this->LbLine->TabIndex = 0;
			this->LbLine->Text = L"Line:";
			// 
			// LbDegUAng
			// 
			this->LbDegUAng->AutoSize = true;
			this->LbDegUAng->Location = System::Drawing::Point(243, 51);
			this->LbDegUAng->Name = L"LbDegUAng";
			this->LbDegUAng->Size = System::Drawing::Size(32, 18);
			this->LbDegUAng->TabIndex = 2;
			this->LbDegUAng->Text = L"deg";
			// 
			// TBoxUnitAngle
			// 
			this->TBoxUnitAngle->Location = System::Drawing::Point(103, 48);
			this->TBoxUnitAngle->Name = L"TBoxUnitAngle";
			this->TBoxUnitAngle->Size = System::Drawing::Size(130, 24);
			this->TBoxUnitAngle->TabIndex = 1;
			// 
			// LbUnitAngle
			// 
			this->LbUnitAngle->AutoSize = true;
			this->LbUnitAngle->Location = System::Drawing::Point(6, 51);
			this->LbUnitAngle->Name = L"LbUnitAngle";
			this->LbUnitAngle->Size = System::Drawing::Size(81, 18);
			this->LbUnitAngle->TabIndex = 0;
			this->LbUnitAngle->Text = L"Unit angle: ";
			// 
			// BtnNextTInt
			// 
			this->BtnNextTInt->Location = System::Drawing::Point(693, 520);
			this->BtnNextTInt->Name = L"BtnNextTInt";
			this->BtnNextTInt->Size = System::Drawing::Size(148, 46);
			this->BtnNextTInt->TabIndex = 3;
			this->BtnNextTInt->Text = L"Next";
			this->BtnNextTInt->UseVisualStyleBackColor = true;
			this->BtnNextTInt->Click += gcnew System::EventHandler(this, &Creator::BtnNextTInt_Click);
			// 
			// CanvasTInt
			// 
			this->CanvasTInt->BackColor = System::Drawing::Color::White;
			this->CanvasTInt->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->CanvasTInt->Location = System::Drawing::Point(9, 9);
			this->CanvasTInt->Name = L"CanvasTInt";
			this->CanvasTInt->Size = System::Drawing::Size(589, 562);
			this->CanvasTInt->TabIndex = 2;
			this->CanvasTInt->TabStop = false;
			// 
			// TabChooseMovableLines
			// 
			this->TabChooseMovableLines->BackColor = System::Drawing::Color::WhiteSmoke;
			this->TabChooseMovableLines->Controls->Add(this->GrBoxMvLines);
			this->TabChooseMovableLines->Controls->Add(this->BtnNextMvLn);
			this->TabChooseMovableLines->Controls->Add(this->CanvasMvLn);
			this->TabChooseMovableLines->ForeColor = System::Drawing::SystemColors::ControlText;
			this->TabChooseMovableLines->Location = System::Drawing::Point(4, 27);
			this->TabChooseMovableLines->Name = L"TabChooseMovableLines";
			this->TabChooseMovableLines->Padding = System::Windows::Forms::Padding(3);
			this->TabChooseMovableLines->Size = System::Drawing::Size(899, 574);
			this->TabChooseMovableLines->TabIndex = 1;
			this->TabChooseMovableLines->Text = L"Choose Movable Lines";
			// 
			// GrBoxMvLines
			// 
			this->GrBoxMvLines->Controls->Add(this->CheckListBoxMvLines);
			this->GrBoxMvLines->Location = System::Drawing::Point(604, 9);
			this->GrBoxMvLines->Name = L"GrBoxMvLines";
			this->GrBoxMvLines->Size = System::Drawing::Size(289, 494);
			this->GrBoxMvLines->TabIndex = 3;
			this->GrBoxMvLines->TabStop = false;
			this->GrBoxMvLines->Text = L"Choose movable lines";
			// 
			// CheckListBoxMvLines
			// 
			this->CheckListBoxMvLines->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->CheckListBoxMvLines->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->CheckListBoxMvLines->FormattingEnabled = true;
			this->CheckListBoxMvLines->Location = System::Drawing::Point(6, 29);
			this->CheckListBoxMvLines->Name = L"CheckListBoxMvLines";
			this->CheckListBoxMvLines->Size = System::Drawing::Size(277, 456);
			this->CheckListBoxMvLines->TabIndex = 0;
			this->CheckListBoxMvLines->SelectedIndexChanged += gcnew System::EventHandler(this, &Creator::CheckListBoxMvLines_SelectedIndexChanged);
			// 
			// BtnNextMvLn
			// 
			this->BtnNextMvLn->Location = System::Drawing::Point(693, 520);
			this->BtnNextMvLn->Name = L"BtnNextMvLn";
			this->BtnNextMvLn->Size = System::Drawing::Size(148, 46);
			this->BtnNextMvLn->TabIndex = 2;
			this->BtnNextMvLn->Text = L"Next";
			this->BtnNextMvLn->UseVisualStyleBackColor = true;
			this->BtnNextMvLn->Click += gcnew System::EventHandler(this, &Creator::BtnNextMvLn_Click);
			// 
			// CanvasMvLn
			// 
			this->CanvasMvLn->BackColor = System::Drawing::Color::White;
			this->CanvasMvLn->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->CanvasMvLn->Location = System::Drawing::Point(9, 9);
			this->CanvasMvLn->Name = L"CanvasMvLn";
			this->CanvasMvLn->Size = System::Drawing::Size(589, 562);
			this->CanvasMvLn->TabIndex = 1;
			this->CanvasMvLn->TabStop = false;
			// 
			// TabMakeCreature
			// 
			this->TabMakeCreature->BackColor = System::Drawing::Color::WhiteSmoke;
			this->TabMakeCreature->Controls->Add(this->BtnMakeCreature);
			this->TabMakeCreature->Controls->Add(this->Elemets);
			this->TabMakeCreature->Controls->Add(this->Canvas);
			this->TabMakeCreature->Location = System::Drawing::Point(4, 27);
			this->TabMakeCreature->Name = L"TabMakeCreature";
			this->TabMakeCreature->Padding = System::Windows::Forms::Padding(3);
			this->TabMakeCreature->Size = System::Drawing::Size(899, 574);
			this->TabMakeCreature->TabIndex = 0;
			this->TabMakeCreature->Text = L"Make Creature";
			// 
			// BtnMakeCreature
			// 
			this->BtnMakeCreature->Location = System::Drawing::Point(693, 520);
			this->BtnMakeCreature->Name = L"BtnMakeCreature";
			this->BtnMakeCreature->Size = System::Drawing::Size(148, 46);
			this->BtnMakeCreature->TabIndex = 2;
			this->BtnMakeCreature->Text = L"Make Creature";
			this->BtnMakeCreature->UseVisualStyleBackColor = true;
			this->BtnMakeCreature->Click += gcnew System::EventHandler(this, &Creator::BtnMakeCreature_Click);
			// 
			// Elemets
			// 
			this->Elemets->Controls->Add(this->BtnClearCanvas);
			this->Elemets->Controls->Add(this->Line);
			this->Elemets->Controls->Add(this->Dot);
			this->Elemets->Location = System::Drawing::Point(604, 9);
			this->Elemets->Name = L"Elemets";
			this->Elemets->Size = System::Drawing::Size(287, 215);
			this->Elemets->TabIndex = 1;
			this->Elemets->TabStop = false;
			this->Elemets->Text = L"Elemets";
			// 
			// BtnClearCanvas
			// 
			this->BtnClearCanvas->Location = System::Drawing::Point(98, 153);
			this->BtnClearCanvas->Name = L"BtnClearCanvas";
			this->BtnClearCanvas->Size = System::Drawing::Size(127, 41);
			this->BtnClearCanvas->TabIndex = 2;
			this->BtnClearCanvas->Text = L"Clear Canvas";
			this->BtnClearCanvas->UseVisualStyleBackColor = true;
			this->BtnClearCanvas->Click += gcnew System::EventHandler(this, &Creator::BtnClearCanvas_Click);
			// 
			// Line
			// 
			this->Line->AutoSize = true;
			this->Line->Location = System::Drawing::Point(19, 85);
			this->Line->Name = L"Line";
			this->Line->Size = System::Drawing::Size(56, 22);
			this->Line->TabIndex = 1;
			this->Line->TabStop = true;
			this->Line->Text = L"Line";
			this->Line->UseVisualStyleBackColor = true;
			// 
			// Dot
			// 
			this->Dot->AutoSize = true;
			this->Dot->Location = System::Drawing::Point(19, 42);
			this->Dot->Name = L"Dot";
			this->Dot->Size = System::Drawing::Size(53, 22);
			this->Dot->TabIndex = 0;
			this->Dot->TabStop = true;
			this->Dot->Text = L"Dot";
			this->Dot->UseVisualStyleBackColor = true;
			// 
			// Canvas
			// 
			this->Canvas->BackColor = System::Drawing::Color::White;
			this->Canvas->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->Canvas->Location = System::Drawing::Point(9, 9);
			this->Canvas->Name = L"Canvas";
			this->Canvas->Size = System::Drawing::Size(589, 562);
			this->Canvas->TabIndex = 0;
			this->Canvas->TabStop = false;
			this->Canvas->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Creator::Canvas_MouseDown);
			this->Canvas->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Creator::Canvas_MouseMove);
			this->Canvas->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Creator::Canvas_MouseUp);
			// 
			// CreationProcess
			// 
			this->CreationProcess->Controls->Add(this->TabMakeCreature);
			this->CreationProcess->Controls->Add(this->TabChooseMovableLines);
			this->CreationProcess->Controls->Add(this->TabChooseTurnIntervals);
			this->CreationProcess->Controls->Add(this->TabChooseInitialStates);
			this->CreationProcess->Controls->Add(this->TabChooseConnections);
			this->CreationProcess->Controls->Add(this->TabSave);
			this->CreationProcess->Dock = System::Windows::Forms::DockStyle::Fill;
			this->CreationProcess->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->CreationProcess->Location = System::Drawing::Point(0, 0);
			this->CreationProcess->Multiline = true;
			this->CreationProcess->Name = L"CreationProcess";
			this->CreationProcess->SelectedIndex = 0;
			this->CreationProcess->Size = System::Drawing::Size(907, 605);
			this->CreationProcess->TabIndex = 0;
			this->CreationProcess->Selected += gcnew System::Windows::Forms::TabControlEventHandler(this, &Creator::CreationProcess_Selected);
			// 
			// TabChooseConnections
			// 
			this->TabChooseConnections->BackColor = System::Drawing::Color::WhiteSmoke;
			this->TabChooseConnections->Controls->Add(this->GrBoxCon);
			this->TabChooseConnections->Controls->Add(this->BtnNextCon);
			this->TabChooseConnections->Controls->Add(this->CanvasCon);
			this->TabChooseConnections->Location = System::Drawing::Point(4, 27);
			this->TabChooseConnections->Name = L"TabChooseConnections";
			this->TabChooseConnections->Padding = System::Windows::Forms::Padding(3);
			this->TabChooseConnections->Size = System::Drawing::Size(899, 574);
			this->TabChooseConnections->TabIndex = 5;
			this->TabChooseConnections->Text = L"Choose Connections";
			// 
			// GrBoxCon
			// 
			this->GrBoxCon->Controls->Add(this->CheckListBoxCon);
			this->GrBoxCon->Controls->Add(this->ComBoxLineCon);
			this->GrBoxCon->Controls->Add(this->LbLine3);
			this->GrBoxCon->Controls->Add(this->BtnSaveConnections);
			this->GrBoxCon->Location = System::Drawing::Point(604, 9);
			this->GrBoxCon->Name = L"GrBoxCon";
			this->GrBoxCon->Size = System::Drawing::Size(289, 490);
			this->GrBoxCon->TabIndex = 6;
			this->GrBoxCon->TabStop = false;
			this->GrBoxCon->Text = L"Choose connections";
			// 
			// CheckListBoxCon
			// 
			this->CheckListBoxCon->FormattingEnabled = true;
			this->CheckListBoxCon->Location = System::Drawing::Point(9, 84);
			this->CheckListBoxCon->Name = L"CheckListBoxCon";
			this->CheckListBoxCon->Size = System::Drawing::Size(274, 327);
			this->CheckListBoxCon->TabIndex = 5;
			// 
			// ComBoxLineCon
			// 
			this->ComBoxLineCon->BackColor = System::Drawing::SystemColors::Window;
			this->ComBoxLineCon->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->ComBoxLineCon->FormattingEnabled = true;
			this->ComBoxLineCon->Location = System::Drawing::Point(77, 37);
			this->ComBoxLineCon->Name = L"ComBoxLineCon";
			this->ComBoxLineCon->Size = System::Drawing::Size(206, 26);
			this->ComBoxLineCon->TabIndex = 1;
			this->ComBoxLineCon->SelectedIndexChanged += gcnew System::EventHandler(this, &Creator::ComBoxLineCon_SelectedIndexChanged);
			// 
			// LbLine3
			// 
			this->LbLine3->AutoSize = true;
			this->LbLine3->Location = System::Drawing::Point(6, 40);
			this->LbLine3->Name = L"LbLine3";
			this->LbLine3->Size = System::Drawing::Size(39, 18);
			this->LbLine3->TabIndex = 0;
			this->LbLine3->Text = L"Line:";
			// 
			// BtnSaveConnections
			// 
			this->BtnSaveConnections->Location = System::Drawing::Point(34, 433);
			this->BtnSaveConnections->Name = L"BtnSaveConnections";
			this->BtnSaveConnections->Size = System::Drawing::Size(224, 40);
			this->BtnSaveConnections->TabIndex = 4;
			this->BtnSaveConnections->Text = L"Save connections";
			this->BtnSaveConnections->UseVisualStyleBackColor = true;
			this->BtnSaveConnections->Click += gcnew System::EventHandler(this, &Creator::BtnSaveConnections_Click);
			// 
			// BtnNextCon
			// 
			this->BtnNextCon->Location = System::Drawing::Point(693, 520);
			this->BtnNextCon->Name = L"BtnNextCon";
			this->BtnNextCon->Size = System::Drawing::Size(148, 46);
			this->BtnNextCon->TabIndex = 3;
			this->BtnNextCon->Text = L"Next";
			this->BtnNextCon->UseVisualStyleBackColor = true;
			this->BtnNextCon->Click += gcnew System::EventHandler(this, &Creator::BtnNextCon_Click);
			// 
			// CanvasCon
			// 
			this->CanvasCon->BackColor = System::Drawing::Color::White;
			this->CanvasCon->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->CanvasCon->Location = System::Drawing::Point(9, 9);
			this->CanvasCon->Name = L"CanvasCon";
			this->CanvasCon->Size = System::Drawing::Size(589, 562);
			this->CanvasCon->TabIndex = 2;
			this->CanvasCon->TabStop = false;
			// 
			// TabSave
			// 
			this->TabSave->BackColor = System::Drawing::Color::WhiteSmoke;
			this->TabSave->Controls->Add(this->GrBoxSave);
			this->TabSave->Controls->Add(this->BtnClose);
			this->TabSave->Controls->Add(this->CanvasSave);
			this->TabSave->Location = System::Drawing::Point(4, 27);
			this->TabSave->Name = L"TabSave";
			this->TabSave->Padding = System::Windows::Forms::Padding(3);
			this->TabSave->Size = System::Drawing::Size(899, 574);
			this->TabSave->TabIndex = 6;
			this->TabSave->Text = L"Save";
			// 
			// GrBoxSave
			// 
			this->GrBoxSave->Controls->Add(this->TBoxCreatureName);
			this->GrBoxSave->Controls->Add(this->LbFilename);
			this->GrBoxSave->Controls->Add(this->BtnSaveToFile);
			this->GrBoxSave->Location = System::Drawing::Point(604, 9);
			this->GrBoxSave->Name = L"GrBoxSave";
			this->GrBoxSave->Size = System::Drawing::Size(289, 205);
			this->GrBoxSave->TabIndex = 6;
			this->GrBoxSave->TabStop = false;
			this->GrBoxSave->Text = L"Saving To File";
			// 
			// TBoxCreatureName
			// 
			this->TBoxCreatureName->Location = System::Drawing::Point(9, 74);
			this->TBoxCreatureName->Name = L"TBoxCreatureName";
			this->TBoxCreatureName->Size = System::Drawing::Size(274, 24);
			this->TBoxCreatureName->TabIndex = 5;
			// 
			// LbFilename
			// 
			this->LbFilename->AutoSize = true;
			this->LbFilename->Location = System::Drawing::Point(6, 40);
			this->LbFilename->Name = L"LbFilename";
			this->LbFilename->Size = System::Drawing::Size(110, 18);
			this->LbFilename->TabIndex = 0;
			this->LbFilename->Text = L"Creature name:";
			// 
			// BtnSaveToFile
			// 
			this->BtnSaveToFile->Location = System::Drawing::Point(34, 143);
			this->BtnSaveToFile->Name = L"BtnSaveToFile";
			this->BtnSaveToFile->Size = System::Drawing::Size(224, 40);
			this->BtnSaveToFile->TabIndex = 4;
			this->BtnSaveToFile->Text = L"Save To File";
			this->BtnSaveToFile->UseVisualStyleBackColor = true;
			this->BtnSaveToFile->Click += gcnew System::EventHandler(this, &Creator::BtnSaveToFile_Click);
			// 
			// BtnClose
			// 
			this->BtnClose->Location = System::Drawing::Point(693, 520);
			this->BtnClose->Name = L"BtnClose";
			this->BtnClose->Size = System::Drawing::Size(148, 46);
			this->BtnClose->TabIndex = 3;
			this->BtnClose->Text = L"Close";
			this->BtnClose->UseVisualStyleBackColor = true;
			this->BtnClose->Click += gcnew System::EventHandler(this, &Creator::BtnClose_Click);
			// 
			// CanvasSave
			// 
			this->CanvasSave->BackColor = System::Drawing::Color::White;
			this->CanvasSave->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->CanvasSave->Location = System::Drawing::Point(9, 9);
			this->CanvasSave->Name = L"CanvasSave";
			this->CanvasSave->Size = System::Drawing::Size(589, 562);
			this->CanvasSave->TabIndex = 2;
			this->CanvasSave->TabStop = false;
			// 
			// contextMenuStrip1
			// 
			this->contextMenuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->contextMenuStrip1->Name = L"contextMenuStrip1";
			this->contextMenuStrip1->Size = System::Drawing::Size(61, 4);
			// 
			// Creator
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(907, 605);
			this->Controls->Add(this->CreationProcess);
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(925, 652);
			this->MinimumSize = System::Drawing::Size(925, 652);
			this->Name = L"Creator";
			this->Text = L"Creator";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Creator::Creator_FormClosing);
			this->Load += gcnew System::EventHandler(this, &Creator::Creator_Load);
			this->TabChooseInitialStates->ResumeLayout(false);
			this->GrBoxInSt->ResumeLayout(false);
			this->GrBoxInSt->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->CanvasInSt))->EndInit();
			this->TabChooseTurnIntervals->ResumeLayout(false);
			this->GrBoxTInt->ResumeLayout(false);
			this->GrBoxTInt->PerformLayout();
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TrackBarMaxAng))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TrackBarMinAng))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->CanvasTInt))->EndInit();
			this->TabChooseMovableLines->ResumeLayout(false);
			this->GrBoxMvLines->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->CanvasMvLn))->EndInit();
			this->TabMakeCreature->ResumeLayout(false);
			this->Elemets->ResumeLayout(false);
			this->Elemets->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Canvas))->EndInit();
			this->CreationProcess->ResumeLayout(false);
			this->TabChooseConnections->ResumeLayout(false);
			this->GrBoxCon->ResumeLayout(false);
			this->GrBoxCon->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->CanvasCon))->EndInit();
			this->TabSave->ResumeLayout(false);
			this->GrBoxSave->ResumeLayout(false);
			this->GrBoxSave->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->CanvasSave))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion

		Image^ imgbuf;
		Image^ imgcur;
		Image^ imgMvLn;
		Image^ imgTIntcur;
		Image^ imgTIntbuf;
		Image^ imgInStcur;
		Image^ imgInStbuf;
		Image^ imgConcur;
		Image^ imgConbuf;
		Image^ imgSave;
		Graphics^ gr;
		Pen^ pen;
		SolidBrush^ brush;
		bool paint = false;
		double start_x = 0;
		double start_y = 0;
		double point_r = 5;

		int prev_selected_tab;


		void dfs(int v) {
			used[v] = 1;
			for (int i = 0; i < graph[v].size(); ++i) {
				if (used[graph[v][i]] == 0) {
					dfs(graph[v][i]);
				}
			}
		}

		double get_dist(double x1, double y1, double x2, double y2) {
			double res = sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
			return res;
		}

		double deg_to_rad(double deg_ang) {
			double res = deg_ang*1.0*M_PI / 180.0;
			return res;
		}

		double get_angle(double x1, double y1, double x2, double y2) {  //         / x2,y2
			//double res = 0.0;								            //        /
			//y2 *= -1.0; //из-за направления оси	(Плохо, так нельзя!!!!!!!!!!!)						// x1,y1 /______ 

			//if (x1 == x2) {
			//	if (y1 == y2)
			//		return res;
			//	if (y2 > y1)
			//		return res = 1.0 * M_PI / 2;
			//	else
			//		return res = 3.0 * M_PI / 2;
			//}

			//if (y1 == y2) {
			//	if (x2 > x1)
			//		return res = 0.0;
			//	else
			//		return res = 1.0*M_PI;
			//}

			//res = atan((1.0*abs(y2 - y1)) / (1.0*abs(x2 - x1)));
			//if (x2 > x1 && y2 > y1)
			//	return res;
			//if (x2 < x1 && y2 > y1)
			//	return res = M_PI - res;
			//if (x2 < x1 && y2 < y1)
			//	return res = M_PI + res;
			//if (x2 > x1 && y2 < y1)
			//	return res = 2 * M_PI - res;

			double res = 0.0;
			res = acos((x2 - x1) / get_dist(x1, y1, x2, y2));
			return 2 * M_PI - res;
		}


	private: System::Void Creator_Load(System::Object^  sender, System::EventArgs^  e) {

		joints.clear();
		new_joints.clear();
		lines.clear();
		movable_lines.clear();
		turn_ints.clear();
		mvstates.clear();
		refs.clear();

		unit_turn_angle = 0.0;
		unit_fall_angle = 0.0;

		points.clear();
		drlines.clear();

		start_point = -1;
		finish_point = -1;

		graph.clear();
		used.clear();

		TabChooseMovableLines->Enabled = false;
		TabChooseTurnIntervals->Enabled = false;
		TabChooseInitialStates->Enabled = false;
		TabChooseConnections->Enabled = false;
		TabSave->Enabled = false;

		prev_selected_tab = CreationProcess->SelectedIndex;

		imgbuf = gcnew Bitmap(Canvas->ClientSize.Width, Canvas->ClientSize.Height);
		imgcur = gcnew Bitmap(Canvas->ClientSize.Width, Canvas->ClientSize.Height);
		gr = Canvas->CreateGraphics();

		imgMvLn = gcnew Bitmap(CanvasMvLn->ClientSize.Width, CanvasMvLn->ClientSize.Height);

		imgTIntcur = gcnew Bitmap(CanvasTInt->ClientSize.Width, CanvasTInt->ClientSize.Height);
		imgTIntbuf = gcnew Bitmap(CanvasTInt->ClientSize.Width, CanvasTInt->ClientSize.Height);

		imgInStcur = gcnew Bitmap(CanvasInSt->ClientSize.Width, CanvasTInt->ClientSize.Height);
		imgInStbuf = gcnew Bitmap(CanvasInSt->ClientSize.Width, CanvasTInt->ClientSize.Height);

		imgConcur = gcnew Bitmap(CanvasCon->ClientSize.Width, CanvasTInt->ClientSize.Height);
		imgConbuf = gcnew Bitmap(CanvasCon->ClientSize.Width, CanvasTInt->ClientSize.Height);

		imgSave = gcnew Bitmap(CanvasCon->ClientSize.Width, CanvasTInt->ClientSize.Height);

		brush = gcnew SolidBrush(Color::Blue);
		pen = gcnew Pen(Brushes::Black);
	}

	private: System::Void Canvas_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		if (Line->Checked) {
			bool can_paint_line = false;
			double sx = -1, sy = -1, ppos = -1;
			for (int i = 0; i < points.size(); ++i) {
				double sqrdist = (points[i].first - e->X)*(points[i].first - e->X) + (points[i].second - e->Y)*(points[i].second - e->Y);
				if (sqrdist < (point_r * point_r)) {
					can_paint_line = true;
					sx = points[i].first;
					sy = points[i].second;
					ppos = i;
				}
			}
			if (can_paint_line) {
				paint = true;
				start_x = sx;
				start_y = sy;
				start_point = ppos;
				delete imgbuf;
				imgbuf = gcnew Bitmap(Canvas->BackgroundImage);
			}
		}
	}
	private: System::Void Canvas_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		if (Line->Checked) {
			if (paint) {
				delete imgcur;
				imgcur = gcnew Bitmap(imgbuf);
				Graphics^ g = Graphics::FromImage(imgcur);
				g->DrawLine(pen, Point(start_x, start_y), Point(e->X, e->Y));
				Canvas->BackgroundImage = imgcur;
				delete g;
			}
		}
	}
	private: System::Void Canvas_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		if (Dot->Checked) {
			bool can_paint_dot = true;
			for (int i = 0; i < points.size(); ++i) {
				double sqrdist = (points[i].first - e->X)*(points[i].first - e->X) + (points[i].second - e->Y)*(points[i].second - e->Y);
				if (sqrdist < (2 * point_r * 2 * point_r)) {
					can_paint_dot = false;
				}
			}

			if (can_paint_dot) {
				delete imgcur;
				imgcur = gcnew Bitmap(imgbuf);
				Graphics^ g = Graphics::FromImage(imgcur);
				g->FillEllipse(brush, RectangleF(e->X - point_r, e->Y - point_r, 2 * point_r, 2 * point_r));
				Canvas->BackgroundImage = imgcur;
				delete imgbuf;
				imgbuf = gcnew Bitmap(Canvas->BackgroundImage);
				delete g;

				points.push_back(std::make_pair(e->X, e->Y));
			}
		}
		else if (Line->Checked && paint) {
			paint = false;

			bool can_paint_line = false;
			double fx = -1, fy = -1;
			for (int i = 0; i < points.size(); ++i) {
				double sqrdist = (points[i].first - e->X)*(points[i].first - e->X) + (points[i].second - e->Y)*(points[i].second - e->Y);
				if (sqrdist < (2 * point_r * 2 * point_r)) {
					can_paint_line = true;
					fx = points[i].first;
					fy = points[i].second;
					finish_point = i;
				}
			}

			delete imgcur;
			imgcur = gcnew Bitmap(imgbuf);

			if (can_paint_line) {
				Graphics^ g = Graphics::FromImage(imgcur);
				pen = gcnew Pen(Brushes::Black);
				g->DrawLine(pen, Point(start_x, start_y), Point(fx, fy));
				delete g;

				if (start_point < finish_point)
					drlines.insert(std::make_pair(start_point, finish_point));
				else if (start_point > finish_point)
					drlines.insert(std::make_pair(finish_point, start_point));
			}
			Canvas->BackgroundImage = imgcur;

			delete imgbuf;
			imgbuf = gcnew Bitmap(Canvas->BackgroundImage);

			start_x = 0;
			start_y = 0;
			start_point = -1;
			finish_point = -1;
		}
	}

	private: System::Void BtnClearCanvas_Click(System::Object^  sender, System::EventArgs^  e) {
		points.clear();
		drlines.clear();
		delete imgbuf;
		delete imgcur;
		imgbuf = gcnew Bitmap(Canvas->ClientSize.Width, Canvas->ClientSize.Height);
		imgcur = gcnew Bitmap(Canvas->ClientSize.Width, Canvas->ClientSize.Height);
		gr->Clear(Canvas->BackColor);
	}

	private: System::Void BtnMakeCreature_Click(System::Object^  sender, System::EventArgs^  e) {
		joints.clear();
		lines.clear();
		graph.clear();
		used.clear();


		graph.resize(points.size());
		used.resize(points.size(), 0);
		// Точки, которые соединены отрезками
		std::set<int> used_points;
		for (auto it = drlines.begin(); it != drlines.end(); ++it) {
			used_points.insert(it->first);
			used_points.insert(it->second);
			graph[it->first].push_back(it->second);
			graph[it->second].push_back(it->first);
		}

		// Отмечаем -1 точки, которые не соединены отрезками
		int component_count = 0;
		for (int i = 0; i < points.size(); ++i) {
			if (used_points.count(i) == 0) {
				used[i] = -1;
				continue;
			}
			if (used[i] == 0) {
				dfs(i);
				component_count++;
			}
		}

		if (component_count > 1) { // несколько групп отрезков, не связанных между собой
			MessageBox::Show("Error!\nСлишком много компонент");
		}
		else if (drlines.size() < 2) {
			MessageBox::Show("Error!\nСлишком мало соединений");
		}
		else {
			// Перенумеруем точки (удаляем те, которые не используютя)
			int cou = 0;
			for (int i = 0; i < points.size(); ++i) {
				if (used[i] == -1) continue;
				joints.push_back(points[i]);
				used[i] = cou;
				cou++;
			}
			points = joints;

			for (auto it = drlines.begin(); it != drlines.end(); ++it) {
				lines.push_back(std::make_pair(used[it->first], used[it->second]));
			}
			drlines.clear();
			for (int i = 0; i < lines.size(); ++i) {
				drlines.insert(lines[i]);
			}


			// Рисунок на текущей вкладке
			delete imgcur;
			imgcur = gcnew Bitmap(CanvasMvLn->ClientSize.Width, CanvasMvLn->ClientSize.Height);
			Graphics^ g = Graphics::FromImage(imgcur);

			// Рисунок на следующей вкладке
			delete imgMvLn;
			imgMvLn = gcnew Bitmap(CanvasMvLn->ClientSize.Width, CanvasMvLn->ClientSize.Height);
			Graphics^ gMvLn = Graphics::FromImage(imgMvLn);

			System::Drawing::Font^ font = gcnew System::Drawing::Font(TabChooseMovableLines->Font->FontFamily, 12);

			brush->Color = Color::Red;
			for (int i = 0; i < lines.size(); ++i) {
				double x1 = joints[lines[i].first].first;
				double y1 = joints[lines[i].first].second;
				double x2 = joints[lines[i].second].first;
				double y2 = joints[lines[i].second].second;
				g->DrawLine(pen, Point(x1, y1), Point(x2, y2));
				gMvLn->DrawLine(pen, Point(x1, y1), Point(x2, y2));

				// Номера отрезков
				gMvLn->DrawString(Convert::ToString(i + 1), font, brush, RectangleF((x1 + x2) / 2 - 2 * point_r, (y1 + y2) / 2 - 2 * point_r, 8 * point_r, 4 * point_r));
			}
			brush->Color = Color::Blue;

			for (int i = 0; i < joints.size(); ++i) {
				g->FillEllipse(brush, RectangleF(joints[i].first - point_r, joints[i].second - point_r, 2 * point_r, 2 * point_r));
				gMvLn->FillEllipse(brush, RectangleF(joints[i].first - 2 * point_r, joints[i].second - 2 * point_r, 4 * point_r, 4 * point_r));

				// Номера точек
				brush->Color = Color::White;
				gMvLn->DrawString(Convert::ToString(i + 1), font, brush, RectangleF(joints[i].first - 2 * point_r, joints[i].second - 2 * point_r, 8 * point_r, 4 * point_r));
				brush->Color = Color::Blue;
			}

			delete font;

			Canvas->BackgroundImage = imgcur;
			delete imgbuf;
			imgbuf = gcnew Bitmap(Canvas->BackgroundImage);
			delete g;

			CanvasMvLn->BackgroundImage = imgMvLn;
			delete gMvLn;

			// Добавление элементов в CheckListBoxMvLines
			CheckListBoxMvLines->Items->Clear();
			for (int i = 0; i < lines.size(); ++i) {
				std::string st1 = "line " + std::to_string(i + 1) + " (joint " + std::to_string(lines[i].first + 1) + ")";
				std::string st2 = "line " + std::to_string(i + 1) + " (joint " + std::to_string(lines[i].second + 1) + ")";
				String^ s1 = gcnew String(st1.c_str());
				String^ s2 = gcnew String(st2.c_str());
				CheckListBoxMvLines->Items->Add(s1, false);
				CheckListBoxMvLines->Items->Add(s2, false);
				delete s1;
				delete s2;
			}

			TabChooseMovableLines->Enabled = true;
			CreationProcess->SelectedTab = TabChooseMovableLines;
			prev_selected_tab = CreationProcess->SelectedIndex;
		}

	}

	private: System::Void CreationProcess_Selected(System::Object^  sender, System::Windows::Forms::TabControlEventArgs^  e) {
		if (prev_selected_tab > CreationProcess->SelectedIndex) {
			for (int i = CreationProcess->SelectedIndex + 1; i < CreationProcess->TabPages->Count; ++i) {
				CreationProcess->TabPages[i]->Enabled = false;
			}
		}
		prev_selected_tab = CreationProcess->SelectedIndex;

	}

	private: System::Void CheckListBoxMvLines_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		// Выделение отмеченных отрезков
		delete imgMvLn;
		imgMvLn = gcnew Bitmap(CanvasMvLn->ClientSize.Width, CanvasMvLn->ClientSize.Height);
		Graphics^ gMvLn = Graphics::FromImage(imgMvLn);

		System::Drawing::Font^ font = gcnew System::Drawing::Font(TabChooseMovableLines->Font->FontFamily, 12);

		brush->Color = Color::Red;
		int cou = 0;
		std::set<int> red_points;
		for (int i = 0; i < lines.size(); ++i) {
			double x1 = joints[lines[i].first].first;
			double y1 = joints[lines[i].first].second;
			double x2 = joints[lines[i].second].first;
			double y2 = joints[lines[i].second].second;

			pen->Color = Color::Black;
			pen->Width = 1;

			// Чтобы был выбран только один сустав поворота
			if (CheckListBoxMvLines->GetItemChecked(cou) || CheckListBoxMvLines->GetItemChecked(cou + 1)) {
				pen->Color = Color::Red;
				pen->Width = 3;
				if (CheckListBoxMvLines->SelectedIndex == cou) {
					if (CheckListBoxMvLines->GetItemChecked(cou)) {
						CheckListBoxMvLines->SetItemChecked(cou + 1, false);
						red_points.insert(lines[i].first);
					}
					else red_points.insert(lines[i].second);
				}
				else if (CheckListBoxMvLines->SelectedIndex == cou + 1) {
					if (CheckListBoxMvLines->GetItemChecked(cou + 1)) {
						CheckListBoxMvLines->SetItemChecked(cou, false);
						red_points.insert(lines[i].second);
					}
					else red_points.insert(lines[i].first);
				}
				else {
					if (CheckListBoxMvLines->GetItemChecked(cou)) red_points.insert(lines[i].first);
					else red_points.insert(lines[i].second);
				}
			}

			gMvLn->DrawLine(pen, Point(x1, y1), Point(x2, y2));

			// Номера отрезков
			gMvLn->DrawString(Convert::ToString(i + 1), font, brush, RectangleF((x1 + x2) / 2 - 2 * point_r, (y1 + y2) / 2 - 2 * point_r, 8 * point_r, 4 * point_r));

			cou += 2;
		}
		brush->Color = Color::Blue;
		pen->Color = Color::Black;
		pen->Width = 1;

		for (int i = 0; i < joints.size(); ++i) {
			brush->Color = Color::Blue;
			if (red_points.count(i) != 0)
				brush->Color = Color::Red;

			gMvLn->FillEllipse(brush, RectangleF(joints[i].first - 2 * point_r, joints[i].second - 2 * point_r, 4 * point_r, 4 * point_r));

			// Номера точек
			brush->Color = Color::White;
			gMvLn->DrawString(Convert::ToString(i + 1), font, brush, RectangleF(joints[i].first - 2 * point_r, joints[i].second - 2 * point_r, 8 * point_r, 4 * point_r));
		}
		brush->Color = Color::Blue;
		delete font;

		CanvasMvLn->BackgroundImage = imgMvLn;
		delete gMvLn;
	}

	private: System::Void BtnNextMvLn_Click(System::Object^  sender, System::EventArgs^  e) {
		movable_lines.clear();
		int cou = 0;
		for (int i = 0; i < lines.size(); ++i) {
			if (CheckListBoxMvLines->GetItemChecked(cou)) {
				if (graph[lines[i].first].size() > 1) // Проверка сустава на возможность изгиба
					movable_lines.push_back(std::make_pair(i, lines[i].first));
			}
			else if (CheckListBoxMvLines->GetItemChecked(cou + 1)) {
				if (graph[lines[i].second].size() > 1) // Проверка сустава на возможность изгиба
					movable_lines.push_back(std::make_pair(i, lines[i].second));
			}
			cou += 2;
		}

		if (movable_lines.size() < 1) {
			MessageBox::Show("Error!\nПодвижные отрезки не выбраны \nили выбраные недопустимые суставы");
		}
		else {
			// Рисунок на следующей вкладке
			delete imgTIntcur;
			imgTIntcur = gcnew Bitmap(CanvasTInt->ClientSize.Width, CanvasTInt->ClientSize.Height);
			Graphics^ gTInt = Graphics::FromImage(imgTIntcur);

			System::Drawing::Font^ font = gcnew System::Drawing::Font(TabChooseMovableLines->Font->FontFamily, 12);

			brush->Color = Color::Red;
			for (int i = 0; i < lines.size(); ++i) {
				double x1 = joints[lines[i].first].first;
				double y1 = joints[lines[i].first].second;
				double x2 = joints[lines[i].second].first;
				double y2 = joints[lines[i].second].second;
				gTInt->DrawLine(pen, Point(x1, y1), Point(x2, y2));

				// Номера отрезков
				gTInt->DrawString(Convert::ToString(i + 1), font, brush, RectangleF((x1 + x2) / 2 - 2 * point_r, (y1 + y2) / 2 - 2 * point_r, 8 * point_r, 4 * point_r));
			}
			brush->Color = Color::Black;

			for (int i = 0; i < joints.size(); ++i) {
				gTInt->FillEllipse(brush, RectangleF(joints[i].first - 2 * point_r, joints[i].second - 2 * point_r, 4 * point_r, 4 * point_r));

				// Номера точек
				brush->Color = Color::White;
				gTInt->DrawString(Convert::ToString(i + 1), font, brush, RectangleF(joints[i].first - 2 * point_r, joints[i].second - 2 * point_r, 8 * point_r, 4 * point_r));
				brush->Color = Color::Black;
			}
			brush->Color = Color::Blue;
			delete font;

			CanvasTInt->BackgroundImage = imgTIntcur;
			delete imgTIntbuf;
			imgTIntbuf = gcnew Bitmap(CanvasTInt->BackgroundImage);
			delete gTInt;

			//Добавление отрезков в ComBoxLineTInt
			ComBoxLineTInt->Items->Clear();
			for (int i = 0; i < movable_lines.size(); ++i) {
				std::string st = "line " + std::to_string(movable_lines[i].first + 1) + " (joint " + std::to_string(movable_lines[i].second + 1) + ")";
				String^ s = gcnew String(st.c_str());
				ComBoxLineTInt->Items->Add(s);
				delete s;
			}

			turn_ints.clear();
			turn_ints.resize(lines.size(), std::make_pair(-1.0, -1.0));

			ComBoxLineTInt->SelectedIndex = 0;

			TBoxUnitAngle->Text = L"1";
			TBoxFallAngle->Text = L"1";

			TBoxMinAngle->Text = L"0";
			TBoxMaxAngle->Text = L"0";

			TrackBarMinAng->Value = 0;
			TrackBarMaxAng->Value = 0;

			TabChooseTurnIntervals->Enabled = true;
			CreationProcess->SelectedTab = TabChooseTurnIntervals;
			prev_selected_tab = CreationProcess->SelectedIndex;
		}
	}

	private: System::Void BtnShowTInt_Click(System::Object^  sender, System::EventArgs^  e) {
		try {
			double min_ang = Convert::ToDouble(TBoxMinAngle->Text);
			double max_ang = Convert::ToDouble(TBoxMaxAngle->Text);

			if (min_ang > max_ang) {
				MessageBox::Show("Error!\nДиапазон границы заданы некорректно");
			}
			else if (min_ang < 0.0 || max_ang < 0.0) {
				MessageBox::Show("Error!\nЗначения углов должны быть положительными");
			}
			else {

				int line = ComBoxLineTInt->SelectedIndex;
				int mvline = movable_lines[line].first;
				turn_ints[mvline] = std::make_pair(min_ang, max_ang);

				// Изменение рисунка
				delete imgTIntcur;
				imgTIntcur = gcnew Bitmap(imgTIntbuf);
				Graphics^ gTInt = Graphics::FromImage(imgTIntcur);

				System::Drawing::Font^ font = gcnew System::Drawing::Font(TabChooseMovableLines->Font->FontFamily, 12);

				pen->Color = Color::Blue;
				pen->Width = 2;
				// Отрезки
				int osp, nosp;
				osp = movable_lines[line].second;
				if (lines[mvline].first != osp) nosp = lines[mvline].first;
				else nosp = lines[mvline].second;
				double x1 = joints[osp].first;
				double y1 = joints[osp].second;
				double x2 = joints[nosp].first;
				double y2 = joints[nosp].second;
				gTInt->DrawLine(pen, Point(x1, y1), Point(x2, y2));

				double linelen = get_dist(x1, y1, x2, y2);

				double mnx2 = x1 + linelen*cos(deg_to_rad(min_ang));
				double mny2 = y1 - linelen*sin(deg_to_rad(min_ang)); // тк ось Oy направлена вниз

				double mxx2 = x1 + linelen*cos(deg_to_rad(max_ang));
				double mxy2 = y1 - linelen*sin(deg_to_rad(max_ang));

				pen->Color = Color::Red;
				gTInt->DrawLine(pen, Point(x1, y1), Point(mnx2, mny2));
				gTInt->DrawLine(pen, Point(x1, y1), Point(mxx2, mxy2));

				pen->Color = Color::Black;
				pen->Width = 1;

				// Номер отрезка
				gTInt->DrawString(Convert::ToString(mvline + 1), font, brush, RectangleF((x1 + x2) / 2 - 2 * point_r, (y1 + y2) / 2 - 2 * point_r, 8 * point_r, 4 * point_r));

				//Точки
				brush->Color = Color::Red;
				gTInt->FillEllipse(brush, RectangleF(x1 - 2 * point_r, y1 - 2 * point_r, 4 * point_r, 4 * point_r));
				gTInt->FillEllipse(brush, RectangleF(mnx2 - 2 * point_r, mny2 - 2 * point_r, 4 * point_r, 4 * point_r));
				gTInt->FillEllipse(brush, RectangleF(mxx2 - 2 * point_r, mxy2 - 2 * point_r, 4 * point_r, 4 * point_r));
				brush->Color = Color::Black;
				gTInt->FillEllipse(brush, RectangleF(x2 - 2 * point_r, y2 - 2 * point_r, 4 * point_r, 4 * point_r));


				brush->Color = Color::White;
				// Номера точек
				gTInt->DrawString(Convert::ToString(osp + 1), font, brush, RectangleF(x1 - 2 * point_r, y1 - 2 * point_r, 8 * point_r, 4 * point_r));
				gTInt->DrawString(Convert::ToString(nosp + 1), font, brush, RectangleF(x2 - 2 * point_r, y2 - 2 * point_r, 8 * point_r, 4 * point_r));
				brush->Color = Color::Blue;

				delete font;

				CanvasTInt->BackgroundImage = imgTIntcur;
				delete gTInt;
			}
		}
		catch (...) {
			MessageBox::Show("Error!\nПоля заполнены некорректно\nВозможно, следует заменить точку на запятую");
		}
	}

	private: System::Void ComBoxLineTInt_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		int line = ComBoxLineTInt->SelectedIndex;
		int mvline = movable_lines[line].first;
		double min_ang = turn_ints[mvline].first;
		double max_ang = turn_ints[mvline].second;

		bool fl_selected_int = true;
		if (min_ang == -1.0 || max_ang == -1.0) {
			fl_selected_int = false;
		}

		// Изменение рисунка
		delete imgTIntcur;
		imgTIntcur = gcnew Bitmap(imgTIntbuf);
		Graphics^ gTInt = Graphics::FromImage(imgTIntcur);

		System::Drawing::Font^ font = gcnew System::Drawing::Font(TabChooseMovableLines->Font->FontFamily, 12);

		pen->Color = Color::Blue;
		pen->Width = 2;
		// Отрезки
		int osp, nosp;
		osp = movable_lines[line].second;
		if (lines[mvline].first != osp) nosp = lines[mvline].first;
		else nosp = lines[mvline].second;
		double x1 = joints[osp].first;
		double y1 = joints[osp].second;
		double x2 = joints[nosp].first;
		double y2 = joints[nosp].second;
		gTInt->DrawLine(pen, Point(x1, y1), Point(x2, y2));

		double linelen = get_dist(x1, y1, x2, y2);

		double mnx2 = x1 + linelen*cos(deg_to_rad(min_ang));
		double mny2 = y1 - linelen*sin(deg_to_rad(min_ang)); // тк ось Oy направлена вниз

		double mxx2 = x1 + linelen*cos(deg_to_rad(max_ang));
		double mxy2 = y1 - linelen*sin(deg_to_rad(max_ang));

		if (fl_selected_int) {
			pen->Color = Color::Red;
			gTInt->DrawLine(pen, Point(x1, y1), Point(mnx2, mny2));
			gTInt->DrawLine(pen, Point(x1, y1), Point(mxx2, mxy2));
		}

		pen->Color = Color::Black;
		pen->Width = 1;

		// Номер отрезка
		gTInt->DrawString(Convert::ToString(mvline + 1), font, brush, RectangleF((x1 + x2) / 2 - 2 * point_r, (y1 + y2) / 2 - 2 * point_r, 8 * point_r, 4 * point_r));

		//Точки
		if (fl_selected_int) {
			brush->Color = Color::Red;
			gTInt->FillEllipse(brush, RectangleF(x1 - 2 * point_r, y1 - 2 * point_r, 4 * point_r, 4 * point_r));
			gTInt->FillEllipse(brush, RectangleF(mnx2 - 2 * point_r, mny2 - 2 * point_r, 4 * point_r, 4 * point_r));
			gTInt->FillEllipse(brush, RectangleF(mxx2 - 2 * point_r, mxy2 - 2 * point_r, 4 * point_r, 4 * point_r));
		}
		else {
			gTInt->FillEllipse(brush, RectangleF(x1 - 2 * point_r, y1 - 2 * point_r, 4 * point_r, 4 * point_r));
		}
		brush->Color = Color::Black;
		gTInt->FillEllipse(brush, RectangleF(x2 - 2 * point_r, y2 - 2 * point_r, 4 * point_r, 4 * point_r));


		brush->Color = Color::White;
		// Номера точек
		gTInt->DrawString(Convert::ToString(osp + 1), font, brush, RectangleF(x1 - 2 * point_r, y1 - 2 * point_r, 8 * point_r, 4 * point_r));
		gTInt->DrawString(Convert::ToString(nosp + 1), font, brush, RectangleF(x2 - 2 * point_r, y2 - 2 * point_r, 8 * point_r, 4 * point_r));
		brush->Color = Color::Blue;

		delete font;

		CanvasTInt->BackgroundImage = imgTIntcur;
		delete gTInt;

		if (fl_selected_int) {
			TBoxMinAngle->Text = Convert::ToString(turn_ints[mvline].first);
			TBoxMaxAngle->Text = Convert::ToString(turn_ints[mvline].second);
		}
		else {
			TBoxMinAngle->Clear();
			TBoxMaxAngle->Clear();
		}

	}

	private: System::Void BtnNextTInt_Click(System::Object^  sender, System::EventArgs^  e) {
		try {
			unit_turn_angle = Convert::ToDouble(TBoxUnitAngle->Text);
			unit_fall_angle = Convert::ToDouble(TBoxFallAngle->Text);

			if (unit_turn_angle <= 0.0 || unit_fall_angle <= 0.0) {
				MessageBox::Show("Error!\nЗначения углов должны быть положительными");
			}
			else {
				//Прорисовка
				delete imgInStcur;
				imgInStcur = gcnew Bitmap(imgTIntbuf);
				CanvasInSt->BackgroundImage = imgInStcur;
				delete imgInStbuf;
				imgInStbuf = gcnew Bitmap(CanvasInSt->BackgroundImage);

				//Добавление отрезков в ComBoxLineInSt
				ComBoxLineInSt->Items->Clear();
				for (int i = 0; i < movable_lines.size(); ++i) {
					std::string st = "line " + std::to_string(movable_lines[i].first + 1) + " (joint " + std::to_string(movable_lines[i].second + 1) + ")";
					String^ s = gcnew String(st.c_str());
					ComBoxLineInSt->Items->Add(s);
					delete s;
				}

				mvstates.clear();
				mvstates.resize(lines.size(), std::make_pair(-1, 0));

				// Просчет количества состояний
				for (int i = 0;i < mvstates.size(); ++i) {
					mvstates[i].second = (turn_ints[i].second - turn_ints[i].first) / unit_turn_angle + 1; //не учитывается интервал%единичный_угол!!!!!
				}

				ComBoxLineInSt->SelectedIndex = 0;

				TabChooseInitialStates->Enabled = true;
				CreationProcess->SelectedTab = TabChooseInitialStates;
				prev_selected_tab = CreationProcess->SelectedIndex;
			}
		}
		catch (...) {
			MessageBox::Show("Error!\nПоля заполнены некорректно\nВозможно, следует заменить точку на запятую");
		}
	}

	private: System::Void ComBoxLineInSt_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		//Добавление отрезков в ComBoxStateInSt
		ComBoxStateInSt->Items->Clear();
		int line = ComBoxLineInSt->SelectedIndex;
		int mvline = movable_lines[line].first;
		for (int i = 0; i < mvstates[mvline].second; ++i) {
			ComBoxStateInSt->Items->Add(i + 1);
		}

		// Прорисовка состояний выбранного отрезка
		delete imgInStcur;
		imgInStcur = gcnew Bitmap(imgInStbuf);
		Graphics^ gInSt = Graphics::FromImage(imgInStcur);

		int osp = movable_lines[line].second;
		int nosp;
		if (lines[mvline].first != osp) nosp = lines[mvline].first;
		else nosp = lines[mvline].second;

		// Выделение выбранного отрезка
		pen->Color = Color::Blue;
		pen->Width = 2;
		double x1 = joints[osp].first;
		double y1 = joints[osp].second;
		double x2 = joints[nosp].first;
		double y2 = joints[nosp].second;
		gInSt->DrawLine(pen, Point(x1, y1), Point(x2, y2));

		// Состояния
		System::Drawing::Font^ font = gcnew System::Drawing::Font(TabChooseMovableLines->Font->FontFamily, 6);
		int curang = (turn_ints[mvline].first != -1.0) ? turn_ints[mvline].first : 0.0;
		double len = get_dist(x1, y1, x2, y2) * 0.75;
		pen->Color = Color::Red;
		pen->Width = 1;
		for (int i = 0; i < mvstates[mvline].second; ++i) {
			double xx = x1 + len*cos(deg_to_rad(curang));
			double yy = y1 - len*sin(deg_to_rad(curang));
			gInSt->DrawLine(pen, Point(x1, y1), Point(xx, yy));
			//Точка в конце
			brush->Color = Color::Red;
			gInSt->FillEllipse(brush, RectangleF(xx - 1.5*point_r, yy - 1.5*point_r, 3 * point_r, 3 * point_r));
			//Номер состояния
			brush->Color = Color::White;
			gInSt->DrawString(Convert::ToString(i + 1), font, brush, RectangleF(xx - 1.5*point_r + 2, yy - 1.5*point_r + 2, 6 * point_r, 3 * point_r));
			curang += unit_turn_angle;
		}
		brush->Color = Color::Blue;
		gInSt->FillEllipse(brush, RectangleF(x1 - 2 * point_r, y1 - 2 * point_r, 4 * point_r, 4 * point_r));
		brush->Color = Color::Black;
		gInSt->FillEllipse(brush, RectangleF(x2 - 2 * point_r, y2 - 2 * point_r, 4 * point_r, 4 * point_r));
		brush->Color = Color::White;
		font = gcnew System::Drawing::Font(TabChooseMovableLines->Font->FontFamily, 12);
		gInSt->DrawString(Convert::ToString(osp + 1), font, brush, RectangleF(x1 - 2 * point_r, y1 - 2 * point_r, 8 * point_r, 4 * point_r));
		gInSt->DrawString(Convert::ToString(nosp + 1), font, brush, RectangleF(x2 - 2 * point_r, y2 - 2 * point_r, 8 * point_r, 4 * point_r));
		pen->Color = Color::Black;
		brush->Color = Color::Blue;
		delete font;

		CanvasInSt->BackgroundImage = imgInStcur;
		delete gInSt;

		if (mvstates[mvline].first != -1)
			ComBoxStateInSt->SelectedIndex = mvstates[mvline].first;
		else ComBoxStateInSt->SelectedIndex = 0;
	}

	private: System::Void BtnSaveState_Click(System::Object^  sender, System::EventArgs^  e) {
		int line = ComBoxLineInSt->SelectedIndex;
		int mvline = movable_lines[line].first;
		mvstates[mvline].first = ComBoxStateInSt->SelectedIndex;
	}

	private: System::Void BtnNextInSt_Click(System::Object^  sender, System::EventArgs^  e) {
		//Прорисовка
		delete imgConcur;
		imgConcur = gcnew Bitmap(imgInStbuf);
		CanvasCon->BackgroundImage = imgConcur;
		delete imgInStbuf;
		imgConbuf = gcnew Bitmap(CanvasCon->BackgroundImage);

		// Устанавливаем нулевое состояние по умолчанию
		for (int i = 0; i < movable_lines.size(); ++i) {
			if (mvstates[movable_lines[i].first].first == -1)
				mvstates[movable_lines[i].first].first = 0;
		}

		refs.clear();
		refs.resize(lines.size());

		ComBoxLineCon->Items->Clear();
		for (int i = 0; i < movable_lines.size(); ++i) {
			std::string st = "line " + std::to_string(movable_lines[i].first + 1) + " (joint " + std::to_string(movable_lines[i].second + 1) + ")";
			String^ s = gcnew String(st.c_str());
			ComBoxLineCon->Items->Add(s);
			delete s;
		}

		ComBoxLineCon->SelectedIndex = 0;

		TabChooseConnections->Enabled = true;
		CreationProcess->SelectedTab = TabChooseConnections;
		prev_selected_tab = CreationProcess->SelectedIndex;
	}

	private: System::Void ComBoxLineCon_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		int selected_line = movable_lines[ComBoxLineCon->SelectedIndex].first;
		CheckListBoxCon->Items->Clear();
		for (int i = 0; i < lines.size(); ++i) {
			if (i == selected_line) continue;
			std::string st = "line " + std::to_string(i + 1);
			String^ s = gcnew String(st.c_str());
			CheckListBoxCon->Items->Add(s);
			delete s;
		}

		for (int i = 0; i < refs[selected_line].size(); ++i) {
			int pos = refs[selected_line][i];
			if (pos >= selected_line) pos--;
			CheckListBoxCon->SetItemChecked(pos, true);
		}

		// Прорисовка состояний выбранного отрезка
		delete imgConcur;
		imgConcur = gcnew Bitmap(imgConbuf);
		Graphics^ gCon = Graphics::FromImage(imgConcur);

		int osp = movable_lines[ComBoxLineCon->SelectedIndex].second;
		int nosp;
		if (lines[selected_line].first != osp) nosp = lines[selected_line].first;
		else nosp = lines[selected_line].second;

		// Выделение выбранного отрезка
		pen->Color = Color::Blue;
		pen->Width = 2;
		double x1 = joints[osp].first;
		double y1 = joints[osp].second;
		double x2 = joints[nosp].first;
		double y2 = joints[nosp].second;
		gCon->DrawLine(pen, Point(x1, y1), Point(x2, y2));

		// Состояния
		brush->Color = Color::Blue;
		gCon->FillEllipse(brush, RectangleF(x1 - 2 * point_r, y1 - 2 * point_r, 4 * point_r, 4 * point_r));
		brush->Color = Color::Black;
		gCon->FillEllipse(brush, RectangleF(x2 - 2 * point_r, y2 - 2 * point_r, 4 * point_r, 4 * point_r));
		brush->Color = Color::White;
		System::Drawing::Font^ font = gcnew System::Drawing::Font(TabChooseMovableLines->Font->FontFamily, 12);
		gCon->DrawString(Convert::ToString(osp + 1), font, brush, RectangleF(x1 - 2 * point_r, y1 - 2 * point_r, 8 * point_r, 4 * point_r));
		gCon->DrawString(Convert::ToString(nosp + 1), font, brush, RectangleF(x2 - 2 * point_r, y2 - 2 * point_r, 8 * point_r, 4 * point_r));
		pen->Color = Color::Black;
		brush->Color = Color::Blue;
		delete font;

		CanvasCon->BackgroundImage = imgConcur;
		delete gCon;

	}

	private: System::Void BtnSaveConnections_Click(System::Object^  sender, System::EventArgs^  e) {
		int selected_line = movable_lines[ComBoxLineCon->SelectedIndex].first;
		refs[selected_line].clear();
		int pos = 0;
		for (int i = 0; i < lines.size(); ++i) {
			if (i == selected_line) continue;
			if (CheckListBoxCon->GetItemChecked(pos)) {
				refs[selected_line].push_back(i);
			}
			pos++;
		}
	}

	private: System::Void BtnNextCon_Click(System::Object^  sender, System::EventArgs^  e) {
		new_joints.clear();
		new_joints = joints;

		for (int i = 0; i < movable_lines.size(); ++i) {
			int mvline = movable_lines[i].first;
			int osp = movable_lines[i].second;
			int nosp;
			if (lines[mvline].first != osp) nosp = lines[mvline].first;
			else nosp = lines[mvline].second;

			std::set<int> rpoints;
			rpoints.insert(nosp);

			for (int j = 0; j < refs[mvline].size(); ++j) {
				if (lines[refs[mvline][j]].first != osp) rpoints.insert(lines[refs[mvline][j]].first);
				if (lines[refs[mvline][j]].second != osp) rpoints.insert(lines[refs[mvline][j]].second);
			}

			//rad
			double curang = get_angle(new_joints[osp].first, new_joints[osp].second, new_joints[nosp].first, new_joints[nosp].second);
			//deg
			double needang = (turn_ints[mvline].first != -1.0) ? turn_ints[mvline].first : 0.0;
			needang += unit_turn_angle*mvstates[mvline].first;
			needang = deg_to_rad(needang);
			double deltaang = needang - curang;

			for (auto it = rpoints.begin(); it != rpoints.end(); ++it) {
				double dist = get_dist(new_joints[osp].first, new_joints[osp].second, new_joints[*it].first, new_joints[*it].second);
				double ang = get_angle(new_joints[osp].first, new_joints[osp].second, new_joints[*it].first, new_joints[*it].second);
				ang += deltaang;
				new_joints[*it].first = new_joints[osp].first + dist*cos(ang);
				new_joints[*it].second = new_joints[osp].second - dist*sin(ang);
			}
		}

		// Прорисовка
		delete imgSave;
		imgSave = gcnew Bitmap(CanvasTInt->ClientSize.Width, CanvasTInt->ClientSize.Height);
		Graphics^ gSave = Graphics::FromImage(imgSave);

		brush->Color = Color::Black;
		for (int i = 0; i < lines.size(); ++i) {
			double x1 = new_joints[lines[i].first].first;
			double y1 = new_joints[lines[i].first].second;
			double x2 = new_joints[lines[i].second].first;
			double y2 = new_joints[lines[i].second].second;
			gSave->DrawLine(pen, Point(x1, y1), Point(x2, y2));
		}

		for (int i = 0; i < joints.size(); ++i) {
			gSave->FillEllipse(brush, RectangleF(new_joints[i].first - point_r, new_joints[i].second - point_r, 2 * point_r, 2 * point_r));
		}
		brush->Color = Color::Blue;

		CanvasSave->BackgroundImage = imgSave;
		delete gSave;


		TBoxCreatureName->Text = Convert::ToString(CREATURENAME);

		TabSave->Enabled = true;
		CreationProcess->SelectedTab = TabSave;
		prev_selected_tab = CreationProcess->SelectedIndex;

	}

	private: System::Void BtnSaveToFile_Click(System::Object^  sender, System::EventArgs^  e) {
		std::string crfilename;
		std::string imgfilename;
		Creature new_creature;

		bool fl_filename = true;
		if (TBoxCreatureName->Text->Length != 0) {
			std::string creature_name = msclr::interop::marshal_as<std::string>(TBoxCreatureName->Text);
			for (int i = 0; i < creature_name.length(); ++i) {
				if (creature_name[i] == ' ')
					creature_name[i] = '_';
			}
			new_creature.name = creature_name;
			crfilename = creatures_dir_str + creature_name + creature_finame_end;
			imgfilename = creatures_dir_str + creature_name + img_finame_end;
		}
		else {
			fl_filename = false;
			MessageBox::Show("Error!\nНе задано имя");
		}

		std::ofstream fout(crfilename);

		if (fl_filename && fout.is_open()) {
			double max_y = -DBL_MAX;
			for (int i = 0; i < new_joints.size(); ++i) {
				if (new_joints[i].second > max_y) {
					max_y = new_joints[i].second;
				}
			}

			fout << "------------------Joints-------------------" << std::endl;
			fout << new_joints.size() << std::endl;
			new_creature.joints.resize(new_joints.size());
			for (int i = 0; i < new_joints.size(); ++i) {
				double new_y = fabs(new_joints[i].second - max_y); // Изменение направления оси Oy (направление ее вверх) 
				fout << new_joints[i].first << " " << new_y << std::endl;

				new_creature.joints[i].first = new_joints[i].first;
				new_creature.joints[i].second = new_y;
			}

			fout << "------------------Lines(poit_num1 point_num2)-------------------" << std::endl;
			fout << lines.size() << std::endl;
			for (int i = 0; i < lines.size(); ++i) {
				fout << lines[i].first << " " << lines[i].second << std::endl;
			}
			new_creature.lines = lines;

			fout << "------------------Movable lines (line_num turn_point_num)-------------------" << std::endl;
			fout << movable_lines.size() << std::endl;
			for (int i = 0; i < movable_lines.size(); ++i) {
				fout << movable_lines[i].first << " " << movable_lines[i].second << std::endl;
			}
			new_creature.movable_lines = movable_lines;

			fout << "------------------Unit fall angle-------------------" << std::endl;
			fout << deg_to_rad(unit_fall_angle) << std::endl;
			new_creature.fall_unit_angle = unit_fall_angle;

			fout << "------------------Unit turn angle-------------------" << std::endl;
			fout << deg_to_rad(unit_turn_angle) << std::endl;
			new_creature.turn_unit_angle = unit_turn_angle;

			fout << "------------------Turn intervals (min_angle max_angle)-------------------" << std::endl;
			fout << turn_ints.size() << std::endl;
			new_creature.turn_intervals.resize(turn_ints.size());
			for (int i = 0; i < turn_ints.size(); ++i) {
				double min_ang = (turn_ints[i].first != -1.0) ? turn_ints[i].first : 0.0;
				double max_ang = min_ang + unit_turn_angle*(mvstates[i].second - 1);
				min_ang = deg_to_rad(min_ang);
				max_ang = deg_to_rad(max_ang);
				fout << min_ang << " " << max_ang << std::endl;

				new_creature.turn_intervals[i].first = min_ang;
				new_creature.turn_intervals[i].second = max_ang;
			}

			fout << "------------------Initial states (state_num state_count)-------------------" << std::endl;
			fout << mvstates.size() << std::endl;
			for (int i = 0; i < mvstates.size(); ++i) {
				fout << mvstates[i].first << " " << mvstates[i].second << std::endl;
			}
			new_creature.states_mvlines = mvstates;

			fout << "------------------Dependent lines (line_count list_of_lines)-------------------" << std::endl;
			fout << refs.size() << std::endl;
			for (int i = 0; i < refs.size(); ++i) {
				fout << refs[i].size() << " ";
				for (int j = 0; j < refs[i].size(); ++j) {
					fout << refs[i][j] << " ";
				}
				fout << std::endl;
			}
			new_creature.refs = refs;

			fout.close();

			creatures.push_back(new_creature);
			creatures_names[new_creature.name] = creatures.size() - 1;

			String^ sfname = gcnew String(imgfilename.c_str());
			imgSave->Save(sfname);
			delete sfname;

			std::string message = "Message!\nДанные записаны в файл \"" + crfilename + "\"";
			String^ s = gcnew String(message.c_str());
			MessageBox::Show(s);
		}
		else {
			MessageBox::Show("Error!\nНевозможно открыть файл");
		}
	}

	private: System::Void BtnClose_Click(System::Object^  sender, System::EventArgs^  e) {
		Creator::Close();
	}

	private: System::Void Creator_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
		if (CreationProcess->SelectedTab == TabSave) {
			if (MessageBox::Show(this, "Созранить данные в файл?", "Form Closing", MessageBoxButtons::YesNo) == System::Windows::Forms::DialogResult::Yes)
			{
				// Отменить закрытие формы
				e->Cancel = true;
			}
		}
		else {
			if (MessageBox::Show(this, "Закрыть приложение?", "Form Closing", MessageBoxButtons::YesNo) == System::Windows::Forms::DialogResult::No)
			{
				// Отменить закрытие формы
				e->Cancel = true;
			}
		}
	}
	private: System::Void TrackBarMinAng_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
		TBoxMinAngle->Text = Convert::ToString(TrackBarMinAng->Value);
	}
	private: System::Void TrackBarMaxAng_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
		TBoxMaxAngle->Text = Convert::ToString(TrackBarMaxAng->Value);
	}
	private: System::Void TBoxMinAngle_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		try {
			double min_angle = Convert::ToDouble(TBoxMinAngle->Text);
			int min_angle_int = min_angle;
			if (min_angle_int < 0)
				min_angle_int = 0;
			else if (min_angle_int > 720)
				min_angle_int = 720;

			TrackBarMinAng->Value = min_angle_int;

		}
		catch (...) {
			TrackBarMinAng->Value = 0;
		}
	}
	private: System::Void TBoxMaxAngle_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		try {
			double max_angle = Convert::ToDouble(TBoxMaxAngle->Text);
			int max_angle_int = max_angle;
			if (max_angle_int < 0)
				max_angle_int = 0;
			else if (max_angle_int > 720)
				max_angle_int = 720;

			TrackBarMaxAng->Value = max_angle_int;

		}
		catch (...) {
			TrackBarMaxAng->Value = 0;
		}
	}
	};
}
