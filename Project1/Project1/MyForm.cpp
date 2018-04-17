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
		DrawGame();
		Sleep(50);
	}
}

void Project1::MyForm::DrawGame()
{
	//Paštaisīts DOUBLE BUFFER!!
	//Atrisina flickering problēmu :)
	BufferedGraphicsContext ^currentContext;
	BufferedGraphics ^myBuffer;
	// Gets a reference to the current BufferedGraphicsContext
	currentContext = BufferedGraphicsManager::Current;
	// Creates a BufferedGraphics instance associated with Form1, and with 
	// dimensions the same size as the drawing surface of Form1.
	myBuffer = currentContext->Allocate(this->CreateGraphics(),
		this->DisplayRectangle);

	//Tā kā zīmēju uz formas, tad "notīru" formu pirms katras zīmēšanas
	SolidBrush ^myBrush = gcnew SolidBrush(form1->BackColor);
	myBuffer->Graphics->FillRectangle(myBrush, System::Drawing::Rectangle(0, 0, form1->Width, form1->Height));

	field->draw(myBuffer);
	ball->draw(myBuffer);

	myBuffer->Render();
	myBuffer->Render(this->CreateGraphics());

	delete myBuffer;
}


// Uzlieku laukuma izmērus
void Project1::MyForm::CreateField()
{
	field = new Field(form1->Width - 107, form1->Height - 50);
}
