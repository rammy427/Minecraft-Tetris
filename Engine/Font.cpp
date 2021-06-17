#include "Font.h"
#include <cassert>
#include "SpriteEffect.h"

Font::Font(const std::string& filename, Color chroma)
	:
	surface(filename),
	chroma(chroma),
	glyphWidth(surface.GetWidth() / nColumns),
	glyphHeight(surface.GetHeight() / nRows)
{
	assert(glyphWidth * nColumns == surface.GetWidth());
	assert(glyphHeight * nRows == surface.GetHeight());
}

void Font::DrawText(const std::string& text, const Vei2& pos, Color color, Graphics& gfx) const
{
	Vei2 curPos = pos;
	for (char c : text)
	{
		if (c == '\n')
		{
			curPos.y += glyphHeight;
			curPos.x = pos.x;
			continue;
		}
		else if (c >= firstChar + 1 && c <= lastChar)
		{
			gfx.DrawSprite(curPos.x, curPos.y, MapGlyphRect(c), surface, SpriteEffect::SmartSubstitution{ chroma,color });
		}
		curPos.x += glyphWidth;
	}
}

int Font::GetGlyphWidth() const
{
	return glyphWidth;
}

int Font::GetGlyphHeight() const
{
	return glyphHeight;
}

RectI Font::MapGlyphRect(char c) const
{
	assert(c >= firstChar && c <= lastChar);
	const int glyphIndex = c - ' ';
	const int yGlyph = glyphIndex / nColumns;
	const int xGlyph = glyphIndex % nColumns;
	return { { xGlyph * glyphWidth, yGlyph * glyphHeight }, glyphWidth, glyphHeight };
}