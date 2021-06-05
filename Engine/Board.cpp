#include "Board.h"

Board::Tile::Tile(const RectI& rect)
	:
	rect(rect)
{
}

void Board::Tile::Set()
{
	isAlive = true;
}

void Board::Tile::SetColor(Color c_in)
{
	c = c_in;
}

void Board::Tile::Draw(Graphics& gfx)
{
	if (isAlive)
	{
		bev.SetBaseColor(c);
	}
	else
	{
		bev.SetBaseColor(Colors::Gray);
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

bool Board::Tile::IsAlive() const
{
	return isAlive;
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

void Board::SetTile(const Vei2& gridPos, Color c)
{
	TileAt(gridPos).SetColor(c);
	TileAt(gridPos).Set();
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

bool Board::TileIsAlive(const Vei2& gridPos) const
{
	return TileAt(gridPos).IsAlive();
}

bool Board::IsInsideBoard(const Vei2& gridPos) const
{
	return gridPos.x >= 0 &&
		gridPos.x < width &&
		gridPos.y >= 0 &&
		gridPos.y < height;
}

int Board::GetWidth() const
{
	return width;
}

int Board::GetHeight() const
{
	return height;
}

Board::Tile& Board::TileAt(const Vei2& gridPos)
{
	assert(IsInsideBoard(gridPos));
	return tiles[gridPos.y * width + gridPos.x];
}

const Board::Tile& Board::TileAt(const Vei2& gridPos) const
{
	return const_cast<Board*>(this)->TileAt(gridPos);
}