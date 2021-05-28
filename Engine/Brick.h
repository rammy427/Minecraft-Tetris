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
	void Rotate(bool clockwise);
	bool WillCollide(const std::vector<Vei2>& newPositions) const;
private:
	static constexpr int tileAmount = 4;
	std::vector<Vei2> tilePositions;
	Color c;
	Board& brd;
};