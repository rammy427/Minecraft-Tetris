#include "TextManager.h"

void TextManager::DrawGameOver(const Font& font, Graphics& gfx)
{
	const std::string str = "NO ESTAS FILU";
	font.DrawText(str, Graphics::GetRect().GetCenter() - Vei2(font.GetGlyphWidth() * int(str.size()), font.GetGlyphHeight()) / 2, Colors::Red, gfx);
}

void TextManager::DrawPaused(const Font& font, Graphics& gfx)
{
	const std::string str = "PAUSE";
	font.DrawText(str, Graphics::GetRect().GetCenter() - Vei2(font.GetGlyphWidth() * int(str.size()), font.GetGlyphHeight()) / 2, Colors::Red, gfx);
}

void TextManager::DrawVictory(const Font& font, Graphics& gfx)
{
	const std::string str = "ESTAS BIEN FILU!";
	font.DrawText(str, Graphics::GetRect().GetCenter() - Vei2(font.GetGlyphWidth() * int(str.size()), font.GetGlyphHeight()) / 2, Colors::Yellow, gfx);
}

void TextManager::DrawLineCounter(const Font& font, const Board& brd, Graphics& gfx)
{
	font.DrawText("Lines:", { spacing, spacing }, Colors::White, gfx);
	font.DrawText(std::to_string(brd.GetClearedLineCount()), { spacing, font.GetGlyphHeight() + spacing }, Colors::White, gfx);
}

void TextManager::DrawQueueText(const Font& font, const RectI& borderRect, Graphics& gfx)
{
	const std::string str = "NEXT";
	const Vei2 pos = { borderRect.GetCenter().x - (font.GetGlyphWidth() * int(str.size())) / 2, borderRect.top - font.GetGlyphHeight() - spacing };
	font.DrawText(str, pos, Colors::Yellow, gfx);
}

void TextManager::DrawHoldText(const Font& font, const RectI& borderRect, Graphics& gfx)
{
	const std::string str = "HOLD";
	const Vei2 pos = { borderRect.GetCenter().x - (font.GetGlyphWidth() * int(str.size())) / 2, borderRect.top - font.GetGlyphHeight() - spacing };
	font.DrawText(str, pos, Colors::Yellow, gfx);
}

void TextManager::DrawPowerupText(const Font& font, const RectI& borderRect, Graphics& gfx)
{
	const std::string str = "POWERUP";
	const Vei2 pos = { borderRect.GetCenter().x - (font.GetGlyphWidth() * int(str.size())) / 2, borderRect.top - font.GetGlyphHeight() - spacing };
	font.DrawText(str, pos, Colors::Yellow, gfx);
}