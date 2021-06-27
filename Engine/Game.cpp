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
#include "Brick.h"
#include "Game.h"
#include "MainWindow.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	brd({ int(Graphics::GetRect().GetCenter().x / 1.1875f), Graphics::GetRect().GetCenter().y }),
	nextBrick({ int(Graphics::GetRect().right - QueuedBrick::GetSpriteWidth() * 2), Graphics::GetRect().GetCenter().y })
{
	nextBrick.Roll();
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
		pBrick->ProcessTransformations(wnd.kbd, dt);
		brd.ClearRows();

		if (pBrick->IsBinded())
		{
			SpawnBrick();
		}
		if (pBrick->IsColliding())
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
	pBrick = std::make_unique<Brick>(nextBrick.GetNumber(), Vei2(brd.GetWidth() / 2, 0), brd);
	nextBrick.Roll();
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
		pBrick->Draw(gfx);
		nextBrick.Draw(gfx);
		TextCodex::DrawNextBrickText(consola, nextBrick, gfx);
		TextCodex::DrawLineCounter(consola, brd, gfx);
		break;
	case State::GameOver:
		brd.Draw(gfx);
		TextCodex::DrawGameOver(consolab, gfx);
		break;
	}
}