#include "MyForm.h"
#include "Ball.h"
#include "Field.h"
#include "Windows.h"
#include <stdlib.h>


using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
void Main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Futbols::MyForm form;
	Application::Run(%form);
}

void Futbols::MyForm::energyControl()
{
	int enL = 0, enR = 0;
	for (int i = 0; i < Team1.Count; i++) enL += Team1[i]->getEnergy();
	for (int i = 0; i < Team2.Count; i++) enR += Team2[i]->getEnergy();
	setEnergyTeam1(enL);
	setEnergyTeam2(enR);
}

//Thread safe call, nevareju savadak mainit nup veribas.
delegate void callbackSetEnergyTeam1(int energy);
void Futbols::MyForm::setEnergyTeam1(int energy) {

	if (this->nudTeam1->InvokeRequired)
	{
		callbackSetEnergyTeam1^ d =
			gcnew callbackSetEnergyTeam1(this, &Futbols::MyForm::setEnergyTeam1);
		this->Invoke(d, gcnew array<Object^> { energy });
	}
	else
	{
		this->nudTeam1->Value = energy;
	}	
}

delegate void cbSetCommentText(String ^);
void Futbols::MyForm::setCommentText(String ^text) {

	if (this->nudTeam1->InvokeRequired)
	{
		cbSetCommentText^ d =
			gcnew cbSetCommentText(this, &Futbols::MyForm::setCommentText);
		this->Invoke(d, gcnew array<Object^> { text });
	}
	else
	{
		this->textBoxComments->Text = text;
	}
}

delegate void callbackSetEnergyTeam2(int energy);
void Futbols::MyForm::setEnergyTeam2(int energy) {

	if (this->nudTeam2->InvokeRequired)
	{
		callbackSetEnergyTeam1^ d =
			gcnew callbackSetEnergyTeam1(this, &Futbols::MyForm::setEnergyTeam2);
		this->Invoke(d, gcnew array<Object^> { energy });
	}
	else
	{
		this->nudTeam2->Value = energy;
	}
}

void Futbols::MyForm::Simulate()
{
	if (gameState == sGameStart || !checkBoxPause->Checked) {
		startGame();
	}
	
	while (canSimulateGame) {

		canSimulateGame = true;

		int xc, yc, xb, yb;
		field->getCentre(xc, yc);
		ball->getCoord(xb, yb);

		drawAll();

		switch (gameState) {
		case sGoal:
			::Sleep(1000);
			sound("whistle.wav");
			sound("mencheer.wav");
			if (checkBoxGirls->Checked) {
				gameState = sPause;
				lights[0]->on = lights[1]->on = true;
				sound("successtada.wav");
			}
			else gameState = sRestartGame;

			continue;

		case sRestartGame:
			::Sleep(1000);
			for (int i = 0; i<5; ++i) girl[i]->moveTo(xc - 2 * 6 + i * 6, 4);
			lights[0]->on = lights[1]->on = false;
			sound("whistle.wav");
			gameState = sFirstKick;
			continue;	

		}

		if (field->isGoalLeft(xb, yb))
		{
			scoreR += 1;
			gameState = sGoal;
			ball->moveTo(xc, yc);
			ball->setSpeed(0);
			position1();

			continue;
		}

		if (field->isGoalRight(xb, yb))
		{
			scoreL += 1;
			gameState = sGoal;
			ball->moveTo(xc, yc);
			ball->setSpeed(0);
			position2();
			
			continue;
		}

		Sleep(500 - 50 * slowdown);  //slows down action		

		moveAll();

		energyControl();		
	}
}


void Futbols::MyForm::startGame()
{
	int xc, yc;
	field->getCentre(xc, yc);
	ball->moveTo(xc, yc);
	ball->setSpeed(0);
	assRef1->moveTo(xc, field->getBorderW() / 2 + 2);
	assRef2->moveTo(xc, 3 * field->getBorderW() / 2 + field->getH() - 2);
	for (int i = 0; i < 5; ++i) girl[i]->moveTo(xc - 2 * 6 + i * 6, 4);
	if (rand() % 2) position1(); else position2();
	sound("whistle.wav");
	gameState = sFirstKick;
}

void Futbols::MyForm::drawAll()
{
	//Paštaisīts DOUBLE BUFFER!!
	//Atrisina flickering problēmu :)
	BufferedGraphicsContext ^currentContext;
	BufferedGraphics ^myBuffer;

	currentContext = BufferedGraphicsManager::Current;
	myBuffer = currentContext->Allocate(this->panelField->CreateGraphics(),
		this->panelField->DisplayRectangle);

	//@DELETE?
	//Tā kā zīmēju uz formas, tad "notīru" formu pirms katras zīmēšanas
	/*SolidBrush ^myBrush = gcnew SolidBrush(mainForm->BackColor);
	myBuffer->Graphics->FillRectangle(myBrush, System::Drawing::Rectangle(0, 0, mainForm->Width, mainForm->Height));

	delete myBrush;*/


	field->draw(myBuffer);
	lights[0]->draw(myBuffer);
	lights[1]->draw(myBuffer);
	field->drawLines(myBuffer);
	ball->draw(myBuffer);
	assRef1->draw(myBuffer);
	assRef2->draw(myBuffer);
	referee->draw(myBuffer);
	for (int i = 0; i < Team1.Count; i++)
		Team1[i]->draw(myBuffer);
	for (int i = 0; i < Team2.Count; i++)
		Team2[i]->draw(myBuffer);
	for (int i = 0; i < 5; ++i) girl[i]->draw(myBuffer);

	myBuffer->Render(this->panelField->CreateGraphics());

	//@DELETE?
	//mem leak fix
	delete myBuffer;
	currentContext = nullptr;
	delete currentContext;
}

void Futbols::MyForm::moveAll()
{
	if (gameState == sPause) {
		for (int i = 0; i < 5; ++i) {
			girl[i]->move();
		}
		lights[0]->move();
		lights[1]->move();
		return;
	}

	ball->move();
	assRef1->move();
	assRef2->move();
	referee->move();
	for (int i = 0; i < Team1.Count; i++)
		Team1[i]->move();
	for (int i = 0; i < Team2.Count; i++)
		Team2[i]->move();

}

void Futbols::MyForm::position0()
{
	int y, xc, yc;
	field->getCentre(xc, yc);
	referee->moveTo(xc, yc - 50);
	ball->moveTo(xc, yc - 45);
	assRef1->moveTo(xc - 10, yc - 50);
	assRef2->moveTo(xc + 10, yc - 50);
	y = yc - 10 * Team1.Count / 2;
	for (int i = 0; i < Team1.Count; i++)
	{
		Team1[i]->moveTo(xc - 20, y);
		y += 10;
	}
	y = yc - 10 * Team2.Count / 2;
	for (int i = 0; i < Team2.Count; i++)
	{
		Team2[i]->moveTo(xc + 20, y);
		y += 10;
	}
	for (int i = 0; i<5; ++i) girl[i]->moveTo(xc - 2 * 6 + i * 6, 4);
}

void Futbols::MyForm::position1()
{
	int xc, yc;
	field->getCentre(xc, yc);
	referee->moveTo(xc + 50, yc - 50);

	Team1[0]->moveTo(xc - 5, yc);
	for (int i = 1; i < Team1.Count; i++)
	{
		if (!Team1[i]->inGame) continue;
		if (Team1[i]->type == tGoalkeeper) Team1[i]->moveTo(field->fieldRect->left, yc);
		else Team1[i]->moveTo(xc - (rand()%(field->getW() / 2 - 30)), (rand()%(field->getH() - 20) + 20));
	}

	for (int i = 0; i < Team2.Count; i++)
	{
		if (!Team2[i]->inGame) continue;
		if (Team2[i]->type == tGoalkeeper) Team2[i]->moveTo(field->fieldRect->right, yc);
		else Team2[i]->moveTo(xc + (rand()%(field->getW() / 2 - 30)), (rand()%(field->getH() - 20) + 20));
	}
}

void Futbols::MyForm::position2()
{
	int xc, yc;
	field->getCentre(xc, yc);
	referee->moveTo(xc - 50, yc - 50);
	for (int i = 0; i < Team1.Count; i++)
	{
		if (!Team1[i]->inGame) continue;
		if (Team1[i]->type == tGoalkeeper) Team1[i]->moveTo(field->fieldRect->left, yc);
		else Team1[i]->moveTo(xc - (rand()%(field->getW() / 2 - 30)), (rand()%(field->getH() - 20) + 20));
	}

	Team2[0]->moveTo(xc + 5, yc);
	for (int i = 1; i < Team2.Count; i++)
	{
		if (!Team2[i]->inGame) continue;
		if (Team2[i]->type == tGoalkeeper) Team2[i]->moveTo(field->fieldRect->right, yc);
		else Team2[i]->moveTo(xc + (rand()%(field->getW() / 2 - 30)), (rand()%(field->getH() - 20) + 20));
	}
}

void Futbols::MyForm::sound(String ^ soundFile)
{
	System::Media::SoundPlayer ^simpleSound = gcnew	System::Media::SoundPlayer("sound\\"+soundFile);
	if (checkBoxSound->Checked) {
		simpleSound->Play();
	}		
}
