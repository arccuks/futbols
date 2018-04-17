#include "Rect.h"
#pragma once
class Field
{
private:
	int h;
	int w;
	int x_c;
	int y_c;
public:
	Field(int, int);
	Rect *fieldRect;
	void getCentre(int& x, int& y) { x = x_c; y = y_c; }
	int getH() { return h; }
	int getW() { return w; }
	void draw();
	void drawLines();
	bool isInside(int x, int y);
	bool isOutSide(int x, int y);
	bool isOutLeft(int x, int y);
	bool isOutRight(int x, int y);
};

