#pragma once

#include "Board.h"
#include "Font.h"

class TextCodex
{
public:
	static void DrawTitle(const Font& font, Graphics& gfx);
	static void DrawGameOver(const Font& font, Graphics& gfx);
	static void DrawLineCounter(const Font& font, const Board& brd, Graphics& gfx);
private:
	static constexpr int spacing = 10;
};