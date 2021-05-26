#include "Brick.h"

Brick::Brick(const Vei2& gridPos, Color c)
	:
	c(c)
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
}

void Brick::Draw(Board& brd, Graphics& gfx)
{
	for (const Vei2& pos : tilePositions)
	{
		brd.DrawGhostCell(pos, c, gfx);
	}
}

void Brick::TranslateBy(const Vei2& delta)
{
	for (Vei2& pos : tilePositions)
	{
		pos += delta;
	}
}