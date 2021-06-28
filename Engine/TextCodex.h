#pragma once

#include "Font.h"
#include "QueuedPiece.h"

class TextCodex
{
public:
	static void DrawTitle(const Font& font, Graphics& gfx);
	static void DrawGameOver(const Font& font, Graphics& gfx);
	static void DrawLineCounter(const Font& font, const Board& brd, Graphics& gfx);
	static void DrawNextPieceText(const Font& font, const QueuedPiece& nextPiece, Graphics& gfx);
private:
	static constexpr int spacing = 10;
};