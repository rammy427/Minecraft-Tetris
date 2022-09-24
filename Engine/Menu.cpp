#include "Menu.h"

Menu::Menu(Mouse& mouse, const Font& font)
	:
	mouse(mouse),
	goalEntry(10, 200, 5, 100, { 50, 50 }, font)
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
		}
	}
}

void Menu::Draw(Graphics& gfx)
{
	goalEntry.Draw(gfx);
}

const Menu::Entry<int>& Menu::GetGoalEntry() const
{
	return goalEntry;
}