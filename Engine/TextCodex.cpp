#include "TextCodex.h"

void TextCodex::DrawTitle(const Font& font, Graphics& gfx)
{
	const std::string str = "MINECRAFT TETRIS";
	font.DrawText(str, Graphics::GetRect().GetCenter() - Vei2(font.GetGlyphWidth() * int(str.size()), font.GetGlyphHeight()) / 2, Colors::Blue, gfx);
}

void TextCodex::DrawGameOver(const Font& font, Graphics& gfx)
{
	const std::string str = "NO ESTAS FILU";
	font.DrawText(str, Graphics::GetRect().GetCenter() - Vei2(font.GetGlyphWidth() * int(str.size()), font.GetGlyphHeight()) / 2, Colors::Red, gfx);
}

void TextCodex::DrawLineCounter(const Font& font, const Board& brd, Graphics& gfx)
{
	font.DrawText("Lines cleared:", { spacing, spacing }, Colors::White, gfx);
	font.DrawText(std::to_string(brd.GetClearedLineCount()), { spacing, font.GetGlyphHeight() + spacing }, Colors::White, gfx);
}

void TextCodex::DrawNextPieceText(const Font& font, const QueuedPiece& nextPiece, Graphics& gfx)
{
	const std::string str = "Next brick:";
	const Vei2 pos = { nextPiece.GetRect().GetCenter().x - font.GetGlyphWidth() * int(str.size()) / 2, nextPiece.GetRect().top - font.GetGlyphHeight() - spacing };
	font.DrawText(str, pos, Colors::White, gfx);
}