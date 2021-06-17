#pragma once

#include "Colors.h"
#include "Graphics.h"

namespace SpriteEffect
{
	class Chroma
	{
	public:
		Chroma(Color chroma)
			:
			chroma(chroma)
		{
		}
		void operator()(Color src, int xDest, int yDest, Graphics& gfx)
		{
			if (src != chroma)
			{
				gfx.PutPixel(xDest, yDest, src);
			}
		}
	private:
		Color chroma = Colors::Magenta;
	};
	class SmartSubstitution
	{
	public:
		SmartSubstitution(Color chroma, Color sub)
			:
			chroma(chroma),
			sub(sub)
		{
		}
		void operator()(Color src, int xDest, int yDest, Graphics& gfx)
		{
			if (src != chroma)
			{
				const Color newColor = {
					unsigned char(((255 - float(src.GetR())) / 255) * sub.GetR()),
					unsigned char(((255 - float(src.GetG())) / 255) * sub.GetG()),
					unsigned char(((255 - float(src.GetB())) / 255) * sub.GetB())
				};
				gfx.PutPixel(xDest, yDest, newColor);
			}
		}
	private:
		Color chroma = Colors::Magenta;
		Color sub;
	};
}