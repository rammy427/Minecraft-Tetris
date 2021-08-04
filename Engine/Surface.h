#pragma once

#include <string>
#include <vector>
#include "Colors.h"
#include "Rect.h"

class Surface
{
public:
	Surface( const std::string& filename );
	Surface( int width,int height );
	Surface() = default;
	void PutPixel( int x,int y,Color c );
	Color GetPixel( int x,int y ) const;
	int GetWidth() const;
	int GetHeight() const;
	RectI GetRect() const;
	void Fill(Color c);
	const Color* Data() const;
private:
	std::vector<Color> pixels;
	int width;
	int height;
};