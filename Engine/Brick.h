#pragma once

#include "Board.h"

class Brick
{
public:
	Brick(const Vei2& gridPos, Color c);
	void Draw(Board& brd, Graphics& gfx);
private:
	Vei2 tilePositions[4];
	Color c;
};