#pragma once

#include "Beveler.h"

class Border
{
public:
	Border(RectI innerBounds);
	void Draw(Graphics& gfx);
	const RectI& GetInnerBounds() const;
private:
	Beveler bev;
	RectI innerBounds;
	static constexpr int thickness = 6;
	static constexpr Color color = { 0,0,230 }; // Blue
};