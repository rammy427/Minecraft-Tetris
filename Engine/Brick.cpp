#include "Brick.h"

Brick::Brick(const Vei2& gridPos, Color c)
	:
	c(c)
{
	tilePositions[0] = gridPos;
	tilePositions[1] = { gridPos.x - 1, gridPos.y };
	tilePositions[2] = { gridPos.x + 1, gridPos.y };
	tilePositions[3] = { gridPos.x + 2, gridPos.y };
}

void Brick::Draw(Board& brd, Graphics& gfx)
{
	for (const Vei2& pos : tilePositions)
	{
		brd.DrawGhostCell(pos, c, gfx);
	}
}