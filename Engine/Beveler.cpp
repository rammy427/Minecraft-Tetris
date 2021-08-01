#include "Beveler.h"

void Beveler::DrawOuterBevel(const RectI& rect, int size, Graphics& gfx, bool clear) const
{
	const int left = rect.left;
	const int right = rect.right;
	const int top = rect.top;
	const int bottom = rect.bottom;

	// left side bevel (corner,side,corner)
	gfx.DrawIsoRightTriBL(left, top, size, leftColor, clear);
	gfx.DrawRect(left, top + size, left + size, bottom - size, leftColor, clear);
	gfx.DrawIsoRightTriUL(left, bottom - size, size, leftColor, clear);
	// top side bevel
	gfx.DrawIsoRightTriUR(left, top, size, topColor, clear);
	gfx.DrawRect(left + size, top, right - size, top + size, topColor, clear);
	gfx.DrawIsoRightTriUL(right - size, top, size, topColor, clear);
	// right side bevel
	gfx.DrawIsoRightTriBR(right - size, top, size, rightColor, clear);
	gfx.DrawRect(right - size, top + size, right, bottom - size, rightColor, clear);
	gfx.DrawIsoRightTriUR(right - size, bottom - size, size, rightColor, clear);
	// bottom side bevel
	gfx.DrawIsoRightTriBR(left, bottom - size, size, bottomColor, clear);
	gfx.DrawRect(left + size, bottom - size, right - size, bottom, bottomColor, clear);
	gfx.DrawIsoRightTriBL(right - size, bottom - size, size, bottomColor, clear);
}

void Beveler::DrawInnerBevel(const RectI& rect, int size, Graphics& gfx, bool clear) const
{
	const int left = int(rect.left);
	const int right = int(rect.right);
	const int top = int(rect.top);
	const int bottom = int(rect.bottom);
	// left side bevel (corner,side,corner)
	gfx.DrawIsoRightTriBL(left, top, size, rightColor, clear);
	gfx.DrawRect(left, top + size, left + size, bottom - size, rightColor, clear);
	gfx.DrawIsoRightTriUL(left, bottom - size, size, rightColor, clear);
	// top side bevel
	gfx.DrawIsoRightTriUR(left, top, size, bottomColor, clear);
	gfx.DrawRect(left + size, top, right - size, top + size, bottomColor, clear);
	gfx.DrawIsoRightTriUL(right - size, top, size, bottomColor, clear);
	// right side bevel
	gfx.DrawIsoRightTriBR(right - size, top, size, leftColor, clear);
	gfx.DrawRect(right - size, top + size, right, bottom - size, leftColor, clear);
	gfx.DrawIsoRightTriUR(right - size, bottom - size, size, leftColor, clear);
	// bottom side bevel
	gfx.DrawIsoRightTriBR(left, bottom - size, size, topColor, clear);
	gfx.DrawRect(left + size, bottom - size, right - size, bottom, topColor, clear);
	gfx.DrawIsoRightTriBL(right - size, bottom - size, size, topColor, clear);
}

void Beveler::DrawBeveledBrick(const RectI& rect, int bevelSize, Graphics& gfx, bool clear) const
{
	DrawOuterBevel(rect, bevelSize, gfx, clear);
	gfx.DrawRect(rect.GetExpanded(-bevelSize), baseColor, clear);
}

void Beveler::DrawBevelFrame(const RectI& rect, int bevelSize, Graphics& gfx, bool clear) const
{
	DrawOuterBevel(rect, bevelSize, gfx, clear);
	DrawInnerBevel(rect.GetExpanded(-bevelSize), bevelSize, gfx, clear);
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