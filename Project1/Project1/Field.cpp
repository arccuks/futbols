#include "Field.h"
#include "MyForm.h"
#include "Rect.h"

using namespace System::Drawing;
using namespace System::Drawing::Drawing2D;

Field::Field()
{
	borderWidth = Futbols::MyForm::mainForm->FieldImage->Height / 20;

	fieldRect = gcnew Rect(borderWidth, borderWidth,
		Futbols::MyForm::mainForm->FieldImage->Width - borderWidth,
		Futbols::MyForm::mainForm->FieldImage->Height - borderWidth);
	h = fieldRect->Height();
	w = fieldRect->Width();

	goalWidth = h / 8;
	goalAreaH = goalWidth * 2;
	goalAreaW = goalWidth * 0.75;

	x_c = w / 2 + borderWidth;
	y_c = h / 2 + borderWidth;
}

void Field::draw(BufferedGraphics ^myBuffer)
{
	SolidBrush ^myBrush = gcnew SolidBrush(Color::Black);
	myBuffer->Graphics->FillRectangle(myBrush, Rectangle(0, 0, Futbols::MyForm::mainForm->FieldImage->Width, Futbols::MyForm::mainForm->FieldImage->Height));

	myBrush = gcnew SolidBrush(Color::Green);
	myBuffer->Graphics->FillRectangle(myBrush, Rectangle(fieldRect->left, fieldRect->top, fieldRect->right-borderWidth, fieldRect->bottom- borderWidth));

	drawLines(myBuffer);
}

void Field::drawLines(BufferedGraphics ^myBuffer)
{
	SolidBrush ^myBrush = gcnew SolidBrush(Color::White);
	Pen ^pen = gcnew Pen(System::Drawing::Color::White);

	//speles laukuma baltas malas
	myBuffer->Graphics->DrawRectangle(pen, Rectangle(fieldRect->left, fieldRect->top, fieldRect->right- borderWidth, fieldRect->bottom- borderWidth));
	
	//centra rinkis, centra truksais rinkis, centra linija
	myBuffer->Graphics->DrawLine(pen, x_c, fieldRect->bottom - 1, x_c, fieldRect->top);
	myBuffer->Graphics->DrawEllipse(pen, Rectangle(x_c - cirCenRad, y_c - cirCenRad, cirCenRad*2, cirCenRad*2));
	myBuffer->Graphics->FillEllipse(myBrush, Rectangle(x_c - cenRad, y_c - cenRad, cenRad*2, cenRad*2));

	//sis vel nav skatits
	myBrush = gcnew SolidBrush(Color::White);
	HatchBrush ^hBrush = gcnew HatchBrush(HatchStyle::DiagonalCross, Color::White, Color::Black);

	//Vartu rezgis abam pusem
	myBuffer->Graphics->FillRectangle(hBrush, Rectangle(0, y_c - goalWidth / 2, borderWidth, goalWidth));
	myBuffer->Graphics->FillRectangle(hBrush, Rectangle(fieldRect->right, y_c - goalWidth / 2, borderWidth, goalWidth));
	myBuffer->Graphics->DrawRectangle(pen, Rectangle(0, y_c - goalWidth / 2, borderWidth, goalWidth));
	myBuffer->Graphics->DrawRectangle(pen, Rectangle(fieldRect->right, y_c - goalWidth / 2, borderWidth, goalWidth));
	myBuffer->Graphics->DrawRectangle(pen, fieldRect->left, y_c - goalAreaH / 2, goalAreaW, goalAreaH);
	myBuffer->Graphics->DrawRectangle(pen, fieldRect->right - goalAreaW, y_c - goalAreaH / 2, goalAreaW, goalAreaH);

	delete myBrush;
	delete hBrush;
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

bool Field::isGoalRight(int x, int y)
{
	return isOutRight(x, y) && (y > (y_c - goalWidth / 2)) && (y < (y_c + goalWidth / 2));
}

bool Field::isGoalLeft(int x, int y)
{
	return isOutLeft(x, y) && (y >(y_c - goalWidth / 2)) && (y < (y_c + goalWidth / 2));
}