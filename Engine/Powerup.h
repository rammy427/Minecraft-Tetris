#pragma once

#include "Board.h"

class Powerup
{
public:
	Powerup(Vei2 rectTopLeft, Board& brd);
	void Draw(Graphics& gfx) const;
private:
	Board& brd;
	Surface sprite = "Sprites\\tnt.bmp";
	Border border;
	static constexpr int spriteDim = 64;
	static constexpr float cooldown = 1.0f;
	float curTime = .0f;
	bool isBeingUsed = false;
};