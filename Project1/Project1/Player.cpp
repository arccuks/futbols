#include <math.h>
#include "Player.h"
#include "Field.h"
#include "Ball.h"
#include "MyForm.h"
#include "Referee.h"
#include "functions.h"
#include <stdlib.h>


Player::Player(int t, int n)
{
	teamNo = t;
	No = n;
	color = t == 1 ? System::Drawing::Color::White : System::Drawing::Color::Red;
	speed = 0;
	sound = 0;
	/*font = new TFont;
	font->Name = "Courier New";
	font->Height = 2 * r + 1;*/
	inGame = true;
}
void Player::draw(System::Drawing::BufferedGraphics ^bf)
{
	Human::draw(bf);
	/*aCanvas->Font = font;
	aCanvas->Brush->Style = bsClear;
	aCanvas->TextOutA(x - r + 1, y - r, IntToStr(No));*/

	switch (sound) {
	case 0: break;
	/*case 1: Futbols::MyForm::mainForm->sound("kick1.wav", SND_ASYNC); break;
	case 2: Futbols::MyForm::mainForm->sound("kick2.wav", SND_ASYNC); break;
	case 3: Futbols::MyForm::mainForm->sound("kick3.wav", SND_ASYNC); break;*/
	};
	if (sound) {
		/*Futbols::MyForm::mainForm->CommentText->Caption = "Team " + IntToStr(teamNo) +
			", No. " + IntToStr(No);*/
	}
	sound = 0;
}
void Player::move()
{
	if (!inGame) { moveToBench(); return; }
	int close = 2 * r + 2;
	int xc, yc, xb, yb, xd, yd;
	Futbols::MyForm::mainForm->field->getCentre(xc, yc);
	Futbols::MyForm::mainForm->ball->getCoord(xb, yb);
	xd = xb; yd = yb;
	bool ownSide = (teamNo == 1 && x < xc) || (teamNo == 2 && x > xc);
	if (ownSide && distance(x, y, xb, yb) > 150) yd = disperse(y, 50);
	energy = energy > 0 ? --energy : 0;
	speed = 5 + (rand() % (energy / 1000));

	dir = direction(x, y, xd, yd);
	dir = disperse(dir, PI / 12);

	x += speed * cos(dir);
	y -= speed * sin(dir);

	avoidCollision();

	if (distance(x, y, xb, yb) < close) kick();
}

void Player::kick()
{
	int xb, yb, xc, yc, xd, yd, speedb;
	Futbols::MyForm::mainForm->ball->getCoord(xb, yb);
	Futbols::MyForm::mainForm->field->getCentre(xc, yc);
	yd = yc;
	if (teamNo == 1)  xd = Futbols::MyForm::mainForm->field->fieldRect->right;
	else            xd = Futbols::MyForm::mainForm->field->fieldRect->left;

	speedb = disperse(20, 10);

	bool ownSide = (teamNo == 1 && x < xc) || (teamNo == 2 && x > xc);

	TPoint p = partner();
	if (p.x >= 0) {  //is partner ?
		int speedp = sqrt(2 * distance(x, y, p.x, p.y) + 0.25) - 0.5;

		//        if (ownSide) {
		//                xd = p.x; yd = p.y; speedb = speedp;
		//        }
		//        else {
		if ((teamNo == 1 && p.x > x + 10) || (teamNo == 2 && p.x < x - 10)) {
			xd = p.x; yd = p.y;
			speedb = speedp + disperse(10, 5);
		}
		//        }

		if (Futbols::MyForm::mainForm->gameState == sFirstKick) {
			xd = p.x; yd = p.y; speedb = speedp + disperse(10, 3);
			Futbols::MyForm::mainForm->gameState = sRunning;
		}
	} //if is partner

	double dirb;
	dirb = direction(xb, yb, xd, yd);
	dirb = disperse(dirb, PI / 24);
	Futbols::MyForm::mainForm->ball->setDir(dirb);
	Futbols::MyForm::mainForm->ball->setSpeed(speedb);
	sound = 2;
}

void Player::avoidCollision()
{
	int lim = 5 * r;
	int nPos = Futbols::MyForm::mainForm->Team1.Count + Futbols::MyForm::mainForm->Team2.Count;
	TPoint* occupiedPos = new TPoint[nPos];

	int j = 0;
	for (int i = 0; i < Futbols::MyForm::mainForm->Team1.Count; i++) {
		if (Futbols::MyForm::mainForm->Team1[i] == this) continue;
		if (!Futbols::MyForm::mainForm->Team1[i]->inGame) continue;
		occupiedPos[j].x = Futbols::MyForm::mainForm->Team1[i]->x;
		occupiedPos[j].y = Futbols::MyForm::mainForm->Team1[i]->y;
		++j;
	}
	for (int i = 0; i < Futbols::MyForm::mainForm->Team2.Count; i++) {
		if (Futbols::MyForm::mainForm->Team2[i] == this) continue;
		if (!Futbols::MyForm::mainForm->Team2[i]->inGame) continue;
		occupiedPos[j].x = Futbols::MyForm::mainForm->Team2[i]->x;
		occupiedPos[j].y = Futbols::MyForm::mainForm->Team2[i]->y;
		++j;
	}
	occupiedPos[j].x = Futbols::MyForm::mainForm->referee->getPos().X;
	occupiedPos[j].y = Futbols::MyForm::mainForm->referee->getPos().Y;

	int attempts = 10000;
	bool tooClose;
	int xa = x, ya = y, speeda = speed;
	double dira = dir;
	int dist;
	nPos = j + 1;
	do {
		for (int i = 0; i < nPos; i++) {
			tooClose = distance(xa, ya, occupiedPos[i].x, occupiedPos[i].y) < lim;
			dist = distance(xa, ya, occupiedPos[i].x, occupiedPos[i].y);
			if (tooClose) {
				--attempts;
				speeda = speeda + dist - lim;//disperse(speed, lim);
				dira = disperse(dir, PI / 12);
				xa = x + speeda * cos(dira);
				ya = y - speeda * sin(dira);
				break;
			}
		}
	} while (tooClose && attempts > 0);
	x = xa;
	y = ya;
	speed = speeda;
	dir = dira;
	delete occupiedPos;
}

void Player::moveToBench()
{
	int xc, yc;
	Futbols::MyForm::mainForm->field->getCentre(xc, yc);
	if (teamNo == 1)
		moveTo(xc - 20 - No * 3 * r,
			Futbols::MyForm::mainForm->field->fieldRect->top - Futbols::MyForm::mainForm->field->getW() + r);
	else
		moveTo(xc + 20 + No * 3 * r,
			Futbols::MyForm::mainForm->field->fieldRect->top - Futbols::MyForm::mainForm->field->getW() + r);
}

TPoint& Player::partner()
{
	int dist[7];
	TPoint p[6];
	int n = 0;

	if (teamNo == 1) {
		for (int i = 0; i < Futbols::MyForm::mainForm->Team1.Count; i++) {
			if (Futbols::MyForm::mainForm->Team1[i] == this) continue;
			if (!Futbols::MyForm::mainForm->Team1[i]->inGame) continue;
			if (Futbols::MyForm::mainForm->Team1[i]->type == tGoalkeeper) continue;
			p[n].x = Futbols::MyForm::mainForm->Team1[i]->x;
			p[n].y = Futbols::MyForm::mainForm->Team1[i]->y;
			++n;
		}
	}
	else {
		for (int i = 0; i < Futbols::MyForm::mainForm->Team2.Count; i++) {
			if (Futbols::MyForm::mainForm->Team2[i] == this) continue;
			if (!Futbols::MyForm::mainForm->Team2[i]->inGame) continue;
			if (Futbols::MyForm::mainForm->Team2[i]->type == tGoalkeeper) continue;
			p[n].x = Futbols::MyForm::mainForm->Team2[i]->x;
			p[n].y = Futbols::MyForm::mainForm->Team2[i]->y;
			++n;
		}
	}
	if (n == 0) { p[0].x = -1; return p[0]; } // no partners
	int d, mindist = distance(x, y, p[0].x, p[0].y);
	int np = 0;
	for (int i = 0; i < n; i++) {
		d = distance(x, y, p[i].x, p[i].y);
		if (d < mindist) {
			mindist = d;
			np = i;
		}
	}
	return p[np];
}
