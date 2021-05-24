#include "Board.h"

Board::Tile::Tile(const RectI& rect)
	:
	rect(rect)
{
}

void Board::Tile::Draw(Graphics& gfx)
{
	if (isAlive)
	{
		bev.SetBaseColor(c);
	}
	else
	{
		bev.SetBaseColor({ 230,230,230 });
	}
	bev.DrawBeveledBrick(rect.GetExpanded(-padding), bevelSize, gfx);
}

void Board::Tile::DrawGhost(Color ghostColor, Graphics& gfx)
{
	assert(!isAlive);
	bev.SetBaseColor(ghostColor);
	bev.DrawBeveledBrick(rect.GetExpanded(-padding), bevelSize, gfx);
}

int Board::Tile::GetDimension()
{
	return dimension;
}

Board::Board(const Vei2& center)
	:
	topLeft(center - Vei2(width, height) * Tile::GetDimension() / 2)
{
	const int dim = Tile::GetDimension();
	for (Vei2 gridPos = { 0,0 }; gridPos.y < height; gridPos.y++)
	{
		for (gridPos.x = 0; gridPos.x < width; gridPos.x++)
		{
			TileAt(gridPos) = { { gridPos * dim + topLeft, dim, dim } };
		}
	}
}

void Board::Draw(Graphics& gfx)
{
	for (Tile& t : tiles)
	{
		t.Draw(gfx);
	}
}

void Board::DrawGhostCell(const Vei2& gridPos, Color ghostColor, Graphics& gfx)
{
	TileAt(gridPos).DrawGhost(ghostColor, gfx);
}

Board::Tile& Board::TileAt(const Vei2& gridPos)
{
	assert(gridPos.x >= 0);
	assert(gridPos.x < width);
	assert(gridPos.y >= 0);
	assert(gridPos.y < height);
	return tiles[gridPos.y * width + gridPos.x];
}