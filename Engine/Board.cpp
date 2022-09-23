#include "Board.h"
#include <algorithm>
#include <iterator>
#include "Piece.h"
#include "Score.h"

Board::Tile::Tile(const RectI& rect)
	:
	rect(rect)
{
}

void Board::Tile::Set()
{
	assert(!isAlive);
	isAlive = true;
}

void Board::Tile::Kill()
{
	isAlive = false;
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
		bev.DrawBeveledBrick(rect.GetExpanded(-padding), bevelSize, gfx);
	}
	else
	{
		DrawGhost({ 171, 142, 114 }, gfx); // Dark Apricot.
	}
}

void Board::Tile::DrawGhost(Color color, Graphics& gfx)
{
	assert(!isAlive);
	bev.SetBaseColor(color);
	bev.DrawBeveledBrick(rect.GetExpanded(-padding), bevelSize, gfx, true);
}

int Board::Tile::GetDimension()
{
	return dimension;
}

int Board::Tile::GetPadding()
{
	return padding;
}

bool Board::Tile::IsAlive() const
{
	return isAlive;
}

Color Board::Tile::GetColor() const
{
	return c;
}

Board::Board(const Vei2& center)
	:
	topLeft(center - Vei2(width, height) * Tile::GetDimension() / 2),
	border({ topLeft, width * Tile::GetDimension(), height * Tile::GetDimension() })
{
	const int dim = Tile::GetDimension();
	for (Vei2 gridPos = { 0,0 }; gridPos.y < height; gridPos.y++)
	{
		for (gridPos.x = 0; gridPos.x < width; gridPos.x++)
		{
			TileAt(gridPos) = { { gridPos * dim + topLeft, dim, dim } };
		}
	}
	Reset(true);
}

void Board::ClearRows()
{
	int streak = 0;
	for (Vei2 gridPos = { 0, 0 }; gridPos.y < height; gridPos.y++)
	{
		const auto begin = std::begin(tiles) + width * std::size_t(gridPos.y);
		const auto end = std::begin(tiles) + width * (std::size_t(gridPos.y) + 1);
		const auto pred = [](Tile& t){ return t.IsAlive(); };
		// If all tiles in row are set...
		if (std::all_of(begin, end, pred))
		{
			// Kill all tiles in row.
			for (auto i = begin; i != end; i++)
			{
				i->Kill();
			}
			// Let every floating tile fall down.
			for (Vei2 scanPos = { 0, gridPos.y }; scanPos.y > 0; scanPos.y--)
			{
				for (scanPos.x = 0; scanPos.x < width; scanPos.x++)
				{
					Tile& upperTile = TileAt(Vei2(scanPos.x, scanPos.y - 1));
					if (upperTile.IsAlive())
					{
						TileAt(scanPos).SetColor(upperTile.GetColor());
						TileAt(scanPos).Set();
						upperTile.Kill();
					}
				}
			}
			Piece::UpdateFreeFallTime(++nClearedLines);
			Score::Add(200);
			streak++;
		}
	}

	if (streak >= 4)
	{
		// TETRIS combo achieved.
		Score::Add(1000);
	}
}

void Board::Reset(bool clearLines)
{
	for (Tile& t : tiles)
	{
		t.Kill();
	}
	
	if (clearLines)
	{
		nClearedLines = 0;
		lineGoal = 2;
	}
}

void Board::Draw(Graphics& gfx)
{
	for (Tile& t : tiles)
	{
		t.Draw(gfx);
	}
	border.Draw(gfx);
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

int Board::GetClearedLineCount() const
{
	return nClearedLines;
}

int Board::GetLineGoal() const
{
	return lineGoal;
}

const RectI& Board::GetRect() const
{
	return border.GetInnerBounds();
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

Vei2 Board::ScreenToGrid(const Vei2& screenPos) const
{
	return (screenPos - topLeft) / Tile::GetDimension();
}