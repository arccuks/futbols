#include <math.h>
#include "FullBack.h"
#include "Field.h"
#include "Ball.h"
#include "MyForm.h"
#include "Referee.h"
#include "functions.h"
#include <stdlib.h>


FullBack::FullBack(int t, int n) : Player(t, n)
{
	speed = 5;
	int xc, yc;
	Futbols::MyForm::mainForm->field->getCentre(xc, yc);
	if (teamNo == 1)  area = gcnew Rect(Futbols::MyForm::mainForm->field->fieldRect->left, Futbols::MyForm::mainForm->field->fieldRect->top,
		xc, Futbols::MyForm::mainForm->field->fieldRect->bottom);
	else            area = gcnew Rect(xc, Futbols::MyForm::mainForm->field->fieldRect->top,
		Futbols::MyForm::mainForm->field->fieldRect->right, Futbols::MyForm::mainForm->field->fieldRect->bottom);
	type = tFullBack;
}

void FullBack::move()
{
	if (!inGame) {
		moveToBench(); return;
	}
	int close = 2 * r;
	int xb, yb, xc, yc, xd, yd;
	Futbols::MyForm::mainForm->ball->getCoord(xb, yb);
	Futbols::MyForm::mainForm->field->getCentre(xc, yc);

	energy = energy>0 ? --energy : 0;

	//@BUG
	if ((energy / 1000) > 1) {
		speed = 3 + (rand() % (energy / 1000));
	}
	else {
		speed = 3;
	}

	xd = xb; yd = yb;
	if (teamNo == 1 && xb>xc) { xd = disperse(xc / 2, xc / 4); yd = (rand() % (2 * yc)); }
	if (teamNo == 2 && xb<xc) { xd = disperse(xc + xc / 2, xc / 4);  yd = (rand() % (2 * yc)); }

	dir = direction(x, y, xd, yd);
	//dir = disperse(dir, PI/6);

	x += speed * cos(dir);
	y -= speed * sin(dir);
	if (x<area->left) x = area->left + 2 * r;
	if (x>area->right) x = area->right - 2 * r;

	avoidCollision();

	if (distance(x, y, xb, yb)<close) kick();
}

void FullBack::kick()
{
	int xb, yb, xc, yc;
	Futbols::MyForm::mainForm->ball->getCoord(xb, yb);
	Futbols::MyForm::mainForm->field->getCentre(xc, yc);

	if (teamNo == 1) xc = Futbols::MyForm::mainForm->field->fieldRect->right;
	else  xc = Futbols::MyForm::mainForm->field->fieldRect->left;
	double dirb = direction(xb, yb, xc, yc);
	dirb = disperse(dirb, PI / 8);
	Futbols::MyForm::mainForm->ball->setDir(dirb);
	Futbols::MyForm::mainForm->ball->setSpeed(30);
	sound = 1;
}


