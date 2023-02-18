#include "Piece.h"
#include "Score.h"
#include <sstream>

Piece::Piece(int shape, const Vei2& gridPos, Board& brd)
	:
	shape(shape),
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

void Piece::ProcessTransformations(Keyboard& kbd, Controller& controller, unsigned char eventCharCode)
{
	if (!isFrozen)
	{
		std::vector<Vei2> old = tilePositions;

		if (eventCharCode == controller.GetBinding(Controller::Key::RotateLeft))
		{
			kbd.DisableAutorepeat();
			Rotate(false);
		}
		else if (eventCharCode == controller.GetBinding(Controller::Key::RotateRight))
		{
			kbd.DisableAutorepeat();
			Rotate(true);
		}
		else if (eventCharCode == controller.GetBinding(Controller::Key::MoveLeft))
		{
			kbd.EnableAutorepeat();
			TranslateBy({ -1, 0 });
		}
		else if (eventCharCode == controller.GetBinding(Controller::Key::MoveRight))
		{
			kbd.EnableAutorepeat();
			TranslateBy({ 1, 0 });
		}
		else if (eventCharCode == controller.GetBinding(Controller::Key::HardDrop))
		{
			kbd.DisableAutorepeat();
			Drop();
		}
	}
}

void Piece::UpdateDrop(Keyboard& kbd, Controller& controller, float dt)
{
	if (!isFrozen)
	{
		if (effect != Effect::None)
		{
			curEffectTime += dt;
			if (curEffectTime >= potionEffectDuration)
			{
				effect = Effect::None;
				curEffectTime = 0.0f;
			}
		}

		switch (effect)
		{
		case Effect::None:
			speed = kbd.KeyIsPressed(controller.GetBinding(Controller::Key::SoftDrop)) ? softDropTime : freeFallTime;
			break;
		case Effect::Slowdown:
			speed = maxSpeed;
			break;
		case Effect::Speedup:
			speed = minSpeed;
			break;
		}

		curTime += dt;
		while (curTime >= speed)
		{
			TranslateBy({ 0, 1 });
			curTime = 0.0f;
		}
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
	if (!tilePositions.empty())
	{
		for (Vei2& pos : tilePositions)
		{
			brd.get().TileAt(pos).SetColor(c);
			brd.get().TileAt(pos).Set();
		}
		// Clear piece tiles since they're now locked to the board.
		// Piece should now be deleted.
		tilePositions.clear();
		Score::Add(10);
	}
}

void Piece::Cut()
{
	for (auto i = tilePositions.begin(); i != tilePositions.end();)
	{
		if (TileIsColliding(*i))
		{
			i = tilePositions.erase(i);
		}
		else
		{
			i++;
		}
	}
}

void Piece::Freeze()
{
	isFrozen = true;
}

void Piece::Unfreeze()
{
	isFrozen = false;
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

bool Piece::IsFrozen() const
{
	return isFrozen;
}

void Piece::InitPotionEffect(bool isSpeedingUp)
{
	effect = isSpeedingUp ? Effect::Speedup : Effect::Slowdown;
}

void Piece::UpdateFreeFallTime()
{
	freeFallTime = std::max(minSpeed, freeFallTime - speedStep);
}

void Piece::ResetStaticData(int minLevel, int maxLevel, int startingLevel)
{
	SetInitialSpeed(minLevel, maxLevel, startingLevel);
	curEffectTime = 0.0f;
	effect = Effect::None;
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
	if (shape != 3 && !IsLocked())
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

		const auto pred = [&](const Vei2& lhs, const Vei2& rhs) {return lhs.x < rhs.x; };
		const auto left = std::min_element(tilePositions.begin(), tilePositions.end(), pred)->x;
		const auto right = std::max_element(tilePositions.begin(), tilePositions.end(), pred)->x;

		if (left < 0)
		{
			TranslateBy({ -left, 0 });
		}
		else if (right >= brd.get().GetWidth())
		{
			TranslateBy({ brd.get().GetWidth() - right - 1, 0 });
		}

		if (IsColliding())
		{
			// Revert rotation.
			tilePositions = old;
		}
		else
		{
			sndRotate.Play();
		}
	}
}

bool Piece::TileIsColliding(const Vei2& gridPos) const
{
	return !brd.get().IsInsideBoard(gridPos) || brd.get().TileAt(gridPos).IsAlive();
}

void Piece::SetInitialSpeed(int minLevel, int maxLevel, int startingLevel)
{
	freeFallTime = (maxSpeed / 2 - minSpeed) / (minLevel - maxLevel) * (startingLevel - maxLevel) + minSpeed;
}

float Piece::freeFallTime = 1.0f;
float Piece::curEffectTime = 0.0f;
Piece::Effect Piece::effect = Effect::None;