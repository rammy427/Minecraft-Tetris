#pragma once

#include "Board.h"
#include "Keyboard.h"

class Brick
{
public:
	Brick(const Vei2& gridPos, Color c);
	void Update(Keyboard& kbd);
	void Draw(Board& brd, Graphics& gfx);
private:
	void TranslateBy(const Vei2& delta);
private:
	Vei2 tilePositions[4];
	Color c;
};