#pragma once

#include "Board.h"
#include "Keyboard.h"

class Piece
{
public:
	enum class Effect
	{
		None,
		Slowdown,
		Speedup
	};
public:
	Piece(int shape, const Vei2& gridPos, Board& brd);
	void ProcessTransformations(Keyboard& kbd, unsigned char eventCharCode);
	void UpdateDrop(Keyboard& kbd, float dt);
	void Draw(Graphics& gfx);
	void LockToBoard();
	bool IsLocked() const;
	bool IsColliding() const;
	static void InitPotionEffect(bool isSpeedingUp);
	static void UpdateFreeFallTime();
	static void ResetStaticData(float startingSpeed = 1.0f);
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
	static Effect effect;
	static float curEffectTime;
	static constexpr float potionEffectDuration = 10.0f;
	static constexpr float softDropTime = 0.0625f;
	static constexpr float minSpeed = 0.0625f;
	static constexpr float maxSpeed = 2.0f;
	static constexpr float speedStep = 0.009375f;
	static constexpr int tileAmount = 4;
	static constexpr int nShapes = 7;
	std::vector<Vei2> tilePositions;
	Color c;
	std::reference_wrapper<Board> brd;
};