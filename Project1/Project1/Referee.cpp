#include "Referee.h"
#include "MyForm.h"
#include "functions.h"
#include <math.h>
#include <stdlib.h>


Referee::Referee()
{
	type = tReferee;
	color = System::Drawing::Color::Yellow;
	speed = 0;
}

void Referee::move()
{
	int xb, yb;
	Futbols::MyForm::mainForm->ball->getCoord(xb, yb);
	dir = direction(x, y, xb, yb);
	dir = disperse(dir, PI / 8);
	if (distance(x, y, xb, yb) < 50) { speed = 3 + (rand() % 3); dir = -dir; }
	else speed = 3 + (rand() % 3);
	x += speed * cos(dir);
	y -= speed * sin(dir);

}
