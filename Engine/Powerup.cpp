#include "Powerup.h"

Powerup::Powerup(Vei2 rectTopLeft, Board& brd, Mouse& mouse)
	:
	brd(brd),
	mouse(mouse),
	border({ rectTopLeft, spriteDim, spriteDim }, 10)
{
}

void Powerup::Update(float dt)
{
	if (!isActive)
	{
		if (isOnCooldown)
		{
			curTime += dt;
			if (curTime >= coolTime)
			{
				curTime = .0f;
				isOnCooldown = false;
			}
		}
	}
	else
	{
		while (!mouse.IsEmpty())
		{
			const Mouse::Event e = mouse.Read();
			if (e.GetType() == Mouse::Event::Type::LPress)
			{
				const Vei2 mousePos = e.GetPos();
				if (brd.GetRect().Contains(mousePos))
				{
					const Vei2 center = brd.ScreenToGrid(mousePos);
					const int left = center.x - blastRadius;
					const int right = center.x + blastRadius;
					const int top = center.y - blastRadius;
					const int bottom = center.y + blastRadius;
					for (Vei2 gridPos = { left, top }; gridPos.y <= bottom; gridPos.y++)
					{
						for (gridPos.x = left; gridPos.x <= right; gridPos.x++)
						{
							if (brd.IsInsideBoard(gridPos) && (gridPos - center).GetLengthSq() <= blastRadius * blastRadius)
							{
								brd.TileAt(gridPos).Kill();
							}
						}
					}
					isActive = false;
					isOnCooldown = true;
				}
			}
		}
	}
}

void Powerup::Activate()
{
	if (!isOnCooldown)
	{
		isActive = true;
	}
}

void Powerup::Draw(Graphics& gfx) const
{
	border.Draw(gfx);
	const Vei2 pos = border.GetInnerBounds().GetCenter() - Vei2(sprite.GetWidth(), sprite.GetHeight()) / 2;
	gfx.DrawSprite(pos.x, pos.y, sprite, SpriteEffect::Copy{});
}