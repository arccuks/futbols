#include "Rect.h"

Rect::Rect(int left, int top, int right, int bottom)
{
	this->left = left;
	this->right = right;
	this->top = top;
	this->bottom = bottom;
}

int Rect::Width()
{
	return right - left;
}

int Rect::Height() 
{
	return bottom - top;
}
