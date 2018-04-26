#include "Field.h"
#include "MyForm.h"
#include "Rect.h"

using namespace System::Drawing;

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
	SolidBrush ^myBrush = gcnew SolidBrush(Color::Green);
	myBuffer->Graphics->FillRectangle(myBrush, Rectangle(fieldRect->left, fieldRect->top, fieldRect->right, fieldRect->bottom));
	delete myBrush;
	

	myBrush = gcnew SolidBrush(Color::Black);
	myBuffer->Graphics->FillRectangle(myBrush, Rectangle(0, 0, Futbols::MyForm::mainForm->FieldImage->Width, Futbols::MyForm::mainForm->FieldImage->Height));
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

	
	myBuffer->Graphics->FillRectangle(myBrush, Rectangle(0, y_c - goalWidth / 2, fieldRect->left, y_c + goalWidth / 2));
	myBuffer->Graphics->FillRectangle(myBrush, Rectangle(fieldRect->right, y_c - goalWidth / 2, fieldRect->right + borderWidth, y_c + goalWidth / 2));
	myBuffer->Graphics->DrawRectangle(pen, 0, y_c - goalWidth / 2, fieldRect->left, y_c + goalWidth / 2);
	myBuffer->Graphics->DrawRectangle(pen, fieldRect->right, y_c - goalWidth / 2, fieldRect->right + borderWidth, y_c + goalWidth / 2);
	myBuffer->Graphics->DrawRectangle(pen, fieldRect->left, y_c - goalAreaH / 2, fieldRect->left + goalAreaW, y_c + goalAreaH / 2);
	myBuffer->Graphics->DrawRectangle(pen, fieldRect->right - goalAreaW, y_c - goalAreaH / 2, fieldRect->right, y_c + goalAreaH / 2);

	delete myBrush;
	delete pen;

	/*TColor currPenColor = aCanvas->Pen->Color;
	TColor currBrushColor = aCanvas->Brush->Color;
	TBrushStyle currBrushStyle = aCanvas->Brush->Style;
	aCanvas->Brush->Style = bsClear;
	aCanvas->Pen->Color = clWhite;
	aCanvas->Rectangle(*fieldRect);
	aCanvas->MoveTo(x_c, fieldRect->bottom - 1);
	aCanvas->LineTo(x_c, fieldRect->top);
	aCanvas->Ellipse(x_c - 45, y_c - 45, x_c + 45, y_c + 45);
	aCanvas->Brush->Color = clWhite;
	aCanvas->Ellipse(x_c - 2, y_c - 2, x_c + 2, y_c + 2);


	aCanvas->Brush->Color = clWhite;
	aCanvas->Brush->Style = bsDiagCross;
	aCanvas->FillRect(Rect(0, y_c - goalWidth / 2, fieldRect->left, y_c + goalWidth / 2));
	aCanvas->FillRect(Rect(fieldRect->right, y_c - goalWidth / 2, fieldRect->right + borderWidth, y_c + goalWidth / 2));
	aCanvas->Rectangle(0, y_c - goalWidth / 2, fieldRect->left, y_c + goalWidth / 2);
	aCanvas->Rectangle(fieldRect->right, y_c - goalWidth / 2, fieldRect->right + borderWidth, y_c + goalWidth / 2);
	aCanvas->Brush->Style = bsClear;
	aCanvas->Rectangle(fieldRect->left, y_c - goalAreaH / 2, fieldRect->left + goalAreaW, y_c + goalAreaH / 2);
	aCanvas->Rectangle(fieldRect->right - goalAreaW, y_c - goalAreaH / 2, fieldRect->right, y_c + goalAreaH / 2);

	aCanvas->Brush->Style = currBrushStyle;
	aCanvas->Pen->Color = currPenColor;
	aCanvas->Brush->Color = currBrushColor;*/
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