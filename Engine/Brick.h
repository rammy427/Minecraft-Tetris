#pragma once

#include "Board.h"
#include "Keyboard.h"

class Brick
{
public:
	Brick(const Vei2& gridPos, Color c, Board& brd);
	void Update(Keyboard& kbd);
	void Draw(Graphics& gfx);
private:
	void TranslateBy(const Vei2& delta);
	bool IsColliding(const Vei2& delta) const;
private:
	Vei2 tilePositions[4];
	Color c;
	Board& brd;
};