#pragma once
#include "Human.h"
#include "Rect.h"
#include "TPoint.h"

ref class Player : public Human
{
protected:
	int teamNo;
	int No;
	Rect ^area;
	System::Drawing::Font ^font;
	int sound;

public:
	Player(int t, int n);
	virtual void move() override;
	virtual void draw(System::Drawing::BufferedGraphics ^) override;
	virtual void kick();
	void avoidCollision();
	bool inGame;
	void moveToBench();
	TPoint& partner();
};

