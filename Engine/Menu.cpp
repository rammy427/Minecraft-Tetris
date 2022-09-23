#include "Menu.h"

Menu::Entry::Entry(int min, int max, int step, int def, const Vei2& pos, const Font& font)
	:
	min(min),
	max(max),
	step(step),
	def(def),
	font(font)
{
	selection = def;
	for (int i = 0; i < 2; i++)
	{
		const int x = pos.x + i * (dimension + int(std::to_string(max).size()) * font.GetGlyphWidth() + spacing * 2);
		rects[i] = { { x, pos.y }, dimension, dimension };
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
	const std::string str = std::to_string(selection);
	const int x = (rects[0].right + rects[1].left - int(str.size()) * font.GetGlyphWidth()) / 2;
	const int y = rects[0].GetCenter().y - font.GetGlyphHeight() / 2;
	font.DrawText(str, { x, y }, Colors::White, gfx);
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

Menu::Menu(Mouse& mouse, const Font& font)
	:
	mouse(mouse),
	entry(10, 200, 5, 100, { 50, 50 }, font)
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