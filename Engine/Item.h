#pragma once

#include <random>
#include "Piece.h"
#include "Mouse.h"
#include "TextManager.h"
#include "SoundEffect.h"

class Item
{
public:
	Item(Vei2 rectTopLeft, Board& brd, Mouse& mouse, Piece& piece, SoundEffect& effectSnd, const std::string& spritename);
	virtual ~Item() = default;
	void Update(float dt);
	void Activate();
	virtual void EndUse();
	void Draw(const Font& font, Graphics& gfx) const;
	bool HasEnded() const;
private:
	virtual void ProcessUsage() = 0;
protected:
	Board& brd;
	Mouse& mouse;
	Piece& piece;
	Surface sprite;
	Border border;
	SoundEffect& effectSnd;
	std::mt19937 rng = std::mt19937(std::random_device{}());
	static constexpr int spriteDim = 64;
	static constexpr float coolTime = 1.0f;
	// Change cooldown time to 60 after all SFX are tested.
	float curTime = .0f;
	bool isActive = false;
	bool isOnCooldown = true;
	bool hasEnded = false;
};

class Bomb : public Item
{
public:
	Bomb(Vei2 rectTopLeft, Board& brd, Mouse& mouse, Piece& piece, SoundEffect& effectSnd);
private:
	void ProcessUsage() override;
private:
	static constexpr int blastRadius = 2;
};

class Sand : public Item
{
public:
	Sand(Vei2 rectTopLeft, Board& brd, Mouse& mouse, Piece& piece, SoundEffect& effectSnd);
private:
	void ProcessUsage() override;
private:
	static constexpr int nBlocks = 10;
	static constexpr Color c = { 230, 206, 184 }; // Apricot
	std::uniform_int_distribution<int> xDist = std::uniform_int_distribution<int>(0, brd.GetWidth() - 1);
};

class Potion : public Item
{
public:
	Potion(Vei2 rectTopLeft, Board& brd, Mouse& mouse, Piece& piece, SoundEffect& effectSnd);
private:
	void ProcessUsage() override;
private:
	std::uniform_int_distribution<int> fallDist = std::uniform_int_distribution<int>(0, 1);
};

class Pickaxe : public Item
{
public:
	Pickaxe(Vei2 rectTopLeft, Board& brd, Mouse& mouse, Piece& piece, SoundEffect& effectSnd);
private:
	void ProcessUsage() override;
private:
	int nTiles = 0;
	static constexpr int nMaxTiles = 10;
};

class Star : public Item
{
public:
	Star(Vei2 rectTopLeft, Board& brd, Mouse& mouse, Piece& piece, SoundEffect& effectSnd);
private:
	void ProcessUsage() override;
};