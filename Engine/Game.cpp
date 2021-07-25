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
#include "SpriteEffect.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	brd({ int(Graphics::GetRect().GetCenter().x / 1.1875f), Graphics::GetRect().GetCenter().y }),
	queueBorder({ { (Graphics::ScreenWidth + brd.GetRect().right - maxPreviewWidth) / 2, consola.GetGlyphHeight() + 30 }, maxPreviewWidth, maxPreviewHeight }, 10),
	holdBorder({ { (brd.GetRect().left - maxPreviewWidth) / 2, consola.GetGlyphHeight() * 4 + 30 }, maxPreviewWidth, maxPreviewHeight }, 10),
	queuePreview(maxPreviewWidth, maxPreviewHeight),
	holdPreview(maxPreviewWidth, maxPreviewHeight)
{
	ShuffleBoardBGM();
	nNextPiece = shapeDist(rng);
	SpawnPiece(Roll());
}

void Game::Go()
{
	gfx.BeginFrame();
	float elapsedTime = ft.Mark();
	while (elapsedTime > .0f)
	{
		const float dt = std::min(.0025f, elapsedTime);
		UpdateModel(dt);
		elapsedTime -= dt;
	}
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel(float dt)
{
	if (state == State::Playing)
	{
		while (!wnd.kbd.KeyIsEmpty())
		{
			const Keyboard::Event e = wnd.kbd.ReadKey();
			if (e.IsPress())
			{
				const unsigned char charCode = e.GetCode();
				if (charCode == 'Q')
				{
					wnd.kbd.DisableAutorepeat();
					SwapHoldPiece();
				}
				else
				{
					pPiece->ProcessTransformations(wnd.kbd, charCode);
				}
			}
		}

		pPiece->UpdateDrop(wnd.kbd, dt);
		brd.ClearRows();

		if (GameIsWon())
		{
			state = State::Victory;
		}

		if (pPiece->IsBinded())
		{
			SpawnPiece(Roll());
		}
		if (pPiece->IsColliding())
		{
			boardBgm.StopAll();
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
					boardBgm.Play();
					state = State::Playing;
					break;
				case State::Victory:
				case State::GameOver:
					brd.Reset();
					nHoldPiece = -1;
					SpawnPiece(Roll());
					ShuffleBoardBGM();
					state = State::Title;
					break;
				}
			}
		}
	}
}

void Game::SpawnPiece(int nShape)
{
	pPiece = std::make_unique<Piece>(nShape, Vei2(brd.GetWidth() / 2, 0), brd);
	holdIsLocked = false;
}

void Game::SwapHoldPiece()
{
	if (nHoldPiece == -1)
	{
		nHoldPiece = nCurPiece;
		SpawnPiece(Roll());
		holdIsLocked = true;
	}
	else if (!holdIsLocked && nCurPiece != nHoldPiece)
	{
		std::swap(nHoldPiece, nCurPiece);
		SpawnPiece(nCurPiece);
		holdIsLocked = true;
	}
}

void Game::DrawQueuePreview()
{
	queueBorder.Draw(gfx);
	queuePreview = "Sprites\\preview" + std::to_string(nNextPiece) + ".bmp";
	const Vei2 pos = queueBorder.GetInnerBounds().GetCenter() - Vei2(queuePreview.GetWidth(), queuePreview.GetHeight()) / 2;
	gfx.DrawSprite(pos.x, pos.y, queuePreview, SpriteEffect::Chroma{});
	TextManager::DrawQueueText(consola, queueBorder.GetInnerBounds(), gfx);
}

void Game::DrawHoldPreview()
{
	holdBorder.Draw(gfx);
	if (nHoldPiece != -1)
	{
		holdPreview = "Sprites\\preview" + std::to_string(nHoldPiece) + ".bmp";
		const Vei2 pos = holdBorder.GetInnerBounds().GetCenter() - Vei2(holdPreview.GetWidth(), holdPreview.GetHeight()) / 2;
		gfx.DrawSprite(pos.x, pos.y, holdPreview, SpriteEffect::Chroma{});
	}
	TextManager::DrawHoldText(consola, holdBorder.GetInnerBounds(), gfx);
}

int Game::Roll()
{
	// Prepares next piece in queue, but returns CURRENT piece to be spawned.
	nCurPiece = nNextPiece;
	nNextPiece = shapeDist(rng);
	return nCurPiece;
}

bool Game::GameIsWon()
{
	return brd.GetClearedLineCount() >= lineWinThreshold;
}

void Game::ShuffleBoardBGM()
{
	boardBgm = { L"Music\\play" + std::to_wstring(bgmDist(rng)) + L".wav", true };
}

void Game::ComposeFrame()
{
	switch (state)
	{
	case State::Title:
		gfx.DrawSprite(0, 0, background, SpriteEffect::Copy{});
		TextManager::DrawTitle(consolab, gfx);
		break;
	case State::Playing:
		gfx.DrawSprite(0, 0, background, SpriteEffect::Copy{});
		brd.Draw(gfx);
		pPiece->Draw(gfx);
		DrawQueuePreview();
		DrawHoldPreview();
		TextManager::DrawLineCounter(consola, brd, gfx);
		break;
	case State::GameOver:
		gfx.DrawSprite(0, 0, background, SpriteEffect::Copy{});
		brd.Draw(gfx);
		TextManager::DrawGameOver(consolab, gfx);
		break;
	case State::Victory:
		gfx.DrawSprite(0, 0, background, SpriteEffect::Copy{});
		TextManager::DrawLineCounter(consola, brd, gfx);
		TextManager::DrawVictory(consolab, gfx);
		break;
	}
}