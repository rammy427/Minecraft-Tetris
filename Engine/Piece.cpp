#include "Piece.h"
#include "ChiliWin.h"
#include <sstream>

Piece::Piece(int shape, const Vei2& gridPos, Board& brd)
	:
	brd(brd)
{
	std::vector<std::vector<Vei2>> shapes;
	shapes.resize(nShapes);

	// Shape 0 (T)
	shapes[0] =
	{
		{gridPos},
		{gridPos.x - 1, gridPos.y},
		{gridPos.x + 1, gridPos.y},
		{gridPos.x, gridPos.y + 1}
	};
	// Shape 1 (Left Q)
	shapes[1] =
	{
		{gridPos},
		{gridPos.x + 1, gridPos.y},
		{gridPos.x - 1, gridPos.y + 1},
		{gridPos.x, gridPos.y + 1}
	};
	// Shape 2 (Right Q)
	shapes[2] =
	{
		{gridPos},
		{gridPos.x - 1, gridPos.y},
		{gridPos.x, gridPos.y + 1},
		{gridPos.x + 1, gridPos.y + 1}
	};
	// Shape 3 (Square)
	shapes[3] =
	{
		{gridPos},
		{gridPos.x + 1, gridPos.y},
		{gridPos.x, gridPos.y + 1},
		{gridPos.x + 1, gridPos.y + 1}
	};
	// Shape 4 (Left L)
	shapes[4] =
	{
		{gridPos},
		{gridPos.x - 1, gridPos.y},
		{gridPos.x + 1, gridPos.y},
		{gridPos.x - 1, gridPos.y + 1}
	};
	// Shape 5 (Right L)
	shapes[5] =
	{
		{gridPos},
		{gridPos.x - 1, gridPos.y},
		{gridPos.x + 1, gridPos.y},
		{gridPos.x + 1, gridPos.y + 1}
	};
	// Shape 6 (Line)
	shapes[6] =
	{
		{gridPos},
		{gridPos.x - 1, gridPos.y},
		{gridPos.x + 1, gridPos.y},
		{gridPos.x + 2, gridPos.y}
	};

	constexpr Color colors[nShapes] =
	{
		{230, 0, 0},	// Red
		{0, 230, 0},	// Green
		{0, 0, 230},	// Blue
		{230, 230, 0},	// Yellow
		{230, 0, 230},	// Magenta
		{0, 230, 230},	// Cyan
		{230, 103, 0}	// Orange
	};

	tilePositions.reserve(tileAmount);
	tilePositions = shapes[shape];
	c = colors[shape];
}

void Piece::ProcessTransformations(Keyboard& kbd, unsigned char eventCharCode)
{
	std::vector<Vei2> old = tilePositions;
	switch (eventCharCode)
	{
	case 'A':
		kbd.DisableAutorepeat();
		Rotate(false);
		break;
	case 'D':
		kbd.DisableAutorepeat();
		Rotate(true);
		break;
	case VK_LEFT:
		kbd.EnableAutorepeat();
		TranslateBy({ -1, 0 });
		break;
	case VK_RIGHT:
		kbd.EnableAutorepeat();
		TranslateBy({ 1, 0 });
		break;
	case VK_UP:
		kbd.DisableAutorepeat();
		Drop();
		break;
	}

	if (IsColliding())
	{
		// HORIZONTAL transformation failed. Revert to previous position.
		tilePositions = std::move(old);
	}
}

void Piece::UpdateDrop(Keyboard& kbd, float dt)
{
	std::vector<Vei2> old = tilePositions;
	dropWaitTime = kbd.KeyIsPressed(VK_DOWN) ? .05f : .75f;
	curTime += dt;
	while (curTime >= dropWaitTime)
	{
		TranslateBy({ 0, 1 });
		curTime = .0f;
	}

	if (IsColliding())
	{
		// VERTICAL transformation failed (has reached limit). Bind piece to board.
		tilePositions = std::move(old);
		BindToBoard();
	}
}

void Piece::Draw(Graphics& gfx)
{
	assert(!tilePositions.empty());
	for (const Vei2& pos : tilePositions)
	{
		brd.DrawGhostCell(pos, Color(c.GetR() / 2, c.GetG() / 2, c.GetB() / 2), gfx);
	}
}

void Piece::BindToBoard()
{
	assert(!tilePositions.empty());
	for (Vei2& pos : tilePositions)
	{
		brd.SetTile(pos, c);
	}
	// Clear piece tiles since they're now binded to the board.
	// Piece should now be deleted.
	tilePositions.clear();
}

bool Piece::IsBinded() const
{
	// If binded, position vector should be empty.
	return tilePositions.empty();
}

bool Piece::IsColliding() const
{
	return std::any_of(tilePositions.begin(), tilePositions.end(),
		[&](const Vei2& pos)
		{
			return !brd.IsInsideBoard(pos) || brd.TileIsAlive(pos);
		}
	);
}

int Piece::GetMaxShapes()
{
	return nShapes;
}

void Piece::TranslateBy(const Vei2& delta)
{
	for (Vei2& pos : tilePositions)
	{
		pos += delta;
	}
}

void Piece::Drop()
{
	std::vector<Vei2> temp = tilePositions;
	while (temp == tilePositions)
	{
		TranslateBy({ 0, 1 });
		if (!IsColliding())
		{
			temp = tilePositions;
		}
	}
	tilePositions = std::move(temp);
}

void Piece::Rotate(bool clockwise)
{
	// Rotate piece by 90 degrees.
	const Vei2 origin = tilePositions.front();
	for (Vei2& pos : tilePositions)
	{
		if (clockwise)
		{
			// Clockwise rotation. (x, y) -> (-y, x).
			pos = Vei2(origin.y - pos.y, pos.x - origin.x) + origin;
		}
		else
		{
			// Counter-clockwise rotation. (x, y) -> (y, -x).
			pos = Vei2(pos.y - origin.y, origin.x - pos.x) + origin;
		}
	}
}