#include <math.h>
#include "Girl.h"
#include "MyForm.h"
#include "Field.h"
#include "Functions.h"

using namespace System::Drawing;

Girl::Girl()
{
	type = tGirl;
	color = Color::Fuchsia;
	speed = 5;
}

void Girl::move()
{
	int xc, yc;
	Futbols::MyForm::mainForm->field->getCentre(xc, yc);
	if (speed>0 && y<100) speed = 3; else speed = -7;
	y += speed;
	if (y<5) {
		Futbols::MyForm::mainForm->gameState = sRestartGame;
		r = 3;
		speed = 5;
	}
}
void Girl::draw(BufferedGraphics ^bf)
{
	if (Futbols::MyForm::mainForm->gameState == sPause) {
		r = (r == 3) ? 4 : 3;
	}
	Human::draw(bf);

}
