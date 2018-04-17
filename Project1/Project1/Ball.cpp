#include "Ball.h"
#include <math.h>
#include "Field.h"
#include "MyForm.h"

using namespace System::Drawing;

Ball::Ball()
{
	r = 3;
	speed = 0;
	slowdown = 1;
	dir = 0;
}

void Ball::draw(BufferedGraphics ^myBuffer)
{
	SolidBrush ^myBrush = gcnew SolidBrush(Color::Yellow);
	myBuffer->Graphics->FillEllipse(myBrush, Rectangle(x - r, y - r, r*2, r*2));

	delete myBrush;
}

void Ball::move()
{
	if (speed == 0) return;
	bool is_in = Project1::MyForm::form1->field->isInside(x, y);

	x += speed * cos(dir);
	y -= speed * sin(dir);
	speed = speed < slowdown ? 0 : speed - slowdown;

	bool will_be_in = Project1::MyForm::form1->field->isInside(x, y);

	if (is_in && !will_be_in) {
		if (Project1::MyForm::form1->field->isOutRight(x, y) ||
			Project1::MyForm::form1->field->isOutLeft(x, y)) {
			
			dir = PI - dir;
		}
		else {
			dir = -dir;
		}
	}
}