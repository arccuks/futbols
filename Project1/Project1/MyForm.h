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

enum state { sStop, sRunning, sPause, sGoal, sRestartGame, sFirstKick };

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

			for (int i = 0; i<5; ++i) girl[i] = gcnew Girl;
			lights[0] = gcnew Lights(0, 0, 250, PI / 32, -PI / 12, -PI / 2 + PI / 12, PI / 12, PI / 3);
			lights[1] = gcnew Lights(FieldImage->Width, 0, 250, PI / 32, -PI / 2 - PI / 8, -PI + PI / 8, PI / 12, PI / 3);
			position0();
			drawAll();

			for (int i = 0; i < Team1.Count; i++) Team1[i]->setEnergy((rand()% 2000) + 2000);
			for (int i = 0; i < Team2.Count; i++) Team2[i]->setEnergy((rand() % 2000) + 2000);
			gameState = sStop;
			scoreL = scoreR = 0;
			time = 0;
		}
		
	private: System::Windows::Forms::Panel^  panelField;
	private: System::Windows::Forms::CheckBox^  checkBoxSound;
			 int time;
			 void energyControl();
	public:
		Ball ^ball;
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
			this->SuspendLayout();
			// 
			// buttonStart
			// 
			this->buttonStart->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->buttonStart->Location = System::Drawing::Point(599, 307);
			this->buttonStart->Name = L"buttonStart";
			this->buttonStart->Size = System::Drawing::Size(75, 23);
			this->buttonStart->TabIndex = 0;
			this->buttonStart->Text = L"Start";
			this->buttonStart->UseVisualStyleBackColor = true;
			this->buttonStart->Click += gcnew System::EventHandler(this, &MyForm::buttonStart_Click);
			// 
			// buttonStop
			// 
			this->buttonStop->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->buttonStop->Location = System::Drawing::Point(599, 336);
			this->buttonStop->Name = L"buttonStop";
			this->buttonStop->Size = System::Drawing::Size(75, 23);
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
			this->panelField->Size = System::Drawing::Size(581, 347);
			this->panelField->TabIndex = 2;
			// 
			// checkBoxSound
			// 
			this->checkBoxSound->AutoSize = true;
			this->checkBoxSound->Location = System::Drawing::Point(599, 284);
			this->checkBoxSound->Name = L"checkBoxSound";
			this->checkBoxSound->Size = System::Drawing::Size(57, 17);
			this->checkBoxSound->TabIndex = 3;
			this->checkBoxSound->Text = L"Sound";
			this->checkBoxSound->UseVisualStyleBackColor = true;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(686, 371);
			this->Controls->Add(this->checkBoxSound);
			this->Controls->Add(this->panelField);
			this->Controls->Add(this->buttonStop);
			this->Controls->Add(this->buttonStart);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MyForm::MyForm_FormClosing);
			this->ResizeEnd += gcnew System::EventHandler(this, &MyForm::MyForm_ResizeEnd);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::MyForm_Paint);
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

	};
}