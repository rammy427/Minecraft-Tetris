#pragma once

#include "Board.h"
#include "Mouse.h"
#include "TextManager.h"

class Powerup
{
public:
	Powerup(Vei2 rectTopLeft, Board& brd, Mouse& mouse, const std::string& spritename);
	void Update(float dt);
	void Activate();
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
	static constexpr int blastRadius = 2;
	float curTime = .0f;
	bool isActive = false;
	bool isOnCooldown = true;
};

class Bomb : public Powerup
{
public:
	Bomb(Vei2 rectTopLeft, Board& brd, Mouse& mouse);
private:
	void ProcessUsage() override;
};