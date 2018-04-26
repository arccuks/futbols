
#pragma once
ref class Ball
{
private:
	int x;
	int y;
	int r;
	int speed;
	int slowdown;
	double dir;
	System::Drawing::Color color;
public:
	Ball();
	void setSpeed(int s) { speed = s; }
	int getSpeed() { return speed; }
	void setDir(double d) { dir = d; }
	double getDir() { return dir; }
	void draw(System::Drawing::BufferedGraphics ^);
	void move();
	void moveTo(int xTo, int yTo) { x = xTo; y = yTo; }
	void getCoord(int& xb, int& yb) { xb = x; yb = y; }
};
