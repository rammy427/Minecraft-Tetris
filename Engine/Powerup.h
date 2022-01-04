#pragma once

#include "Board.h"
#include "Mouse.h"

class Powerup
{
public:
	Powerup(Vei2 rectTopLeft, Board& brd, Mouse& mouse);
	void Update(float dt);
	void Activate();
	void Draw(Graphics& gfx) const;
private:
	Board& brd;
	Mouse& mouse;
	Surface sprite = "Sprites\\tnt.bmp";
	Border border;
	static constexpr int spriteDim = 64;
	static constexpr float coolTime = 5.0f;
	static constexpr int blastRadius = 2;
	float curTime = .0f;
	bool isActive = false;
	bool isOnCooldown = true;
};