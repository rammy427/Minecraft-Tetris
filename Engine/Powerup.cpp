#include "Powerup.h"

Powerup::Powerup(Vei2 rectTopLeft, Board& brd)
	:
	brd(brd),
	border({ rectTopLeft, spriteDim, spriteDim }, 10)
{
}

void Powerup::Draw(Graphics& gfx) const
{
	border.Draw(gfx);
	const Vei2 pos = border.GetInnerBounds().GetCenter() - Vei2(sprite.GetWidth(), sprite.GetHeight()) / 2;
	gfx.DrawSprite(pos.x, pos.y, sprite, SpriteEffect::Copy{});
}