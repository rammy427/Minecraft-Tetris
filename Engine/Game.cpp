/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
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
#include "Game.h"
#include "MainWindow.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	brd({ int(Graphics::GetRect().GetCenter().x / 1.1875f), Graphics::GetRect().GetCenter().y }),
	nextPiece({ brd.GetRect().right + QueuedPiece::GetSpriteWidth() * 2, brd.GetRect().top + QueuedPiece::GetSpriteHeight() / 2 + consola.GetGlyphHeight() + 10 })
{
	nextPiece.Roll();
	SpawnBrick();
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (state == State::Playing)
	{
		const float dt = ft.Mark();
		pPiece->ProcessTransformations(wnd.kbd, dt);
		brd.ClearRows();

		if (pPiece->IsBinded())
		{
			SpawnBrick();
		}
		if (pPiece->IsColliding())
		{
			state = State::GameOver;
		}
	}
	else
	{
		while (!wnd.kbd.KeyIsEmpty())
		{
			const Keyboard::Event e = wnd.kbd.ReadKey();
			if (e.IsPress() && e.GetCode() == VK_RETURN)
			{
				switch (state)
				{
				case State::Title:
					state = State::Playing;
					break;
				case State::GameOver:
					brd.Reset();
					state = State::Title;
					break;
				}
			}
		}
	}
}

void Game::SpawnBrick()
{
	pPiece = std::make_unique<Piece>(nextPiece.GetNumber(), Vei2(brd.GetWidth() / 2, 0), brd);
	nextPiece.Roll();
}

void Game::ComposeFrame()
{
	switch (state)
	{
	case State::Title:
		brd.Draw(gfx);
		TextCodex::DrawTitle(consolab, gfx);
		break;
	case State::Playing:
		brd.Draw(gfx);
		pPiece->Draw(gfx);
		nextPiece.Draw(gfx);
		TextCodex::DrawNextPieceText(consola, nextPiece, gfx);
		TextCodex::DrawLineCounter(consola, brd, gfx);
		break;
	case State::GameOver:
		brd.Draw(gfx);
		TextCodex::DrawGameOver(consolab, gfx);
		break;
	}
}