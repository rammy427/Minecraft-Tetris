#pragma once

#include "Board.h"
#include "Keyboard.h"

class Piece
{
public:
	Piece(int shape, const Vei2& gridPos, Board& brd);
	void ProcessTransformations(Keyboard& kbd, float dt);
	void Draw(Graphics& gfx);
	void BindToBoard();
	bool IsBinded() const;
	bool IsColliding() const;
	static int GetMaxShapes();
private:
	void TranslateBy(const Vei2& delta);
	void Drop();
	void Rotate(bool clockwise);
private:
	float dropWaitTime;
	float curTime = .0f;
	static constexpr int tileAmount = 4;
	static constexpr int nShapes = 7;
	std::vector<Vei2> tilePositions;
	Color c;
	Board& brd;
};