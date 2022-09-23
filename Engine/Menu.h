#pragma once

#include "Border.h"
#include "Mouse.h"
#include "Font.h"

class Menu
{
public:
	class Entry
	{
	public:
		Entry() = default;
		Entry(int min, int max, int step, int def, const Vei2& pos, const Font& font);
		void Update(const Vei2& mousePos);
		void Draw(Graphics& gfx);
		int GetMin() const;
		int GetMax() const;
		int GetSelection() const;
	private:
		const Font& font;
		RectI rects[2];
		static constexpr int dimension = 32;
		static constexpr int spacing = 10;
		int min;
		int max;
		int step;
		int def;
		int selection;
	};
public:
	Menu(Mouse& mouse, const Font& font);
	void Update();
	void Draw(Graphics& gfx);
	const Entry& GetEntry() const;
private:
	Mouse& mouse;
	Entry entry;
};