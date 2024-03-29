#pragma once

#include "Beveler.h"

class Border
{
public:
	Border(RectI innerBounds, int offset = 0);
	void Draw(Graphics& gfx) const;
	const RectI& GetInnerBounds() const;
	static const Color GetColor();
private:
	Beveler bev;
	RectI innerBounds;
	static constexpr int thickness = 6;
	static constexpr Color color = { 114,114,38 }; // Dark Yellow
};