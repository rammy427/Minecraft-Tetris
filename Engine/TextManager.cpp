#include "TextManager.h"

void TextManager::DrawTitle(const Font& font, Graphics& gfx)
{
	const std::string str = "MINECRAFT TETRIS";
	font.DrawText(str, Graphics::GetRect().GetCenter() - Vei2(font.GetGlyphWidth() * int(str.size()), font.GetGlyphHeight()) / 2, Colors::Blue, gfx);
}

void TextManager::DrawGameOver(const Font& font, Graphics& gfx)
{
	const std::string str = "NO ESTAS FILU";
	font.DrawText(str, Graphics::GetRect().GetCenter() - Vei2(font.GetGlyphWidth() * int(str.size()), font.GetGlyphHeight()) / 2, Colors::Red, gfx);
}

void TextManager::DrawLineCounter(const Font& font, const Board& brd, Graphics& gfx)
{
	font.DrawText("Lines cleared:", { spacing, spacing }, Colors::White, gfx);
	font.DrawText(std::to_string(brd.GetClearedLineCount()), { spacing, font.GetGlyphHeight() + spacing }, Colors::White, gfx);
}