#include "Item.h"
#include "Score.h"

Item::Item(Vei2 rectTopLeft, Board& brd, Mouse& mouse, Piece& piece, SoundEffect& sound, const std::string& spritename)
	:
	brd(brd),
	mouse(mouse),
	piece(piece),
	border({ rectTopLeft, spriteDim, spriteDim }, 10),
	sound(sound),
	sprite(spritename)
{
}

void Item::Update(float dt)
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
		ProcessUsage();
	}
}

void Item::Activate()
{
	if (!isOnCooldown)
	{
		mouse.Flush();
		isActive = true;
		Score::Add(100);
	}
}

void Item::EndUse()
{
	if (isActive)
	{
		hasEnded = true;
	}
}

void Item::Draw(const Font& font, Graphics& gfx) const
{
	border.Draw(gfx);
	const Vei2 pos = border.GetInnerBounds().GetCenter() - Vei2(sprite.GetWidth(), sprite.GetHeight()) / 2;
	gfx.DrawSprite(pos.x, pos.y, sprite, SpriteEffect::Chroma{});
	if (isOnCooldown)
	{
		const Vei2 topLeft = { border.GetInnerBounds().left, border.GetInnerBounds().top };
		int width = int(border.GetInnerBounds().GetWidth() * (1 - curTime / coolTime));
		gfx.DrawRect({ topLeft, width, border.GetInnerBounds().GetHeight() }, Colors::Red, true);
	}
	else if (isActive)
	{
		const Vei2 topLeft = { border.GetInnerBounds().left, border.GetInnerBounds().top };
		gfx.DrawRect({ topLeft, border.GetInnerBounds().GetWidth(), border.GetInnerBounds().GetHeight() }, Border::GetColor(), true);
	}
	TextManager::DrawItemText(font, border.GetInnerBounds(), gfx);
}

bool Item::HasEnded() const
{
	return hasEnded;
}

Bomb::Bomb(Vei2 rectTopLeft, Board& brd, Mouse& mouse, Piece& piece, SoundEffect& sound)
	:
	Item(rectTopLeft, brd, mouse, piece, sound, "Sprites\\tnt.bmp")
{
}

void Bomb::ProcessUsage()
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
				sound.Play(rng);
				EndUse();
			}
		}
	}
}

Sand::Sand(Vei2 rectTopLeft, Board& brd, Mouse& mouse, Piece& piece, SoundEffect& sound)
	:
	Item(rectTopLeft, brd, mouse, piece, sound, "Sprites\\sand.bmp")
{
}

void Sand::ProcessUsage()
{
	for (int n = 0; n < nBlocks; n++)
	{
		const std::vector<Vei2>& positions = piece.GetTilePositions();
		const auto pred = [](const Vei2& lhs, const Vei2& rhs) { return lhs.x < rhs.x; };
		const auto limits = std::minmax_element(positions.begin(), positions.end(), pred);
		const int leftLim = limits.first->x;
		const int rightLim = limits.second->x;

		int rand_x;
		do
		{
			rand_x = xDist(rng);
		} while ((rand_x >= leftLim && rand_x <= rightLim) || brd.TileAt({ rand_x,0 }).IsAlive());

		int next_y = 0;
		while (next_y < brd.GetHeight() && !brd.TileAt({ rand_x, next_y }).IsAlive())
		{
			next_y++;
		}

		const Vei2 gridPos = { rand_x,next_y - 1 };
		brd.TileAt(gridPos).SetColor(c);
		brd.TileAt(gridPos).Set();
	}
	EndUse();
}

Potion::Potion(Vei2 rectTopLeft, Board& brd, Mouse& mouse, Piece& piece, SoundEffect& sound)
	:
	Item(rectTopLeft, brd, mouse, piece, sound, "Sprites\\potion.bmp")
{
}

void Potion::ProcessUsage()
{
	const bool isSlowingDown = bool(fallDist(rng));
	Piece::InitPotionEffect(isSlowingDown);
	sound.Play(rng);
	EndUse();
}

Pickaxe::Pickaxe(Vei2 rectTopLeft, Board& brd, Mouse& mouse, Piece& piece, SoundEffect& sound)
	:
	Item(rectTopLeft, brd, mouse, piece, sound, "Sprites\\pickaxe.bmp")
{
}

void Pickaxe::ProcessUsage()
{
	while (!mouse.IsEmpty())
	{
		const Mouse::Event e = mouse.Read();
		if (e.GetType() == Mouse::Event::Type::LPress)
		{
			const Vei2 mousePos = e.GetPos();
			if (brd.GetRect().Contains(mousePos))
			{
				auto& tile = brd.TileAt(brd.ScreenToGrid(mousePos));
				if (tile.IsAlive())
				{
					tile.Kill();
					nTiles++;
				}
			}
		}
	}

	if (nTiles >= nMaxTiles)
	{
		EndUse();
	}
}

Star::Star(Vei2 rectTopLeft, Board& brd, Mouse& mouse, Piece& piece, SoundEffect& sound)
	:
	Item(rectTopLeft, brd, mouse, piece, sound, "Sprites\\star.bmp")
{
}

void Star::ProcessUsage()
{
	brd.Reset(false);
	EndUse();
}