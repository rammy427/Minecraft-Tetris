#pragma once

#include "Beveler.h"

class Board
{
private:
	class Tile
	{
	public:
		Tile() = default;
		Tile(const RectI& rect);
		void SetColor(Color c);
		void Draw(Graphics& gfx) const;
		static int GetDimension();
	private:
		static constexpr int dimension = 30;
		static constexpr int bevelSize = 3;
		static constexpr int padding = 1;
		bool isAlive = false;
		RectI rect = { 0, 0, 0, 0 };
		Color c = { 230,230,230 };
		Beveler bev;
	};
public:
	Board(const Vei2& center);
	void Draw(Graphics& gfx) const;
private:
	Tile& TileAt(const Vei2& gridPos);
private:
	static constexpr int width = 10;
	static constexpr int height = 18;
	Tile tiles[width * height];
	Vei2 topLeft;
};