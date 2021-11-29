#include "Border.h"

Border::Border(RectI innerBounds, int offset)
	:
	innerBounds(innerBounds.GetExpanded(offset))
{
	assert(thickness % 2 == 0);
	assert(innerBounds.GetExpanded(thickness).IsContainedBy(Graphics::GetRect()));
	bev.SetBaseColor(color);
}

void Border::Draw(Graphics& gfx) const
{
	bev.DrawBevelFrame(innerBounds.GetExpanded(thickness), thickness / 2, gfx);
}

const RectI& Border::GetInnerBounds() const
{
	return innerBounds;
}