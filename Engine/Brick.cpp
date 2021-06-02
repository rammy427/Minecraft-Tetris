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

void Brick::Update(Keyboard& kbd, float dt)
{
	while (!kbd.KeyIsEmpty())
	{
		const Keyboard::Event e = kbd.ReadKey();
		if (e.IsPress())
		{
			switch (e.GetCode())
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
			}
		}
	}

	dropWaitTime = kbd.KeyIsPressed(VK_DOWN) ? .05f : .75f;
	curTime += dt;
	while (curTime >= dropWaitTime)
	{
		TranslateBy({ 0, 1 });
		curTime = .0f;
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
	std::vector<Vei2> newPositions;
	for (const Vei2& pos : tilePositions)
	{
		newPositions.push_back(pos + delta);
	}

	if (!WillCollide(newPositions))
	{
		std::move(newPositions.begin(), newPositions.end(), tilePositions.begin());
	}
}

void Brick::Rotate(bool clockwise)
{
	// Rotate brick by 90 degrees.
	const Vei2 origin = tilePositions.front();
	std::vector<Vei2> newPositions;
	for (const Vei2& pos : tilePositions)
	{
		if (clockwise)
		{
			// Clockwise rotation. (x, y) -> (-y, x).
			newPositions.push_back(Vei2(origin.y - pos.y, pos.x - origin.x) + origin);
		}
		else
		{
			// Counter-clockwise rotation. (x, y) -> (y, -x).
			newPositions.push_back(Vei2(pos.y - origin.y, origin.x - pos.x) + origin);
		}
	}

	if (!WillCollide(newPositions))
	{
		std::move(newPositions.begin(), newPositions.end(), tilePositions.begin());
	}
}

bool Brick::WillCollide(const std::vector<Vei2>& newPositions) const
{
	return std::any_of(newPositions.begin(), newPositions.end(),
		[&](const Vei2& pos)
		{
			return !brd.IsInsideBoard(pos);
		}
	);
}