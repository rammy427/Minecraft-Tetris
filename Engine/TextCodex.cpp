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
	font.DrawText("Lines cleared:", { 10, 10 }, Colors::White, gfx);
	font.DrawText(std::to_string(brd.GetClearedLineCount()), { 10, font.GetGlyphHeight() + 10 }, Colors::White, gfx);
}