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
	Futbols::MyForm form;
	Application::Run(%form);
}

void Futbols::MyForm::Simulate()
{
	while (canSimulateGame) {

		//MessageBox::Show("Fuck");

		ball->move();
		DrawGame();
		Sleep(50);
	}
}

void Futbols::MyForm::DrawGame()
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
	SolidBrush ^myBrush = gcnew SolidBrush(mainForm->BackColor);
	myBuffer->Graphics->FillRectangle(myBrush, System::Drawing::Rectangle(0, 0, mainForm->Width, mainForm->Height));

	delete myBrush;

	field->draw(myBuffer);
	ball->draw(myBuffer);

	//sis laikam nav vajadzīgs
	//myBuffer->Render();
	myBuffer->Render(this->CreateGraphics());

	//mem leak fix
	delete myBuffer;
	currentContext = nullptr;
	delete currentContext;

	//it kā mazliet palīdz, but it is never good to call it
	//GC::Collect();
}


// Uzlieku laukuma izmērus
void Futbols::MyForm::CreateField()
{
	field = new Field(mainForm->Width - 107, mainForm->Height - 50);
}
