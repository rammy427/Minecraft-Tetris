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
		void Set();
		void SetColor(Color c_in);
		void Draw(Graphics& gfx);
		void DrawGhost(Color ghostColor, Graphics& gfx);
		static int GetDimension();
		bool IsAlive() const;
	private:
		static constexpr int dimension = 30;
		static constexpr int bevelSize = 3;
		static constexpr int padding = 1;
		bool isAlive = false;
		RectI rect = { 0, 0, 0, 0 };
		Color c;
		Beveler bev;
	};
public:
	Board(const Vei2& center);
	void SetTile(const Vei2& gridPos, Color c = { 230, 230, 230 });
	void Draw(Graphics& gfx);
	void DrawGhostCell(const Vei2& gridPos, Color ghostColor, Graphics& gfx);
	bool TileIsAlive(const Vei2& gridPos) const;
	bool IsInsideBoard(const Vei2& gridPos) const;
	int GetWidth() const;
	int GetHeight() const;
private:
	Tile& TileAt(const Vei2& gridPos);
	const Tile& TileAt(const Vei2& gridPos) const;
private:
	static constexpr int width = 10;
	static constexpr int height = 18;
	Tile tiles[width * height];
	Vei2 topLeft;
};