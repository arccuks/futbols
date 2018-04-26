#include <math.h>
#include "Goalkeeper.h"
#include "Field.h"
#include "Ball.h"
#include "MyForm.h"
#include "Referee.h"
#include "functions.h"
#include <stdlib.h>

using namespace System::Drawing;


Goalkeeper::Goalkeeper(int t, int n) : Player(t, n)
{
	speed = 1;
	color = t == 1 ? Color::LightGray : Color::Maroon;
	int xc, yc;
	Futbols::MyForm::mainForm->field->getCentre(xc, yc);
	int gw, gh;
	Futbols::MyForm::mainForm->field->getGoalArea(gw, gh);
	if (teamNo == 1)  area = gcnew Rect(Futbols::MyForm::mainForm->field->fieldRect->left, yc - gh / 2,
		Futbols::MyForm::mainForm->field->fieldRect->left + gw, yc + gh / 2);
	else            area = gcnew Rect(Futbols::MyForm::mainForm->field->fieldRect->right - gw, yc - gh / 2,
		Futbols::MyForm::mainForm->field->fieldRect->right, yc + gh / 2);
	type = tGoalkeeper;
}

void Goalkeeper::move()
{
	int close = 2 * r;
	int xb, yb;
	Futbols::MyForm::mainForm->ball->getCoord(xb, yb);

	speed = 5 + (rand() % 5);          //

	dir = direction(x, y, xb, yb);
	dir = disperse(dir, PI / 8);

	x += speed * cos(dir);
	y -= speed * sin(dir);

	if (x<area->left) x = area->left + 2 * r;
	if (x>area->right) x = area->right - 2 * r;
	if (y<area->top) y = area->top + 2 * r;
	if (y>area->bottom) y = area->bottom - 2 * r;

	avoidCollision();

	if (distance(x, y, xb, yb)<close) kick();
}

void Goalkeeper::kick()
{
	int xb, yb, xc, yc;
	Futbols::MyForm::mainForm->ball->getCoord(xb, yb);
	Futbols::MyForm::mainForm->field->getCentre(xc, yc);

	if (teamNo == 1) xc = Futbols::MyForm::mainForm->field->fieldRect->right;
	else  xc = Futbols::MyForm::mainForm->field->fieldRect->left;
	double dirb = direction(xb, yb, xc, yc);
	dirb = disperse(dirb, PI / 4);
	Futbols::MyForm::mainForm->ball->setDir(dirb);
	Futbols::MyForm::mainForm->ball->setSpeed(40);
	sound = 3;
}



