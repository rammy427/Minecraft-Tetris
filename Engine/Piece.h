#pragma once

#include "Board.h"
#include "Keyboard.h"

class Piece
{
public:
	Piece(int shape, const Vei2& gridPos, Board& brd);
	void ProcessTransformations(Keyboard& kbd, unsigned char eventCharCode);
	void UpdateDrop(Keyboard& kbd, float dt);
	void Draw(Graphics& gfx);
	void LockToBoard();
	bool IsLocked() const;
	bool IsColliding() const;
	static void UpdateFreeFallTime(int nClearedLines);
	static void ResetFreeFallTime();
	static int GetMaxShapes();
	const std::vector<Vei2>& GetTilePositions() const;
private:
	void TranslateBy(const Vei2& delta);
	void Drop();
	void Rotate(bool clockwise);
	bool TileIsColliding(const Vei2& gridPos) const;
private:
	float speed;
	float curTime = 0.0f;
	static float freeFallTime;
	static constexpr float softDropTime = 0.0625f;
	static constexpr float minSpeed = 0.0625f;
	static constexpr int tileAmount = 4;
	static constexpr int nShapes = 7;
	std::vector<Vei2> tilePositions;
	Color c;
	std::reference_wrapper<Board> brd;
};