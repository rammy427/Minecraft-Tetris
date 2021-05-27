#include "Brick.h"

Brick::Brick(const Vei2& gridPos, Color c, Board& brd)
	:
	c(c),
	brd(brd)
{
	tilePositions[0] = gridPos;
	tilePositions[1] = { gridPos.x - 1, gridPos.y };
	tilePositions[2] = { gridPos.x + 1, gridPos.y };
	tilePositions[3] = { gridPos.x, gridPos.y - 1 };
}

void Brick::Update(Keyboard& kbd)
{
	if (kbd.KeyIsPressed(VK_LEFT))
	{
		TranslateBy({ -1,0 });
	}
	else if (kbd.KeyIsPressed(VK_RIGHT))
	{
		TranslateBy({ 1,0 });
	}
	if (kbd.KeyIsPressed(VK_UP))
	{
		TranslateBy({ 0,-1 });
	}
	else if (kbd.KeyIsPressed(VK_DOWN))
	{
		TranslateBy({ 0,1 });
	}
}

void Brick::Draw(Graphics& gfx)
{
	for (const Vei2& pos : tilePositions)
	{
		brd.DrawGhostCell(pos, c, gfx);
	}
}

void Brick::TranslateBy(const Vei2& delta)
{
	if (!IsColliding(delta))
	{
		for (Vei2& pos : tilePositions)
		{
			pos += delta;
		}
	}
}

bool Brick::IsColliding(const Vei2& delta) const
{
	for (const Vei2& pos : tilePositions)
	{
		const Vei2 newPos = pos + delta;
		if (newPos.x < 0 ||
			newPos.x >= brd.GetWidth() ||
			newPos.y < 0 ||
			newPos.y >= brd.GetHeight())
		{
			return true;
		}
	}
	return false;
}