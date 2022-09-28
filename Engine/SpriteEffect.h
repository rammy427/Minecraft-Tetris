#pragma once

#include "Colors.h"
#include "Graphics.h"

namespace SpriteEffect
{
	class Chroma
	{
	public:
		Chroma(Color chroma = Colors::Magenta)
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
					unsigned char(sub.GetR() * (src.GetR() + 1)),
					unsigned char(sub.GetG() * (src.GetG() + 1)),
					unsigned char(sub.GetB() * (src.GetB() + 1))
				};
				gfx.PutPixel(xDest, yDest, newColor);
			}
		}
	private:
		Color chroma = Colors::Magenta;
		Color sub;
	};
	class Copy
	{
	public:
		void operator()(Color cSrc, int xDest, int yDest, Graphics& gfx) const
		{
			gfx.PutPixel(xDest, yDest, cSrc);
		}
	};
}