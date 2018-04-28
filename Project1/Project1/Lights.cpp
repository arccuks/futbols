#include "Lights.h"
#include "Field.h"
#include "MyForm.h"
#include "functions.h"
#include <math.h>

Lights::Lights(int xp, int yp, int towerH,
	double foc,
	double dir1, double dir2,
	double tilt1, double tilt2)
{
	x = xp;
	y = yp;
	dir = dir1;
	dirStart = dir1;
	dirEnd = dir2;
	dirSpeed = PI / 64;
	focus = foc;
	towerHeight = towerH;
	tilt = tilt1;
	tiltStart = tilt1;
	tiltEnd = tilt2;
	tiltSpeed = PI / 48;
	on = false;
}

void Lights::draw(System::Drawing::BufferedGraphics ^myBuffer)
{
	if (!on) return;
	
	int dist = towerHeight * tan(tilt);
	int xspot = x + dist * cos(dir);
	int yspot = y - dist * sin(dir);
	int d1 = dist / sin(tilt);

	int spotLength = towerHeight * tan(tilt - focus / 2) - towerHeight * tan(tilt + focus / 2);
	int spotWidth = 2 * d1*tan(focus / 2);

	int x1 = xspot - spotWidth / 2 * sin(dir);
	int y1 = yspot - spotWidth / 2 * cos(dir);
	int x2 = xspot + spotWidth / 2 * sin(dir);
	int y2 = yspot + spotWidth / 2 * cos(dir);

	array<Point>^poly = {Point(x,y),Point(x1,y1),Point(x2,y2) };
	SolidBrush ^brush = gcnew SolidBrush(Color::Yellow);
	myBuffer->Graphics->FillPolygon(brush, poly);

	angellipse(myBuffer, xspot, yspot, spotLength / 2, 0, 2 * PI, dir, spotWidth*1.0 / spotLength);
}

void Lights::move()
{
	if (dir >= dirStart && dirSpeed > 0) dirSpeed = -PI / 64;
	if (dir <= dirEnd && dirSpeed < 0) dirSpeed = PI / 64;
	dir += dirSpeed;
	if (tilt <= tiltStart && tiltSpeed < 0) tiltSpeed = PI / 48;
	if (tilt >= tiltEnd && tiltSpeed > 0) tiltSpeed = -PI / 48;
	tilt += tiltSpeed;
}

