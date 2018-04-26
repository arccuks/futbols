#pragma once
#include "Player.h"
ref class HalfBack : public Player
{
public:
	HalfBack(int t, int n);
	void kick() override;
};

