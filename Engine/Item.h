#pragma once

#include <random>
#include "Piece.h"
#include "Mouse.h"
#include "TextManager.h"

class Item
{
public:
	Item(Vei2 rectTopLeft, Board& brd, Mouse& mouse, const std::string& spritename);
	void Update(float dt);
	void Activate();
	void Reset();
	void Draw(const Font& font, Graphics& gfx) const;
private:
	virtual void ProcessUsage() = 0;
protected:
	Board& brd;
	Mouse& mouse;
	Surface sprite;
	Border border;
	static constexpr int spriteDim = 64;
	static constexpr float coolTime = 5.0f;
	float curTime = .0f;
	bool isActive = false;
	bool isOnCooldown = true;
};

class Bomb : public Item
{
public:
	Bomb(Vei2 rectTopLeft, Board& brd, Mouse& mouse);
private:
	void ProcessUsage() override;
private:
	static constexpr int blastRadius = 2;
};

class Sand : public Item
{
public:
	Sand(Vei2 rectTopLeft, Board& brd, Mouse& mouse, const Piece& piece);
private:
	void ProcessUsage() override;
private:
	const Piece& piece;
	static constexpr int nBlocks = 10;
	static constexpr Color c = { 230, 206, 184 }; // Apricot
	std::mt19937 rng = std::mt19937(std::random_device{}());
	std::uniform_int_distribution<int> xDist = std::uniform_int_distribution<int>(0, brd.GetWidth() - 1);
};