#pragma once
class Ball
{
private:
	int x;
	int y;
	int r;
	int speed;
	int slowdown;
	double dir;
public:
	Ball();
	void setSpeed(int s) { speed = s; }
	int getSpeed() { return speed; }
	void setDir(double d) { dir = d; }
	double getDir() { return dir; }
	void draw();
	void move();
	void moveTo(int xTo, int yTo) { x = xTo; y = yTo; }
	void getCoord(int& xb, int& yb) { xb = x; yb = y; }
};

