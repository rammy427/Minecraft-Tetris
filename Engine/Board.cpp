#include "Board.h"

Board::Tile::Tile(const RectI& rect)
	:
	rect(rect)
{
	SetColor(c);
}

void Board::Tile::SetColor(Color c)
{
	bev.SetBaseColor(c);
}

void Board::Tile::Draw(Graphics& gfx) const
{
	if (isAlive)
	{
		bev.DrawBeveledBrick(rect.GetExpanded(-padding), bevelSize, gfx);
	}
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

void Board::Draw(Graphics& gfx) const
{
	for (const Tile& t : tiles)
	{
		t.Draw(gfx);
	}
}

Board::Tile& Board::TileAt(const Vei2& gridPos)
{
	return tiles[gridPos.y * width + gridPos.x];
}