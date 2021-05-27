#include "Brick.h"
#include <random>

Brick::Brick(const Vei2& gridPos, Color c, Board& brd)
	:
	c(c),
	brd(brd)
{
	constexpr int nShapes = 7;
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

	std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution<int> shapeDist(0, nShapes - 1);
	tilePositions.reserve(tileAmount);
	tilePositions = shapes[shapeDist(rng)];
}

void Brick::Update(Keyboard& kbd)
{
	if (kbd.KeyIsPressed('A'))
	{
		Rotate(false);
	}
	else if (kbd.KeyIsPressed('D'))
	{
		Rotate(true);
	}

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

void Brick::Rotate(bool clockwise)
{
	// Rotate brick by 90 degrees.
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