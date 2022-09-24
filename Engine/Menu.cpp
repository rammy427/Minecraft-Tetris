#include "Menu.h"

Menu::Menu(Mouse& mouse, const Font& font)
	:
	mouse(mouse),
	goalEntry(10, 200, 5, 100, { 50, 50 }, font),
	speedEntry(0.0625f, 2.0f, 0.05f, 1.0f, {50, 92}, font)
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