#include "Field.h"
#include "MyForm.h"
#include "Rect.h"

using namespace System::Drawing;

Field::Field(int width, int height)
{
	fieldRect = new Rect(0, 0, width, height);
	h = height;
	w = width;
	x_c = w / 2;
	y_c = h / 2;
}

void Field::draw(BufferedGraphics ^myBuffer)
{
	SolidBrush ^myBrush = gcnew SolidBrush(Color::Green);
	myBuffer->Graphics->FillRectangle(myBrush, Rectangle(fieldRect->left, fieldRect->top, fieldRect->right, fieldRect->bottom));
	delete myBrush;
	drawLines(myBuffer);
}

void Field::drawLines(BufferedGraphics ^myBuffer)
{
	SolidBrush ^myBrush = gcnew SolidBrush(Color::White);
	Pen ^pen = gcnew Pen(System::Drawing::Color::White);
	
	myBuffer->Graphics->DrawLine(pen, x_c, fieldRect->bottom - 1, x_c, fieldRect->top);
	myBuffer->Graphics->DrawEllipse(pen, Rectangle(x_c - 25, y_c - 25, 50, 50));
	myBuffer->Graphics->FillEllipse(myBrush, Rectangle(x_c - 4, y_c - 4, 8, 8));

	delete myBrush;
	delete pen;
}

bool Field::isInside(int x, int y)
{
	return x >= fieldRect->left && x <= fieldRect->right && y >= fieldRect->top && y <= fieldRect->bottom;
}

bool Field::isOutSide(int x, int y)
{
	return y < fieldRect->top || y > fieldRect->bottom;
}

bool Field::isOutLeft(int x, int y)
{
	return x < fieldRect->left;
}

bool Field::isOutRight(int x, int y)
{
	return x > fieldRect->right;
}