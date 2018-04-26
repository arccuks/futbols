
#pragma once
ref class Lights
{
private:

	int x;
	int y;
	double dir;
	double dirStart, dirEnd;
	double dirSpeed;
	double focus;
	int towerHeight;
	double tilt;
	double tiltStart, tiltEnd;
	double tiltSpeed;

public:
	bool on;
	Lights(int xp, int yp, int towerH,
		double foc,
		double dir1, double dir2,
		double tilt1, double tilt2);
	void draw(System::Drawing::BufferedGraphics ^);
	void move();
	void moveTo(int xTo, int yTo) { x = xTo; y = yTo; }
};
