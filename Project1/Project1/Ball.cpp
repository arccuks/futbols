#include "Ball.h"
#include <math.h>
#include "Field.h"
#include "MyForm.h"

Ball::Ball()
{
	r = 2;
	speed = 0;
	slowdown = 3;
	dir = 0;
	color = Color::Aqua;
}

void Ball::draw(BufferedGraphics ^myBuffer)
{
	SolidBrush ^myBrush = gcnew SolidBrush(color);
	myBuffer->Graphics->FillEllipse(myBrush, Rectangle(x - r, y - r, r*2, r*2));

	delete myBrush;
}

void Ball::move()
{
	if (speed == 0) return;
	bool is_in = Futbols::MyForm::mainForm->field->isInside(x, y);
	x += speed * cos(dir);
	y -= speed * sin(dir);
	bool willbe_in = Futbols::MyForm::mainForm->field->isInside(x, y);

	speed = speed<slowdown ? 0 : speed - slowdown;

	int xc, yc, wg, hg;
	Futbols::MyForm::mainForm->field->getCentre(xc, yc);
	Futbols::MyForm::mainForm->field->getGoalArea(wg, hg);

	if (Futbols::MyForm::mainForm->field->isGoalLeft(x, y)) { x = Futbols::MyForm::mainForm->field->fieldRect->left - 4 * r; return; }
	if (Futbols::MyForm::mainForm->field->isGoalRight(x, y)) { x = Futbols::MyForm::mainForm->field->fieldRect->right + 4 * r; return; }
	if (is_in && !willbe_in) {
		if (Futbols::MyForm::mainForm->field->isOutSide(x, y)) dir = 2 * PI - dir;
		if (Futbols::MyForm::mainForm->field->isOutRight(x, y)) {
			moveTo(Futbols::MyForm::mainForm->field->fieldRect->right - wg, yc);
			speed = 0;
		}
		if (Futbols::MyForm::mainForm->field->isOutLeft(x, y)) {
			moveTo(Futbols::MyForm::mainForm->field->fieldRect->left + wg, yc);
			speed = 0;
		}
	}
}