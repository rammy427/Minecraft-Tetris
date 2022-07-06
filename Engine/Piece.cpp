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
		{228, 25, 25},	// Red
		{25, 228, 25},	// Green
		{25, 25, 228},	// Blue
		{228, 228, 25},	// Yellow
		{228, 25, 228},	// Magenta
		{25, 228, 228},	// Cyan
		{228, 126, 25}	// Orange
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
}

void Piece::UpdateDrop(Keyboard& kbd, float dt)
{
	dropTime = kbd.KeyIsPressed(VK_DOWN) ? softDropTime : fallTime;
	curTime += dt;
	while (curTime >= dropTime)
	{
		TranslateBy({ 0, 1 });
		curTime = .0f;
	}
}

void Piece::Draw(Graphics& gfx)
{
	assert(!tilePositions.empty());
	for (const Vei2& pos : tilePositions)
	{
		brd.get().TileAt(pos).DrawGhost(c, gfx);
	}
}

void Piece::LockToBoard()
{
	assert(!tilePositions.empty());
	for (Vei2& pos : tilePositions)
	{
		brd.get().TileAt(pos).SetColor(c);
		brd.get().TileAt(pos).Set();
	}
	// Clear piece tiles since they're now locked to the board.
	// Piece should now be deleted.
	tilePositions.clear();
}

bool Piece::IsLocked() const
{
	// If locked, position vector should be empty.
	return tilePositions.empty();
}

bool Piece::IsColliding() const
{
	const auto pred = [&](const Vei2& pos){ return TileIsColliding(pos); };
	return std::any_of(tilePositions.begin(), tilePositions.end(), pred);
}

void Piece::SpeedUp(int nClearedLines)
{
	fallTime = std::max(minFallTime, 1 / std::powf(2, float(nClearedLines) / 25));
}

void Piece::ResetSpeed()
{
	fallTime = 1.0f;
}

int Piece::GetMaxShapes()
{
	return nShapes;
}

const std::vector<Vei2>& Piece::GetTilePositions() const
{
	return tilePositions;
}

void Piece::TranslateBy(const Vei2& delta)
{
	const std::vector<Vei2> old = tilePositions;
	for (Vei2& pos : tilePositions)
	{
		pos += delta;
	}

	if (IsColliding())
	{
		// Revert translation.
		tilePositions = old;
		if (delta.y > 0)
		{
			// Reached bottom limit. Lock piece to board.
			LockToBoard();
		}
	}
}

void Piece::Drop()
{
	std::vector<Vei2> old;
	do
	{
		old = tilePositions;
		TranslateBy({ 0, 1 });
	} while (old != tilePositions);
}

void Piece::Rotate(bool clockwise)
{
	if (!IsLocked())
	{
		const std::vector<Vei2> old = tilePositions;
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

		if (IsColliding())
		{
			// Revert rotation.
			tilePositions = old;
		}
	}
}

bool Piece::TileIsColliding(const Vei2& gridPos) const
{
	return !brd.get().IsInsideBoard(gridPos) || brd.get().TileAt(gridPos).IsAlive();
}

float Piece::fallTime = 1.0f;