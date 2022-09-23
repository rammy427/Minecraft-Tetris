#include "Menu.h"

Menu::Entry::Entry(int min, int max, int step, int def, const Vei2& pos)
	:
	min(min),
	max(max),
	step(step),
	def(def)
{
	selection = def;
	const int padding = 10;
	for (int i = 0; i < 2; i++)
	{
		rects[i] = { { pos.x + i * dimension + padding, pos.y }, dimension, dimension };
	}
}

void Menu::Entry::Update(const Vei2& mousePos)
{
	if (rects[0].Contains(mousePos))
	{
		selection = std::max(min, selection - step);
	}
	else if (rects[1].Contains(mousePos))
	{
		selection = std::min(max, selection + step);
	}
}

void Menu::Entry::Draw(Graphics& gfx)
{
	for (const RectI& r : rects)
	{
		gfx.DrawRect(r, Colors::Gray);
	}
}

int Menu::Entry::GetMin() const
{
	return min;
}

int Menu::Entry::GetMax() const
{
	return max;
}

int Menu::Entry::GetSelection() const
{
	return selection;
}

Menu::Menu(Mouse& mouse)
	:
	mouse(mouse),
	entry(10, 200, 5, 100, { 50, 50 })
{
}

void Menu::Update()
{
	while (!mouse.IsEmpty())
	{
		const Mouse::Event e = mouse.Read();
		if (e.LeftIsPressed())
		{
			entry.Update(e.GetPos());
		}
	}
}

void Menu::Draw(Graphics& gfx)
{
	entry.Draw(gfx);
}

const Menu::Entry& Menu::GetEntry() const
{
	return entry;
}