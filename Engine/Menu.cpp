#include "Menu.h"

Menu::Menu(const Vei2& center, const Font& font)
	:
	font(font),
	topLeft(center - Vei2(
		(Menu::Entry::valueStrSize + Menu::Entry::headerSize) * 11 + Menu::Entry::spacing * 7 + Menu::Entry::dimension * 2,
		Menu::Entry::dimension * 4 + Menu::Entry::spacing) / 2),
	goalEntry(10, 200, 5, 100, topLeft, "LINE GOAL:", font),
	levelEntry(1, 10, 1, 1, {topLeft.x, topLeft.y + Menu::Entry::dimension + Menu::Entry::spacing}, "STARTING LEVEL:", font),
	songEntry(0, 13, 1, 13, { topLeft.x, topLeft.y + 2 * (Menu::Entry::dimension + Menu::Entry::spacing) }, "BGM TRACK:", font)
{
}

void Menu::Update(Keyboard& kbd, Mouse& mouse)
{
	if (IsSelecting())
	{
		while (!mouse.IsEmpty())
		{
			const Mouse::Event e = mouse.Read();
			if (e.GetType() == Mouse::Event::Type::LPress)
			{
				goalEntry.Update(e.GetPos());
				levelEntry.Update(e.GetPos());
				songEntry.Update(e.GetPos());
			}
		}

		if (kbd.KeyIsPressed('1'))
		{
			curPage = Page::Controls;
		}
		else if (kbd.KeyIsPressed('2'))
		{
			curPage = Page::Items;
		}
	}
	else
	{
		if (kbd.KeyIsPressed(VK_ESCAPE))
		{
			curPage = Page::Select;
		}
	}
}

void Menu::Draw(Graphics& gfx)
{
	switch (curPage)
	{
	case Page::Select:
	{
		goalEntry.Draw(gfx);
		levelEntry.Draw(gfx);
		songEntry.Draw(gfx);
		const int top = topLeft.y + (Menu::Entry::dimension - font.GetGlyphHeight()) / 2;
		const int unit_offset = Menu::Entry::dimension + Menu::Entry::spacing;
		font.DrawText("Press 1 to view controls.", { topLeft.x, top + unit_offset * 3 }, Colors::Yellow, gfx);
		font.DrawText("Press 2 to view info about items.", { topLeft.x, top + unit_offset * 4 }, Colors::Yellow, gfx);
		break;
	}
	case Page::Controls:
		gfx.DrawSprite(0, 0, controls, SpriteEffect::Copy{});
		break;
	case Page::Items:
		gfx.DrawSprite(0, 0, items, SpriteEffect::Copy{});
		break;
	}
}

const Menu::Entry& Menu::GetGoalEntry() const
{
	return goalEntry;
}

const Menu::Entry& Menu::GetLevelEntry() const
{
	return levelEntry;
}

const Menu::Entry& Menu::GetSongEntry() const
{
	return songEntry;
}

bool Menu::IsSelecting() const
{
	return curPage == Page::Select;
}

Menu::Entry::Entry(int min, int max, int step, int def, const Vei2& pos, const std::string& header, const Font& font)
	:
	min(min),
	max(max),
	step(step),
	def(def),
	pos(pos),
	header(header),
	font(font)
{
	selection = def;
	const int left = pos.x + font.GetGlyphWidth() * headerSize + spacing * 5;
	for (int i = 0; i < 2; i++)
	{
		const int x = left + i * (dimension + valueStrSize * font.GetGlyphWidth() + spacing * 2);
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
	font.DrawText(header, { pos.x, pos.y + (dimension - font.GetGlyphHeight()) / 2 }, Colors::Yellow, gfx);

	for (const RectI& r : rects)
	{
		gfx.DrawRect(r, Colors::Gray);
	}

	const std::string str = std::to_string(selection);
	const int x = (rects[0].right + rects[1].left - int(str.size()) * font.GetGlyphWidth()) / 2;
	const int y = rects[0].GetCenter().y - font.GetGlyphHeight() / 2;
	font.DrawText(str, { x, y }, Colors::White, gfx);

	font.DrawText("<", rects[0].GetCenter() - Vei2(font.GetGlyphWidth(), font.GetGlyphHeight()) / 2, Colors::Black, gfx);
	font.DrawText(">", rects[1].GetCenter() - Vei2(font.GetGlyphWidth(), font.GetGlyphHeight()) / 2, Colors::Black, gfx);
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