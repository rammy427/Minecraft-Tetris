#include "Menu.h"

Menu::Menu(const Vei2& center, const Font& font)
	:
	font(font),
	topLeft(center - Vei2(
		(Menu::Entry<int>::valueStrSize + Menu::Entry<int>::headerSize) * 11 + Menu::Entry<int>::spacing * 7 + Menu::Entry<int>::dimension * 2,
		Menu::Entry<int>::dimension * 4 + Menu::Entry<int>::spacing) / 2),
	goalEntry(10, 200, 5, 100, topLeft, "Line goal:", font),
	speedEntry(0.0625f, 2.0f, 0.05f, 1.0f, {topLeft.x, topLeft.y + Menu::Entry<int>::dimension + Menu::Entry<int>::spacing}, "Starting speed:", font)
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
				speedEntry.Update(e.GetPos());
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
		speedEntry.Draw(gfx);
		const int top = topLeft.y + (Menu::Entry<int>::dimension - font.GetGlyphHeight()) / 2;
		const int unit_offset = Menu::Entry<int>::dimension + Menu::Entry<int>::spacing;
		font.DrawText("Press 1 to view controls.", { topLeft.x, top + unit_offset * 2 }, Colors::Yellow, gfx);
		font.DrawText("Press 2 to view info about items.", { topLeft.x, top + unit_offset * 3 }, Colors::Yellow, gfx);
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

const Menu::Entry<int>& Menu::GetGoalEntry() const
{
	return goalEntry;
}

const Menu::Entry<float>& Menu::GetSpeedEntry() const
{
	return speedEntry;
}

bool Menu::IsSelecting() const
{
	return curPage == Page::Select;
}