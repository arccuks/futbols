#pragma once
#include "Ball.h"
#include "Field.h"
#define PI 3.1415926535897932385

class Ball;
class Field;

namespace Project1 {

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
			form1 = this;
			CreateField();
			ball = new Ball();

			ball->moveTo(100, 100);
			ball->setSpeed(40);
			ball->setDir(PI / 4 - 0.1);
		}
		static MyForm ^form1;
		Ball *ball;
		Field * field;
		void Simulate();

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
		void DrawGame();
		void CreateField();

	protected:


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
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(686, 371);
			this->Controls->Add(this->buttonStop);
			this->Controls->Add(this->buttonStart);
			this->DoubleBuffered = true;
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MyForm::MyForm_FormClosing);
			this->ResizeEnd += gcnew System::EventHandler(this, &MyForm::MyForm_ResizeEnd);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::MyForm_Paint);
			this->ResumeLayout(false);

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
		CreateField();
		DrawGame();
	}
	private: System::Void MyForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
		if (drawThread != nullptr && drawThread->IsAlive) {
			drawThread->Abort();
		}
	}
	private: System::Void MyForm_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
		DrawGame();
	}

	};
}
