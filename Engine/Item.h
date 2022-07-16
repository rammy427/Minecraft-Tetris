#pragma once

#include <random>
#include "Piece.h"
#include "Mouse.h"
#include "TextManager.h"

class Item
{
public:
	Item(Vei2 rectTopLeft, Board& brd, Mouse& mouse, const std::string& spritename);
	virtual ~Item() = default;
	void Update(float dt);
	void Activate();
	virtual void Reset();
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

class Potion : public Item
{
public:
	Potion(Vei2 rectTopLeft, Board& brd, Mouse& mouse);
private:
	void ProcessUsage() override;
private:
	std::mt19937 rng = std::mt19937(std::random_device{}());
	std::uniform_int_distribution<int> fallDist = std::uniform_int_distribution<int>(0, 1);
};

class Pickaxe : public Item
{
public:
	Pickaxe(Vei2 rectTopLeft, Board& brd, Mouse& mouse);
	void Reset() override;
private:
	void ProcessUsage() override;
private:
	int nTiles = 0;
	static constexpr int nMaxTiles = 10;
};