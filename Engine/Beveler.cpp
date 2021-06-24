#include "Beveler.h"

void Beveler::DrawOuterBevel(const RectI& rect, int size, Graphics& gfx) const
{
	const int left = rect.left;
	const int right = rect.right;
	const int top = rect.top;
	const int bottom = rect.bottom;

	// left side bevel (corner,side,corner)
	gfx.DrawIsoRightTriBL(left, top, size, leftColor);
	gfx.DrawRect(left, top + size, left + size, bottom - size, leftColor);
	gfx.DrawIsoRightTriUL(left, bottom - size, size, leftColor);
	// top side bevel
	gfx.DrawIsoRightTriUR(left, top, size, topColor);
	gfx.DrawRect(left + size, top, right - size, top + size, topColor);
	gfx.DrawIsoRightTriUL(right - size, top, size, topColor);
	// right side bevel
	gfx.DrawIsoRightTriBR(right - size, top, size, rightColor);
	gfx.DrawRect(right - size, top + size, right, bottom - size, rightColor);
	gfx.DrawIsoRightTriUR(right - size, bottom - size, size, rightColor);
	// bottom side bevel
	gfx.DrawIsoRightTriBR(left, bottom - size, size, bottomColor);
	gfx.DrawRect(left + size, bottom - size, right - size, bottom, bottomColor);
	gfx.DrawIsoRightTriBL(right - size, bottom - size, size, bottomColor);
}

void Beveler::DrawInnerBevel(const RectI& rect, int size, Graphics& gfx) const
{
	const int left = int(rect.left);
	const int right = int(rect.right);
	const int top = int(rect.top);
	const int bottom = int(rect.bottom);
	// left side bevel (corner,side,corner)
	gfx.DrawIsoRightTriBL(left, top, size, rightColor);
	gfx.DrawRect(left, top + size, left + size, bottom - size, rightColor);
	gfx.DrawIsoRightTriUL(left, bottom - size, size, rightColor);
	// top side bevel
	gfx.DrawIsoRightTriUR(left, top, size, bottomColor);
	gfx.DrawRect(left + size, top, right - size, top + size, bottomColor);
	gfx.DrawIsoRightTriUL(right - size, top, size, bottomColor);
	// right side bevel
	gfx.DrawIsoRightTriBR(right - size, top, size, leftColor);
	gfx.DrawRect(right - size, top + size, right, bottom - size, leftColor);
	gfx.DrawIsoRightTriUR(right - size, bottom - size, size, leftColor);
	// bottom side bevel
	gfx.DrawIsoRightTriBR(left, bottom - size, size, topColor);
	gfx.DrawRect(left + size, bottom - size, right - size, bottom, topColor);
	gfx.DrawIsoRightTriBL(right - size, bottom - size, size, topColor);
}

void Beveler::DrawBeveledBrick(const RectI& rect, int bevelSize, Graphics& gfx) const
{
	DrawOuterBevel(rect, bevelSize, gfx);
	gfx.DrawRect(rect.GetExpanded(-bevelSize), baseColor);
}

void Beveler::DrawBevelFrame(const RectI& rect, int bevelSize, Graphics& gfx) const
{
	DrawOuterBevel(rect, bevelSize, gfx);
	DrawInnerBevel(rect.GetExpanded(-bevelSize), bevelSize, gfx);
}

void Beveler::SetBaseColor(Color baseColor_in)
{
	baseColor = baseColor_in;
	leftColor = Color(
		int(float(baseColor.GetR()) * leftFactor),
		int(float(baseColor.GetG()) * leftFactor),
		int(float(baseColor.GetB()) * leftFactor));
	rightColor = Color(
		int(float(baseColor.GetR()) * rightFactor),
		int(float(baseColor.GetG()) * rightFactor),
		int(float(baseColor.GetB()) * rightFactor));
	topColor = Color(
		int(float(baseColor.GetR()) * topFactor),
		int(float(baseColor.GetG()) * topFactor),
		int(float(baseColor.GetB()) * topFactor));
	bottomColor = Color(
		int(float(baseColor.GetR()) * bottomFactor),
		int(float(baseColor.GetG()) * bottomFactor),
		int(float(baseColor.GetB()) * bottomFactor));
}