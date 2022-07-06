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
#include "Powerup.h"

class Game
{
private:
	enum class State
	{
		Title,
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
	void SwapHoldPiece();
	void DrawQueuePreview();
	void DrawHoldPreview();
	void ResetGame();
	void SpawnPowerup();
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
	State state = State::Title;
	std::mt19937 rng = std::mt19937(std::random_device{}());
	std::uniform_int_distribution<int> shapeDist = std::uniform_int_distribution<int>(0, Piece::GetMaxShapes() - 1);
	int nCurPiece;
	int nNextPiece;
	int nHoldPiece = -1;
	bool holdIsLocked = false;
	static constexpr int lineWinThreshold = 120;
	// Preview sprite members.
	static constexpr int maxPreviewWidth = 80;
	static constexpr int maxPreviewHeight = 40;
	Border queueBorder;
	Border holdBorder;
	Surface queuePreview;
	Surface holdPreview;
	// Other sprites.
	Surface background = "Sprites\\bg.bmp";
	// Sound members.
	std::uniform_int_distribution<int> bgmDist = std::uniform_int_distribution<int>(0, 9);
	Sound boardBgm;
	std::unique_ptr<Powerup> pPowerup;
	/********************************/
};