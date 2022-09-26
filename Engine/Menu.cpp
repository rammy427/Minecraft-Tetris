#include "Menu.h"

Menu::Menu(const Vei2& center, Mouse& mouse, const Font& font)
	:
	mouse(mouse),
	topLeft(center - Vei2(
		(Menu::Entry<int>::valueStrSize + Menu::Entry<int>::headerSize) * 11 + Menu::Entry<int>::spacing * 7 + Menu::Entry<int>::dimension * 2,
		Menu::Entry<int>::dimension * 2 + Menu::Entry<int>::spacing) / 2),
	goalEntry(10, 200, 5, 100, topLeft, "Line goal:", font),
	speedEntry(0.0625f, 2.0f, 0.05f, 1.0f, {topLeft.x, topLeft.y + Menu::Entry<int>::dimension + Menu::Entry<int>::spacing}, "Starting speed:", font)
{
}

void Menu::Update()
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
}

void Menu::Draw(Graphics& gfx)
{
	goalEntry.Draw(gfx);
	speedEntry.Draw(gfx);
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