#include "human.h"

#pragma once
ref class Girl : public Human
{
public:
	Girl();
	void move() override;
	void draw(BufferedGraphics ^bf) override;
};
