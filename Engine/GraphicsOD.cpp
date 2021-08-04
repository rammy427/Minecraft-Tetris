#define GOD_GRAPHICS
#include "Graphics.h"

void Graphics::BeginFrame()
{
	// clear the sysbuffer
	memset(pSysBuffer, 0u, sizeof(Color) * Graphics::ScreenHeight * Graphics::ScreenWidth);
}

void Graphics::PutPixel(int x, int y, Color c)
{
	assert(x >= 0);
	assert(x < int(Graphics::ScreenWidth));
	assert(y >= 0);
	assert(y < int(Graphics::ScreenHeight));
	pSysBuffer[Graphics::ScreenWidth * y + x] = c;
}

Color Graphics::GetPixel(int x, int y) const
{
	return pSysBuffer[y * ScreenWidth + x];
}

void dummy(Graphics& gfx)
{
	gfx.DrawSprite(0, 0, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, {}, SpriteEffect::Copy{});
	gfx.DrawSprite(0, 0, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, {}, SpriteEffect::Chroma{Colors::Black});
	gfx.DrawSprite(0, 0, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, {}, SpriteEffect::SmartSubstitution{Colors::Black, Colors::Black});
}