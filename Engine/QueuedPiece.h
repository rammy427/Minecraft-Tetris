#pragma once

#include <random>
#include "Piece.h"

class QueuedPiece
{
public:
	QueuedPiece(const Vei2& center);
	void Roll();
	void Draw(Graphics& gfx);
	int GetNumber() const;
	RectI GetRect() const;
	static int GetSpriteWidth();
	static int GetSpriteHeight();
private:
	Vei2 center;
	RectI innerRect;
	Beveler bev;
	Surface sprite;
	std::mt19937 rng = std::mt19937(std::random_device{}());
	std::uniform_int_distribution<int> shapeDist = std::uniform_int_distribution<int>(0, Piece::GetMaxShapes() - 1);
	int nNextPiece = 0;
	static constexpr int wallWidth = 4;
	static constexpr int spacing = 10;
	static constexpr int maxSpriteWidth = 80;
	static constexpr int maxSpriteHeight = 40;
	static constexpr Color wallColor = { 0, 0, 230 }; // Blue
};