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
#include "TextCodex.h"

class Game
{
private:
	enum class State
	{
		Title,
		Playing,
		GameOver
	};
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	void SpawnPiece(int shapeNum);
	void SwapHoldPiece();
	int Roll();
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
	std::unique_ptr<Piece> pPiece;
	State state = State::Title;
	std::mt19937 rng = std::mt19937(std::random_device{}());
	std::uniform_int_distribution<int> shapeDist = std::uniform_int_distribution<int>(0, Piece::GetMaxShapes() - 1);
	int curPiece;
	int nextPiece;
	int holdPiece = -1;
	/********************************/
};