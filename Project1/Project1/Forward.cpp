#include <math.h>
#include "Forward.h"
#include "Field.h"
#include "Ball.h"
#include "MyForm.h"
#include "Referee.h"


Forward::Forward(int t, int n) : Player(t, n)
{
	speed = 10;
	area = Futbols::MyForm::mainForm->field->fieldRect;
	type = tForward;
}

/*
void Forward::kick()
{
int xb, yb, xc, yc;
Futbols::MyForm::mainForm->ball->getCoord(xb, yb);
Futbols::MyForm::mainForm->field->getCentre(xc, yc);

if (teamNo==1) xc = Futbols::MyForm::mainForm->field->fieldRect->left;
else  xc = Futbols::MyForm::mainForm->field->fieldRect->right;
int deltaX = xc-xb;
int deltaY = yc-yb;
if (deltaX==0) dir = PI/2;
else dir = atan(double(deltaY)/ deltaX);
if (xc>xb) dir += PI;
dir += 1.0/(random(90)+10);
Futbols::MyForm::mainForm->ball->setDir(dir);
Futbols::MyForm::mainForm->ball->setSpeed(30);
}
*/

