#pragma once

#include "Graphics.h"
#include "Rect.h"

class Beveler
{
public:
	Beveler() = default;
	void DrawOuterBevel(const RectI& rect, int size, Graphics& gfx, bool clear = false) const;
	void DrawInnerBevel(const RectI& rect, int size, Graphics& gfx, bool clear = false) const;
	void DrawBeveledBrick(const RectI& rect, int bevelSize, Graphics& gfx, bool clear = false) const;
	void DrawBevelFrame(const RectI& rect, int bevelSize, Graphics& gfx, bool clear = false) const;
	void SetBaseColor(Color baseColor_in);
private:
	static constexpr float leftFactor = 1.11f;
	static constexpr float topFactor = 0.92f;
	static constexpr float bottomFactor = 0.83f;
	static constexpr float rightFactor = 0.65f;
	Color baseColor;
	Color leftColor;
	Color rightColor;
	Color topColor;
	Color bottomColor;
};