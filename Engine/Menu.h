#pragma once

#include "Border.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "Font.h"

class Menu
{
public:
	enum class Page
	{
		Select,
		Controls,
		Items
	};
private:
	template <typename T>
	class Entry
	{
	public:
		Entry() = default;
		Entry(T min, T max, T step, T def, const Vei2& pos, const std::string& header, const Font& font)
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
	public:
		static constexpr int dimension = 32;
		static constexpr int spacing = 10;
		static constexpr int headerSize = 15;
		static constexpr int valueStrSize = 8;
	private:
		Vei2 pos;
		const Font& font;
		std::string header;
		RectI rects[2];
		T min;
		T max;
		T step;
		T def;
		T selection;
	};
public:
	Menu(const Vei2& center, const Font& font);
	void Update(Keyboard& kbd, Mouse& mouse);
	void Draw(Graphics& gfx);
	const Entry<int>& GetGoalEntry() const;
	const Entry<float>& GetSpeedEntry() const;
	bool IsSelecting() const;
private:
	Vei2 topLeft;
	Page curPage = Page::Select;
	Entry<int> goalEntry;
	Entry<float> speedEntry;
	const Font& font;
	Surface controls = "Sprites\\controlpage.bmp";
	Surface items = "Sprites\\itempage.bmp";
};