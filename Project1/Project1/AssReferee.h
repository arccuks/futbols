#include "human.h"

#pragma once
ref class AssReferee : public Human
{
public:
	AssReferee();
	void move() override;
};
