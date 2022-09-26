#include "Menu.h"

Menu::Menu(const Vei2& center, const Font& font)
	:
	topLeft(center - Vei2(
		(Menu::Entry<int>::valueStrSize + Menu::Entry<int>::headerSize) * 11 + Menu::Entry<int>::spacing * 7 + Menu::Entry<int>::dimension * 2,
		Menu::Entry<int>::dimension * 2 + Menu::Entry<int>::spacing) / 2),
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
		goalEntry.Draw(gfx);
		speedEntry.Draw(gfx);
		break;
	case Page::Controls:
		const int x = (Graphics::ScreenWidth - controls.GetWidth()) / 2;
		const int y = (Graphics::ScreenHeight - controls.GetHeight()) / 2;
		gfx.DrawSprite(x, y, controls, SpriteEffect::Chroma{});
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