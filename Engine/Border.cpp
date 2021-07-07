#include "Border.h"

Border::Border(RectI innerBounds)
	:
	innerBounds(innerBounds)
{
	assert(thickness % 2 == 0);
	assert(innerBounds.GetExpanded(thickness).IsContainedBy(Graphics::GetRect()));
	bev.SetBaseColor(color);
}

void Border::Draw(Graphics& gfx)
{
	bev.DrawBevelFrame(innerBounds.GetExpanded(thickness), thickness / 2, gfx);
}

const RectI& Border::GetInnerBounds() const
{
	return innerBounds;
}