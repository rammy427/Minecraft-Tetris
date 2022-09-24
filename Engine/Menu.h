#pragma once

#include "Border.h"
#include "Mouse.h"
#include "Font.h"

class Menu
{
public:
	template <typename T>
	class Entry
	{
	public:
		Entry() = default;
		Entry(T min, T max, T step, T def, const Vei2& pos, const Font& font)
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
				const int x = pos.x + i * (dimension + int(std::to_string(0.0f).size()) * font.GetGlyphWidth() + spacing * 2);
				rects[i] = { { x, pos.y }, dimension, dimension };
			}
		}
		void Update(const Vei2& mousePos)
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
		void Draw(Graphics& gfx)
		{
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
		T GetMin() const
		{
			return min;
		}
		T GetMax() const
		{
			return max;
		}
		T GetSelection() const
		{
			return selection;
		}
	private:
		const Font& font;
		RectI rects[2];
		static constexpr int dimension = 32;
		static constexpr int spacing = 10;
		T min;
		T max;
		T step;
		T def;
		T selection;
	};
public:
	Menu(Mouse& mouse, const Font& font);
	void Update();
	void Draw(Graphics& gfx);
	const Entry<int>& GetGoalEntry() const;
	const Entry<float>& GetSpeedEntry() const;
private:
	Mouse& mouse;
	Entry<int> goalEntry;
	Entry<float> speedEntry;
};