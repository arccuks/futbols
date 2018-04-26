#ifndef HUMAN_H
#define HUMAN_H

using namespace System::Drawing;

enum htype {
	tReferee, tAssReferee,
	tGoalkeeper, tForward,
	tHalfBack, tQuarterBack, tFullBack, tGirl
};

ref class Human
{
protected:
	int x;
	int y;
	int r;
	int speed;
	int energy;
	double dir;
	Color color;
public:
	Human();
	htype type;
	void setSpeed(int s) { speed = s; }
	void setDir(double d) { dir = d; }
	void setEnergy(int e) { energy = e; };
	int getEnergy() { return energy; };
	Point getPos() { return Point(x, y); }
	double getDir() { return dir; }
	int getSpeed() { return speed; }
	virtual void draw(BufferedGraphics ^);
	virtual void move() = 0;
	void moveTo(int x, int y);
};
#endif