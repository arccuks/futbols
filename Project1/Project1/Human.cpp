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
	//aCanvas->Ellipse(x - r, y - r, x + r, y + r);
	myBuffer->Graphics->DrawEllipse(pen, Rectangle(x - r, y - r, x + r , y + r)); // *2 pedejos 2 radiussus 

	delete myBrush;
	delete pen;
}
