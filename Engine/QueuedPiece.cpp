#include "QueuedPiece.h"
#include "SpriteEffect.h"

QueuedPiece::QueuedPiece(const Vei2& center)
	:
	center(center),
	innerRect(RectI(center - Vei2(maxSpriteWidth, maxSpriteHeight) / 2, maxSpriteWidth, maxSpriteHeight).GetExpanded(spacing)),
	sprite(maxSpriteWidth, maxSpriteHeight)
{
	bev.SetBaseColor(wallColor);
}

void QueuedPiece::Roll()
{
	nNextPiece = shapeDist(rng);
}

void QueuedPiece::Draw(Graphics& gfx)
{
	sprite = "Sprites\\preview" + std::to_string(nNextPiece) + ".bmp";
	const int x = center.x - sprite.GetWidth() / 2;
	const int y = center.y - sprite.GetHeight() / 2;
	gfx.DrawSprite(x, y, sprite, SpriteEffect::Chroma{});
	bev.DrawBevelFrame(innerRect.GetExpanded(wallWidth), wallWidth / 2, gfx);
}

int QueuedPiece::GetNumber() const
{
	return nNextPiece;
}

RectI QueuedPiece::GetRect() const
{
	return innerRect;
}

int QueuedPiece::GetSpriteWidth()
{
	return maxSpriteWidth;
}

int QueuedPiece::GetSpriteHeight()
{
	return maxSpriteHeight;
}