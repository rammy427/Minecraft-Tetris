#pragma once

#include "Board.h"
#include "Font.h"

class TextManager
{
public:
	static void DrawGameOver(const Font& font, Graphics& gfx);
	static void DrawPaused(const Font& font, Graphics& gfx);
	static void DrawVictory(const Font& font, Graphics& gfx);
	static void DrawLineCounter(const Font& font, const Board& brd, Graphics& gfx);
	static void DrawScore(const Font& font, const Board& brd, Graphics& gfx);
	static void DrawQueueText(const Font& font, const RectI& borderRect, Graphics& gfx);
	static void DrawHoldText(const Font& font, const RectI& borderRect, Graphics& gfx);
	static void DrawItemText(const Font& font, const RectI& borderRect, Graphics& gfx);
private:
	static constexpr int spacing = 10;
};