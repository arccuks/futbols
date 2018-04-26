#include "Player.h"
ref class FullBack : public Player
{
protected:

public:
	FullBack(int t, int n);
	void move() override;
	void kick() override;
};

