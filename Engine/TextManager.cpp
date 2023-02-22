#include "TextManager.h"
#include "Score.h"

void TextManager::DrawTitleSubText(const Font& font, Graphics& gfx)
{
	const std::string str = "Press ENTER";
	const int x = (Graphics::ScreenWidth - font.GetGlyphWidth() * int(str.size())) / 2;
	const int y = (Graphics::ScreenHeight * 3 - font.GetGlyphHeight() * 2) / 4;
	font.DrawText(str, { x, y }, Colors::Yellow, gfx);
}

void TextManager::DrawGameOver(const Font& font, Graphics& gfx)
{
	const std::string str = "GAME OVER";
	font.DrawText(str, Graphics::GetRect().GetCenter() - Vei2(font.GetGlyphWidth() * int(str.size()), font.GetGlyphHeight()) / 2, Colors::Red, gfx);
}

void TextManager::DrawPaused(const Font& font, Graphics& gfx)
{
	const std::string str = "PAUSE";
	font.DrawText(str, Graphics::GetRect().GetCenter() - Vei2(font.GetGlyphWidth() * int(str.size()), font.GetGlyphHeight()) / 2, Colors::Red, gfx);
}

void TextManager::DrawVictory(const Font& font, Graphics& gfx)
{
	const std::string str = "VICTORY!";
	font.DrawText(str, Graphics::GetRect().GetCenter() - Vei2(font.GetGlyphWidth() * int(str.size()), font.GetGlyphHeight()) / 2, Colors::Yellow, gfx);
}

void TextManager::DrawReturnText(const Font& font, Graphics& gfx)
{
	const std::string str = "Press ENTER to return to the menu.";
	const int spacing = 20;
	const int x = Graphics::GetRect().GetCenter().x - (font.GetGlyphWidth() * int(str.size())) / 2;
	const int y = Graphics::ScreenHeight - font.GetGlyphHeight() - spacing;
	font.DrawText(str, { x, y }, Colors::White, gfx);
}

void TextManager::DrawMenuReturnText(const Font& font, Graphics& gfx)
{
	const std::string str = "Press ESCAPE to return to the menu.";
	const int spacing = 20;
	const int x = Graphics::GetRect().GetCenter().x - (font.GetGlyphWidth() * int(str.size())) / 2;
	const int y = Graphics::ScreenHeight - font.GetGlyphHeight() - spacing;
	font.DrawText(str, { x, y }, Colors::White, gfx);
}

void TextManager::DrawQuitText(const Font& font, Graphics& gfx)
{
	const std::string str = "Press Q to return to the menu.";
	const int spacing = 20;
	const int x = Graphics::GetRect().GetCenter().x - (font.GetGlyphWidth() * int(str.size())) / 2;
	const int y = Graphics::ScreenHeight - font.GetGlyphHeight() - spacing;
	font.DrawText(str, { x, y }, Colors::Yellow, gfx);
}

void TextManager::DrawLineCounter(const Font& font, const Board& brd, Graphics& gfx)
{
	font.DrawText("Lines:", { spacing, spacing }, Colors::White, gfx);
	font.DrawText(std::to_string(brd.GetClearedLineCount()), { spacing, font.GetGlyphHeight() + spacing }, Colors::White, gfx);
}

void TextManager::DrawGoal(const Font& font, const Board& brd, Graphics& gfx)
{
	const int x = font.GetGlyphWidth() * 9 + spacing;
	const int y = spacing;
	font.DrawText("Goal:", { x, y }, Colors::White, gfx);
	font.DrawText(std::to_string(brd.GetLineGoal()), { x, font.GetGlyphHeight() + y }, Colors::White, gfx);
}

void TextManager::DrawScore(const Font& font, const Board& brd, Graphics& gfx)
{
	const std::string str = "Score:";
	font.DrawText(str, { brd.GetRect().right + spacing * 2, spacing }, Colors::White, gfx);
	font.DrawText(std::to_string(Score::GetScore()), { brd.GetRect().right + spacing * 2, font.GetGlyphHeight() + spacing }, Colors::White, gfx);
}

void TextManager::DrawTopScore(const Font& font, const Board& brd, Graphics& gfx)
{
	const std::string str = "Top Score:";
	font.DrawText(str, { brd.GetRect().right + spacing * 15, spacing }, Colors::White, gfx);
	font.DrawText(std::to_string(Score::GetTop()), { brd.GetRect().right + spacing * 15, font.GetGlyphHeight() + spacing }, Colors::White, gfx);
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

void TextManager::DrawItemText(const Font& font, const RectI& borderRect, Graphics& gfx)
{
	const std::string str = "ITEM";
	const Vei2 pos = { borderRect.GetCenter().x - (font.GetGlyphWidth() * int(str.size())) / 2, borderRect.top - font.GetGlyphHeight() - spacing };
	font.DrawText(str, pos, Colors::Yellow, gfx);
}