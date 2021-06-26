#pragma once

#include <random>
#include "Brick.h"

class QueuedBrick
{
public:
	QueuedBrick(const Vei2& center);
	void Roll();
	void Draw(Graphics& gfx);
	int GetNumber() const;
	static int GetSpriteWidth();
	static int GetSpriteHeight();
private:
	Vei2 center;
	RectI innerRect;
	Beveler bev;
	Surface sprite;
	std::mt19937 rng = std::mt19937(std::random_device{}());
	std::uniform_int_distribution<int> shapeDist = std::uniform_int_distribution<int>(0, Brick::GetMaxShapes() - 1);
	int nNextBrick;
	static constexpr int wallWidth = 4;
	static constexpr int spacing = 10;
	static constexpr int maxSpriteWidth = 80;
	static constexpr int maxSpriteHeight = 40;
	static constexpr Color wallColor = { 0, 0, 230 }; // Blue
};