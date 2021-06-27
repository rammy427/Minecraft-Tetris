#pragma once

#include "Font.h"
#include "QueuedBrick.h"

class TextCodex
{
public:
	static void DrawTitle(const Font& font, Graphics& gfx);
	static void DrawGameOver(const Font& font, Graphics& gfx);
	static void DrawLineCounter(const Font& font, const Board& brd, Graphics& gfx);
	static void DrawNextBrickText(const Font& font, const QueuedBrick& nextBrick, Graphics& gfx);
private:
	static constexpr int spacing = 10;
};