#include <math.h>
#include "HalfBack.h"
#include "Field.h"
#include "Ball.h"
#include "MyForm.h"
#include "Referee.h"
#include "functions.h"


HalfBack::HalfBack(int t, int n) : Player(t, n)
{
	speed = 10;
	area = Futbols::MyForm::mainForm->field->fieldRect;
	type = tHalfBack;
}

void HalfBack::kick()
{
	int xb, yb, xc, yc, xd, yd;
	double dirb, dirdisp = PI / 8;
	int kickSpeed = 20;
	Futbols::MyForm::mainForm->ball->getCoord(xb, yb);
	Futbols::MyForm::mainForm->field->getCentre(xc, yc);
	yd = yb;
	if (teamNo == 1) {
		xd = Futbols::MyForm::mainForm->field->fieldRect->right;
	}
	else {
		xd = Futbols::MyForm::mainForm->field->fieldRect->left;
	}
	if (distance(xb, yb, xd, yd) <= 3 * kickSpeed) {
		yd = yc;
		dirdisp = 0;
	}

	dirb = direction(xb, yb, xd, yd);
	dirb = disperse(dirb, dirdisp);
	Futbols::MyForm::mainForm->ball->setDir(dirb);
	Futbols::MyForm::mainForm->ball->setSpeed(disperse(kickSpeed, kickSpeed / 2));
	sound = 1;
}


