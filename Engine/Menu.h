#pragma once

#include "Border.h"
#include "Mouse.h"
#include "Controller.h"
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
	class Entry
	{
	public:
		Entry(int min, int max, int step, int def, const Vei2& pos, const std::string& header, const Font& font, bool charMode = false, bool hasEndlessMode = false);
		void Update(const Vei2& mousePos);
		void Draw(const Font& font, Graphics& gfx);
		int GetMin() const;
		int GetMax() const;
		int GetSelection() const;
	public:
		static constexpr int dimension = 32;
		static constexpr int spacing = 10;
		static constexpr int headerSize = 15;
		static constexpr int valueStrSize = 8;
	private:
		Vei2 pos;
		std::string header;
		RectI rects[2];
		bool isOnCharMode;
		bool hasEndlessMode;
		int min;
		int max;
		int step;
		int def;
		int selection;
	};
public:
	Menu(const Vei2& center, const Font& font, const Controller& controller);
	void Update(Keyboard& kbd, Mouse& mouse);
	void Draw(const Font& font, Graphics& gfx);
	const Entry& GetGoalEntry() const;
	const Entry& GetLevelEntry() const;
	const Entry& GetSongEntry() const;
	const std::vector<Entry>& GetKeyEntries() const;
	bool IsOnMain() const;
private:
	Vei2 topLeft;
	Page curPage = Page::Select;
	Entry goalEntry;
	Entry levelEntry;
	Entry songEntry;
	std::vector<Entry> keyEntries;
	const Font& font;
	Surface items = "Sprites\\itempage.bmp";
};