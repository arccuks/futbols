#include "Human.h"
#include "Field.h"
#include "MyForm.h"
#include <math.h>
#include "Rect.h"

using namespace System::Drawing;

Human::Human()
{
	r = 3;
	speed = 0;
	energy = 0;
	dir = 0;
}

void Human::moveTo(int xTo, int yTo)
{
	x = xTo; y = yTo;
}

void Human::draw(BufferedGraphics ^myBuffer)
{
	SolidBrush ^myBrush = gcnew SolidBrush(color);
	Pen ^pen = gcnew Pen(color);
	myBuffer->Graphics->FillEllipse(myBrush, Rectangle(x - r, y - r, r*2 , r*2));

	delete myBrush;
	delete pen;
}
