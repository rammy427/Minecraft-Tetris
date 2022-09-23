#pragma once

#include "Border.h"

class Board
{
private:
	class Tile
	{
	public:
		Tile() = default;
		Tile(const RectI& rect);
		void Set();
		void Kill();
		void SetColor(Color c_in);
		void Draw(Graphics& gfx);
		void DrawGhost(Color ghostColor, Graphics& gfx);
		static int GetDimension();
		static int GetPadding();
		bool IsAlive() const;
		Color GetColor() const;
	private:
		static constexpr int dimension = 28;
		static constexpr int bevelSize = 3;
		static constexpr int padding = 1;
		bool isAlive = false;
		RectI rect = { 0, 0, 0, 0 };
		Color c;
		Beveler bev;
	};
public:
	Board(const Vei2& center);
	void SetLineGoal(int goal);
	void ClearRows();
	void Reset(bool clearLines = true);
	void Draw(Graphics& gfx);
	bool IsInsideBoard(const Vei2& gridPos) const;
	int GetWidth() const;
	int GetHeight() const;
	int GetClearedLineCount() const;
	int GetLineGoal() const;
	const RectI& GetRect() const;
	Tile& TileAt(const Vei2& gridPos);
	const Tile& TileAt(const Vei2& gridPos) const;
	Vei2 ScreenToGrid(const Vei2& screenPos) const;
private:
	// Width and height in TILES.
	static constexpr int width = 10;
	static constexpr int height = 20;
	Tile tiles[width * height];
	Vei2 topLeft;
	int nClearedLines = 0;
	int lineGoal;
	Border border;
};