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

	if (DetectCollision() != CollisionType::None)
	{
		// Piece collision detected. Return to previous position.
		tilePositions = std::move(old);
	}
}

void Piece::UpdateDrop(Keyboard& kbd, float dt)
{
	std::vector<Vei2> old = tilePositions;
	dropTime = kbd.KeyIsPressed(VK_DOWN) ? softDropTime : fallTime;
	curTime += dt;
	while (curTime >= dropTime)
	{
		TranslateBy({ 0, 1 });
		curTime = .0f;
	}

	switch (DetectCollision())
	{
	case CollisionType::Bottom:
	case CollisionType::Tile:
		// Peace has reached bottom of the board or another tile.
		tilePositions = std::move(old);
		LockToBoard();
		break;
	}
}

void Piece::Draw(Graphics& gfx)
{
	assert(!tilePositions.empty());
	for (const Vei2& pos : tilePositions)
	{
		brd.TileAt(pos).DrawGhost(c, gfx);
	}
}

void Piece::LockToBoard()
{
	assert(!tilePositions.empty());
	for (Vei2& pos : tilePositions)
	{
		brd.TileAt(pos).SetColor(c);
		brd.TileAt(pos).Set();
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

Piece::CollisionType Piece::DetectCollision() const
{
	const auto xPred = [](const Vei2& lhs, const Vei2& rhs) { return lhs.x < rhs.x; };
	const auto yPred = [](const Vei2& lhs, const Vei2& rhs) { return lhs.y < rhs.y; };
	const auto tilePred = [&](const Vei2& pos) { return brd.TileAt(pos).IsAlive(); };

	const int left = std::min_element(tilePositions.begin(), tilePositions.end(), xPred)->x;
	const int right = std::max_element(tilePositions.begin(), tilePositions.end(), xPred)->x;
	const int top = std::min_element(tilePositions.begin(), tilePositions.end(), yPred)->y;
	const int bottom = std::max_element(tilePositions.begin(), tilePositions.end(), yPred)->y;

	if (left < 0 || right >= brd.GetWidth())
	{
		return CollisionType::Side;
	}
	if (top < 0)
	{
		return CollisionType::Top;
	}
	if (bottom >= brd.GetHeight())
	{
		return CollisionType::Bottom;
	}
	if (std::any_of(tilePositions.begin(), tilePositions.end(), tilePred))
	{
		return CollisionType::Tile;
	}
	return CollisionType::None;
}

void Piece::SpeedUp(int nClearedLines)
{
	fallTime = std::max(minFallTime, 1 / std::powf(2, float(nClearedLines) / 25));
}

void Piece::ResetSpeed()
{
	fallTime = 1;
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
		if (DetectCollision() == CollisionType::None)
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

float Piece::fallTime = 1;