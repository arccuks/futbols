#include <math.h>
#include "AssReferee.h"
#include "Ball.h"
#include "MyForm.h"
#include <stdlib.h>

using namespace System::Drawing;

AssReferee::AssReferee()
{
	type = tAssReferee;
	color = Color::Lime;
	speed = 2;
}

void AssReferee::move()
{
	int xb, yb;
	Futbols::MyForm::mainForm->ball->getCoord(xb, yb);
	
	int delta = 0;

	//@BUG
	if (this->x != xb) {
		delta = rand() % abs(xb - (this->x));
	}
	
	
	delta = delta>5 ? 5 : delta;
	if (x < xb) x += speed + delta;
	if (x > xb) x -= speed + delta;
}
