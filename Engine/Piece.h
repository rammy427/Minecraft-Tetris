#pragma once

#include "Board.h"
#include "Keyboard.h"

class Piece
{
public:
	enum class CollisionType
	{
		None,
		Top,
		Side,
		Bottom,
		Tile
	};
public:
	Piece(int shape, const Vei2& gridPos, Board& brd);
	void ProcessTransformations(Keyboard& kbd, unsigned char eventCharCode);
	void UpdateDrop(Keyboard& kbd, float dt);
	void Draw(Graphics& gfx);
	void LockToBoard();
	bool IsLocked() const;
	CollisionType DetectCollision() const;
	static void SpeedUp(int nClearedLines);
	static void ResetSpeed();
	static int GetMaxShapes();
private:
	void TranslateBy(const Vei2& delta);
	void Drop();
	void Rotate(bool clockwise);
private:
	float dropTime;
	float curTime = 0;
	static float fallTime;
	static constexpr float softDropTime = .0625f;
	static constexpr float minFallTime = .0625f;
	static constexpr int tileAmount = 4;
	static constexpr int nShapes = 7;
	std::vector<Vei2> tilePositions;
	Color c;
	Board& brd;
};