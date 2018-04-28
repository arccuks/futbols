#include "Rect.h"
#pragma once

using namespace System::Drawing;

ref class Field
{
private:
	int h;
	int w;
	int x_c;
	int y_c;
	int borderWidth;
	int goalWidth;
	int goalAreaW;
	int goalAreaH;
	int cenRad = 2;
	int cirCenRad = 45;

public:
	Field();
	Rect ^fieldRect;
	void getCentre(int& x, int& y) { x = x_c; y = y_c; }
	void getGoalArea(int& w, int& h) { w = goalAreaW; h = goalAreaH; }
	int getBorderW() { return borderWidth; }
	int getH() { return h; }
	int getW() { return w; }
	void draw(BufferedGraphics ^);
	void drawLines(BufferedGraphics ^);
	bool isInside(int x, int y);
	bool isOutSide(int x, int y);
	bool isOutLeft(int x, int y);
	bool isOutRight(int x, int y);
	//bool onLeft(int x, int y);
	//bool onRight(int x, int y);
	bool isGoalLeft(int x, int y);
	bool isGoalRight(int x, int y);
	//bool insideLeftGoalArea(int x, int y);
	//bool insideRightGoalArea(int x, int y);
};

