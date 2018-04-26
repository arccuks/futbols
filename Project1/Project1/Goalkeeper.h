#include "Player.h"
ref class Goalkeeper : public Player
{
protected:

public:
	Goalkeeper(int t, int n);
	void move() override;
	void kick() override;
};

