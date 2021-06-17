#pragma once

#include "Surface.h"
#include "Graphics.h"

class Font
{
public:
	Font(const std::string& filename, Color chroma = Colors::White);
	void DrawText(const std::string& text, const Vei2& pos, Color color, Graphics& gfx) const;
	int GetGlyphWidth() const;
	int GetGlyphHeight() const;
private:
	RectI MapGlyphRect(char c) const;
private:
	Surface surface;
	Color chroma;
	int glyphWidth;
	int glyphHeight;
	static constexpr int nColumns = 32;
	static constexpr int nRows = 3;
	static constexpr char firstChar = ' ';
	static constexpr char lastChar = '~';
};