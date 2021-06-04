#pragma once

#include "Board.h"
#include "Keyboard.h"

class Brick
{
public:
	Brick(const Vei2& gridPos, Color c, Board& brd);
	void Update(Keyboard& kbd, float dt);
	void Draw(Graphics& gfx);
private:
	void TranslateBy(const Vei2& delta);
	void Drop();
	void Rotate(bool clockwise);
	bool WillCollide() const;
private:
	float dropWaitTime;
	float curTime = .0f;
	static constexpr int tileAmount = 4;
	std::vector<Vei2> tilePositions;
	Color c;
	Board& brd;
};