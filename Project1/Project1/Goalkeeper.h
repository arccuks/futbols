#include "Player.h"

#pragma once
ref class Goalkeeper : public Player
{
protected:

public:
	Goalkeeper(int t, int n);
	void move() override;
	void kick() override;
};

