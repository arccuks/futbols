#pragma once
//---------------------------------------------------------------------------
#include "Ball.h"
#include "Field.h"
#include <vector>
#include "Girl.h"
#include "Lights.h"
#include "Player.h"
#include "AssReferee.h"
#include "Referee.h"
#include "Forward.h"
#include "HalfBack.h"
#include "FullBack.h"
#include "Goalkeeper.h"


#define PI 3.1415926535897932385

//class Field;
//class Ball;
//class AssReferee;
//class Referee;
//class Player;
//class Girl;
//class Lights;

enum state { sStop, sRunning, sPause, sGoal, sRestartGame, sFirstKick, sGameStart };

using namespace System::Collections::Generic;

namespace Futbols {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			mainForm = this;
			FieldImage = panelField;

			field = gcnew Field;
			ball = gcnew Ball;
			assRef1 = gcnew AssReferee();
			assRef2 = gcnew AssReferee();
			referee = gcnew Referee();

			Player ^p;
			// Make Team1
			int n = 0;
			p = gcnew Forward(1, ++n);
			Team1.Add(p);
			p = gcnew Forward(1, ++n);
			Team1.Add(p);
			p = gcnew Forward(1, ++n);
			Team1.Add(p);
			p = gcnew HalfBack(1, ++n);
			Team1.Add(p);
			p = gcnew FullBack(1, ++n);
			Team1.Add(p);
			p = gcnew FullBack(1, ++n);
			Team1.Add(p);
			p = gcnew Goalkeeper(1, ++n);
			Team1.Add(p);
			// Make Team2
			n = 0;
			p = gcnew Forward(2, ++n);
			Team2.Add(p);
			p = gcnew Forward(2, ++n);
			Team2.Add(p);
			p = gcnew Forward(2, ++n);
			Team2.Add(p);
			p = gcnew HalfBack(2, ++n);
			Team2.Add(p);
			p = gcnew FullBack(2, ++n);
			Team2.Add(p);
			p = gcnew FullBack(2, ++n);
			Team2.Add(p);
			p = gcnew Goalkeeper(2, ++n);
			Team2.Add(p);

			for (int i = 0; i < 5; ++i) girl[i] = gcnew Girl;
			lights[0] = gcnew Lights(0, 0, 250, PI / 32, -PI / 12, -PI / 2 + PI / 12, PI / 12, PI / 3);
			lights[1] = gcnew Lights(FieldImage->Width, 0, 250, PI / 32, -PI / 2 - PI / 8, -PI + PI / 8, PI / 12, PI / 3);
			position0();
			drawAll();

			for (int i = 0; i < Team1.Count; i++) Team1[i]->setEnergy((rand() % 2000) + 2000);
			for (int i = 0; i < Team2.Count; i++) Team2[i]->setEnergy((rand() % 2000) + 2000);
			gameState = sStop;
			scoreL = scoreR = 0;
			time = 0;

			gameState = sGameStart;
		}

	private: System::Windows::Forms::Panel^  panelField;
	private: System::Windows::Forms::CheckBox^  checkBoxSound;
	private: System::Windows::Forms::CheckBox^  checkBoxGirls;
	private: System::Windows::Forms::NumericUpDown^  nudTeam1;
	private: System::Windows::Forms::NumericUpDown^  nudTeam2;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::CheckBox^  cbT26;
	private: System::Windows::Forms::CheckBox^  cbT25;
	private: System::Windows::Forms::CheckBox^  cbT24;
	private: System::Windows::Forms::CheckBox^  cbT23;
	private: System::Windows::Forms::CheckBox^  cbT22;





	private: System::Windows::Forms::CheckBox^  cbT16;

	private: System::Windows::Forms::CheckBox^  cbT15;

	private: System::Windows::Forms::CheckBox^  cbT14;

	private: System::Windows::Forms::CheckBox^  cbT13;

	private: System::Windows::Forms::CheckBox^  cbT12;

			 int time;
			 void energyControl();
			 void setEnergyTeam1(int);
			 void setEnergyTeam2(int);
	public:
		Ball ^ ball;
		Field ^field;
		Referee ^referee;
		AssReferee ^assRef1;
		AssReferee ^assRef2;
		List<Player^> Team1;
		List<Player^> Team2;
		static array<Girl^> ^girl = gcnew array<Girl^>(5);
		static array<Lights^> ^lights = gcnew array<Lights^>(2);

		String ^EnergyLeft;

		void Simulate();
		static MyForm ^mainForm;
		static Panel ^FieldImage;

		state gameState;

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  buttonStart;
	private: System::Windows::Forms::Button^  buttonStop;
	private:
		bool canSimulateGame = false;
		Thread ^drawThread;

	private:
		void startGame();
		void drawAll();
		void moveAll();
		void position0();
		void position1();
		void position2();
		void sound(String ^soundFile);

		int scoreL;
		int scoreR;



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
			this->buttonStart = (gcnew System::Windows::Forms::Button());
			this->buttonStop = (gcnew System::Windows::Forms::Button());
			this->panelField = (gcnew System::Windows::Forms::Panel());
			this->checkBoxSound = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxGirls = (gcnew System::Windows::Forms::CheckBox());
			this->nudTeam1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->nudTeam2 = (gcnew System::Windows::Forms::NumericUpDown());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->cbT26 = (gcnew System::Windows::Forms::CheckBox());
			this->cbT25 = (gcnew System::Windows::Forms::CheckBox());
			this->cbT24 = (gcnew System::Windows::Forms::CheckBox());
			this->cbT23 = (gcnew System::Windows::Forms::CheckBox());
			this->cbT22 = (gcnew System::Windows::Forms::CheckBox());
			this->cbT16 = (gcnew System::Windows::Forms::CheckBox());
			this->cbT15 = (gcnew System::Windows::Forms::CheckBox());
			this->cbT14 = (gcnew System::Windows::Forms::CheckBox());
			this->cbT13 = (gcnew System::Windows::Forms::CheckBox());
			this->cbT12 = (gcnew System::Windows::Forms::CheckBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudTeam1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudTeam2))->BeginInit();
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// buttonStart
			// 
			this->buttonStart->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->buttonStart->Location = System::Drawing::Point(554, 307);
			this->buttonStart->Name = L"buttonStart";
			this->buttonStart->Size = System::Drawing::Size(111, 23);
			this->buttonStart->TabIndex = 0;
			this->buttonStart->Text = L"Start";
			this->buttonStart->UseVisualStyleBackColor = true;
			this->buttonStart->Click += gcnew System::EventHandler(this, &MyForm::buttonStart_Click);
			// 
			// buttonStop
			// 
			this->buttonStop->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->buttonStop->Location = System::Drawing::Point(554, 336);
			this->buttonStop->Name = L"buttonStop";
			this->buttonStop->Size = System::Drawing::Size(111, 23);
			this->buttonStop->TabIndex = 1;
			this->buttonStop->Text = L"Stop";
			this->buttonStop->UseVisualStyleBackColor = true;
			this->buttonStop->Click += gcnew System::EventHandler(this, &MyForm::buttonStop_Click);
			// 
			// panelField
			// 
			this->panelField->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->panelField->Location = System::Drawing::Point(12, 12);
			this->panelField->Name = L"panelField";
			this->panelField->Size = System::Drawing::Size(536, 347);
			this->panelField->TabIndex = 2;
			// 
			// checkBoxSound
			// 
			this->checkBoxSound->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->checkBoxSound->AutoSize = true;
			this->checkBoxSound->Location = System::Drawing::Point(579, 284);
			this->checkBoxSound->Name = L"checkBoxSound";
			this->checkBoxSound->Size = System::Drawing::Size(57, 17);
			this->checkBoxSound->TabIndex = 3;
			this->checkBoxSound->Text = L"Sound";
			this->checkBoxSound->UseVisualStyleBackColor = true;
			// 
			// checkBoxGirls
			// 
			this->checkBoxGirls->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->checkBoxGirls->AutoSize = true;
			this->checkBoxGirls->Location = System::Drawing::Point(579, 261);
			this->checkBoxGirls->Name = L"checkBoxGirls";
			this->checkBoxGirls->Size = System::Drawing::Size(86, 17);
			this->checkBoxGirls->TabIndex = 4;
			this->checkBoxGirls->Text = L"Pause Show";
			this->checkBoxGirls->UseVisualStyleBackColor = true;
			// 
			// nudTeam1
			// 
			this->nudTeam1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->nudTeam1->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
			this->nudTeam1->Location = System::Drawing::Point(554, 53);
			this->nudTeam1->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100000, 0, 0, 0 });
			this->nudTeam1->Name = L"nudTeam1";
			this->nudTeam1->Size = System::Drawing::Size(52, 20);
			this->nudTeam1->TabIndex = 5;
			this->nudTeam1->ValueChanged += gcnew System::EventHandler(this, &MyForm::nudTeam1_ValueChanged);
			// 
			// nudTeam2
			// 
			this->nudTeam2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->nudTeam2->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
			this->nudTeam2->Location = System::Drawing::Point(612, 53);
			this->nudTeam2->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100000, 0, 0, 0 });
			this->nudTeam2->Name = L"nudTeam2";
			this->nudTeam2->Size = System::Drawing::Size(52, 20);
			this->nudTeam2->TabIndex = 6;
			this->nudTeam2->ValueChanged += gcnew System::EventHandler(this, &MyForm::nudTeam2_ValueChanged);
			// 
			// groupBox1
			// 
			this->groupBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->groupBox1->Controls->Add(this->cbT26);
			this->groupBox1->Controls->Add(this->cbT25);
			this->groupBox1->Controls->Add(this->cbT24);
			this->groupBox1->Controls->Add(this->cbT23);
			this->groupBox1->Controls->Add(this->cbT22);
			this->groupBox1->Controls->Add(this->cbT16);
			this->groupBox1->Controls->Add(this->cbT15);
			this->groupBox1->Controls->Add(this->cbT14);
			this->groupBox1->Controls->Add(this->cbT13);
			this->groupBox1->Controls->Add(this->cbT12);
			this->groupBox1->Location = System::Drawing::Point(554, 79);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(110, 176);
			this->groupBox1->TabIndex = 7;
			this->groupBox1->TabStop = false;
			// 
			// cbT26
			// 
			this->cbT26->AutoSize = true;
			this->cbT26->Location = System::Drawing::Point(89, 112);
			this->cbT26->Name = L"cbT26";
			this->cbT26->Size = System::Drawing::Size(15, 14);
			this->cbT26->TabIndex = 9;
			this->cbT26->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->cbT26->UseVisualStyleBackColor = true;
			this->cbT26->CheckedChanged += gcnew System::EventHandler(this, &MyForm::cbT26_CheckedChanged);
			// 
			// cbT25
			// 
			this->cbT25->AutoSize = true;
			this->cbT25->Location = System::Drawing::Point(89, 89);
			this->cbT25->Name = L"cbT25";
			this->cbT25->Size = System::Drawing::Size(15, 14);
			this->cbT25->TabIndex = 8;
			this->cbT25->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->cbT25->UseVisualStyleBackColor = true;
			this->cbT25->CheckedChanged += gcnew System::EventHandler(this, &MyForm::cbT25_CheckedChanged);
			// 
			// cbT24
			// 
			this->cbT24->AutoSize = true;
			this->cbT24->Location = System::Drawing::Point(89, 66);
			this->cbT24->Name = L"cbT24";
			this->cbT24->Size = System::Drawing::Size(15, 14);
			this->cbT24->TabIndex = 7;
			this->cbT24->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->cbT24->UseVisualStyleBackColor = true;
			this->cbT24->CheckedChanged += gcnew System::EventHandler(this, &MyForm::cbT24_CheckedChanged);
			// 
			// cbT23
			// 
			this->cbT23->AutoSize = true;
			this->cbT23->Location = System::Drawing::Point(89, 43);
			this->cbT23->Name = L"cbT23";
			this->cbT23->Size = System::Drawing::Size(15, 14);
			this->cbT23->TabIndex = 6;
			this->cbT23->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->cbT23->UseVisualStyleBackColor = true;
			this->cbT23->CheckedChanged += gcnew System::EventHandler(this, &MyForm::cbT23_CheckedChanged);
			// 
			// cbT22
			// 
			this->cbT22->AutoSize = true;
			this->cbT22->Location = System::Drawing::Point(89, 20);
			this->cbT22->Name = L"cbT22";
			this->cbT22->Size = System::Drawing::Size(15, 14);
			this->cbT22->TabIndex = 5;
			this->cbT22->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->cbT22->UseVisualStyleBackColor = true;
			this->cbT22->CheckedChanged += gcnew System::EventHandler(this, &MyForm::cbT22_CheckedChanged);
			// 
			// cbT16
			// 
			this->cbT16->AutoSize = true;
			this->cbT16->Location = System::Drawing::Point(0, 111);
			this->cbT16->Name = L"cbT16";
			this->cbT16->Size = System::Drawing::Size(62, 17);
			this->cbT16->TabIndex = 4;
			this->cbT16->Text = L"          6";
			this->cbT16->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->cbT16->UseVisualStyleBackColor = true;
			this->cbT16->CheckedChanged += gcnew System::EventHandler(this, &MyForm::cbT16_CheckedChanged);
			// 
			// cbT15
			// 
			this->cbT15->AutoSize = true;
			this->cbT15->Location = System::Drawing::Point(0, 88);
			this->cbT15->Name = L"cbT15";
			this->cbT15->Size = System::Drawing::Size(62, 17);
			this->cbT15->TabIndex = 3;
			this->cbT15->Text = L"          5";
			this->cbT15->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->cbT15->UseVisualStyleBackColor = true;
			this->cbT15->CheckedChanged += gcnew System::EventHandler(this, &MyForm::cbT15_CheckedChanged);
			// 
			// cbT14
			// 
			this->cbT14->AutoSize = true;
			this->cbT14->Location = System::Drawing::Point(0, 65);
			this->cbT14->Name = L"cbT14";
			this->cbT14->Size = System::Drawing::Size(62, 17);
			this->cbT14->TabIndex = 2;
			this->cbT14->Text = L"          4";
			this->cbT14->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->cbT14->UseVisualStyleBackColor = true;
			this->cbT14->CheckedChanged += gcnew System::EventHandler(this, &MyForm::cbT14_CheckedChanged);
			// 
			// cbT13
			// 
			this->cbT13->AutoSize = true;
			this->cbT13->Location = System::Drawing::Point(0, 42);
			this->cbT13->Name = L"cbT13";
			this->cbT13->Size = System::Drawing::Size(62, 17);
			this->cbT13->TabIndex = 1;
			this->cbT13->Text = L"          3";
			this->cbT13->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->cbT13->UseVisualStyleBackColor = true;
			this->cbT13->CheckedChanged += gcnew System::EventHandler(this, &MyForm::cbT13_CheckedChanged);
			// 
			// cbT12
			// 
			this->cbT12->AutoSize = true;
			this->cbT12->Location = System::Drawing::Point(0, 19);
			this->cbT12->Name = L"cbT12";
			this->cbT12->Size = System::Drawing::Size(62, 17);
			this->cbT12->TabIndex = 0;
			this->cbT12->Text = L"          2";
			this->cbT12->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->cbT12->UseVisualStyleBackColor = true;
			this->cbT12->CheckedChanged += gcnew System::EventHandler(this, &MyForm::cbT12_CheckedChanged);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(677, 371);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->nudTeam2);
			this->Controls->Add(this->nudTeam1);
			this->Controls->Add(this->checkBoxGirls);
			this->Controls->Add(this->checkBoxSound);
			this->Controls->Add(this->panelField);
			this->Controls->Add(this->buttonStop);
			this->Controls->Add(this->buttonStart);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MyForm::MyForm_FormClosing);
			this->ResizeEnd += gcnew System::EventHandler(this, &MyForm::MyForm_ResizeEnd);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::MyForm_Paint);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudTeam1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudTeam2))->EndInit();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void buttonStart_Click(System::Object^  sender, System::EventArgs^  e) {
		canSimulateGame = true;
		drawThread = gcnew Thread(gcnew ThreadStart(this, &MyForm::Simulate));
		drawThread->Start();

		this->buttonStart->Enabled = false;
		this->buttonStop->Enabled = true;
	}
	private: System::Void buttonStop_Click(System::Object^  sender, System::EventArgs^  e) {
		canSimulateGame = false;
		this->buttonStart->Enabled = true;
		this->buttonStop->Enabled = false;
		//FG_Frm->CommentText->Caption = "Pause...";
		gameState = sStop;
	}
	private: System::Void MyForm_ResizeEnd(System::Object^  sender, System::EventArgs^  e) {
		/*CreateField();
		DrawGame();*/
	}
	private: System::Void MyForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
		if (drawThread != nullptr && drawThread->IsAlive) {
			drawThread->Abort();
		}
	}
	private: System::Void MyForm_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
		drawAll();
	}

	private: System::Void nudTeam1_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
		int enPortion = (int)nudTeam1->Value / Team1.Count;
		for (int i = 0; i < Team1.Count; i++) Team1[i]->setEnergy(enPortion);
	}
	private: System::Void nudTeam2_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
		int enPortion = (int)nudTeam2->Value / Team2.Count;
		for (int i = 0; i < Team2.Count; i++) Team2[i]->setEnergy(enPortion);
	}


	private: System::Void cbT12_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		Team1[1]->inGame = cbT12->Checked;
	}
	private: System::Void cbT13_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		Team1[2]->inGame = cbT13->Checked;
	}
	private: System::Void cbT14_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		Team1[3]->inGame = cbT14->Checked;
	}
	private: System::Void cbT15_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		Team1[4]->inGame = cbT15->Checked;
	}
	private: System::Void cbT16_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		Team1[5]->inGame = cbT16->Checked;
	}
	private: System::Void cbT22_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		Team2[1]->inGame = cbT22->Checked;
	}
	private: System::Void cbT23_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		Team2[2]->inGame = cbT23->Checked;
	}
	private: System::Void cbT24_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		Team2[3]->inGame = cbT24->Checked;
	}
	private: System::Void cbT25_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		Team2[4]->inGame = cbT25->Checked;
	}
	private: System::Void cbT26_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		Team2[5]->inGame = cbT26->Checked;
	}
	};
}