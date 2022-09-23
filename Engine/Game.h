/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#pragma once

#include <memory>
#include <random>
#include "FrameTimer.h"
#include "Graphics.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Piece.h"
#include "Sound.h"
#include "Item.h"
#include "Menu.h"

class Game
{
private:
	enum class State
	{
		Title,
		Menu,
		Playing,
		Paused,
		GameOver,
		Victory
	};
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel(float dt);
	/********************************/
	/*  User Functions              */
	void SpawnPiece(int nShape);
	void SpawnItem(int nItem); // nItem = 0 -> Rare, 1+ -> Common
	void GenerateItem();
	void SwapHoldPiece();
	void DrawQueuePreview();
	void DrawHoldPreview();
	void ResetGame();
	int RollPiece();
	bool GameIsWon();
	// Sound functions.
	void ShuffleBoardBGM();
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	const Font consola = "Fonts\\Consolas11x21.bmp";
	const Font consolab = "Fonts\\ConsolasBold43x77.bmp";
	FrameTimer ft;
	Board brd;
	Piece piece = { 0, { 0,0 }, brd };
	Menu menu;
	State state = State::Title;
	std::mt19937 rng = std::mt19937(std::random_device{}());
	std::uniform_int_distribution<int> shapeDist = std::uniform_int_distribution<int>(0, Piece::GetMaxShapes() - 1);
	int nCurPiece;
	int nNextPiece;
	int nHoldPiece = -1;
	bool holdIsLocked = false;
	// Preview sprite members.
	static constexpr int maxPreviewWidth = 80;
	static constexpr int maxPreviewHeight = 40;
	Border queueBorder;
	Border holdBorder;
	Surface queuePreview;
	Surface holdPreview;
	// Other sprites.
	Surface background = "Sprites\\bg.bmp";
	Surface title = "Sprites\\title.bmp";
	// Sound members.
	static constexpr int nSongs = 10;
	std::uniform_int_distribution<int> bgmDist = std::uniform_int_distribution<int>(0, nSongs - 1);
	Sound boardBgm;
	// Item management members.
	std::unique_ptr<Item> pItem;
	static constexpr int rareItemProb = 1;		// Rare:	1/25 =  4% Spawn Rate
	static constexpr int commonItemProb = 6;	// Common:	6/25 = 24% Spawn Rate
	std::uniform_int_distribution<int> itemDist = std::uniform_int_distribution<int>(1, 25);
	/********************************/
};