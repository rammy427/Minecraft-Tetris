#include "TextCodex.h"

void TextCodex::DrawGameOver(const Font& font, Graphics& gfx)
{
	const std::string str = "NO ESTAS FILU";
	font.DrawText(str, Graphics::GetRect().GetCenter() - Vei2(font.GetGlyphWidth() * str.size(), font.GetGlyphHeight()) / 2, Colors::Red, gfx);
}