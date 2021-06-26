#include "QueuedBrick.h"
#include "SpriteEffect.h"

QueuedBrick::QueuedBrick(const Vei2& center)
	:
	center(center),
	innerRect(RectI(center - Vei2(maxSpriteWidth, maxSpriteHeight) / 2, maxSpriteWidth, maxSpriteHeight).GetExpanded(spacing)),
	sprite(maxSpriteWidth, maxSpriteHeight)
{
	bev.SetBaseColor(wallColor);
}

void QueuedBrick::Roll()
{
	nNextBrick = shapeDist(rng);
}

void QueuedBrick::Draw(Graphics& gfx)
{
	sprite = "Sprites\\preview" + std::to_string(nNextBrick) + ".bmp";
	const int x = center.x - sprite.GetWidth() / 2;
	const int y = center.y - sprite.GetHeight() / 2;
	gfx.DrawSprite(x, y, sprite, SpriteEffect::Chroma{});
	bev.DrawBevelFrame(innerRect.GetExpanded(wallWidth), wallWidth / 2, gfx);
}

int QueuedBrick::GetNumber() const
{
	return nNextBrick;
}

int QueuedBrick::GetSpriteWidth()
{
	return maxSpriteWidth;
}

int QueuedBrick::GetSpriteHeight()
{
	return maxSpriteHeight;
}