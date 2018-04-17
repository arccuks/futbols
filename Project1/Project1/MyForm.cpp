#include "MyForm.h"
#include "Ball.h"
#include "Field.h"
#include "Windows.h"


using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
void Main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Project1::MyForm form;
	Application::Run(%form);
}

void Project1::MyForm::Simulate()
{
	while (canSimulateGame) {

		//MessageBox::Show("Fuck");

		ball->move();
		DrawField();
		Sleep(50);
	}
}

void Project1::MyForm::DrawField()
{
	SolidBrush ^myBrush = gcnew SolidBrush(form1->BackColor);
	Graphics ^a = Project1::MyForm::form1->CreateGraphics();
	a->FillRectangle(myBrush, System::Drawing::Rectangle(0, 0, form1->Width, form1->Height));

	field->draw();
	ball->draw();
}

void Project1::MyForm::CreateField()
{
	field = new Field(form1->Width - 107, form1->Height - 50);
}
