#pragma once
#include "Human.h"
ref class Referee : public Human
{
public:
	Referee();
	void move() override;
};
