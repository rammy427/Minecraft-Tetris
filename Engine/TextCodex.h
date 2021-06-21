#pragma once

#include "Font.h"

class TextCodex
{
public:
	static void DrawTitle(const Font& font, Graphics& gfx);
	static void DrawGameOver(const Font& font, Graphics& gfx);
};