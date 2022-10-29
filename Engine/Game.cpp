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
#include "Score.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	brd({ int(Graphics::GetRect().GetCenter().x / 1.1875f), Graphics::GetRect().GetCenter().y }),
	queueBorder({ { (Graphics::ScreenWidth + brd.GetRect().right - maxPreviewWidth) / 2, consola.GetGlyphHeight() * 4 + 30 }, maxPreviewWidth, maxPreviewHeight }, 10),
	holdBorder({ { (brd.GetRect().left - maxPreviewWidth) / 2, consola.GetGlyphHeight() * 4 + 30 }, maxPreviewWidth, maxPreviewHeight }, 10),
	queuePreview(maxPreviewWidth, maxPreviewHeight),
	holdPreview(maxPreviewWidth, maxPreviewHeight),
	menu(Graphics::GetRect().GetCenter(), consola)
{
	ShuffleBoardBGM();
	nNextPiece = shapeDist(rng);
	SpawnPiece(RollPiece());
	GenerateItem();
	Score::LoadTop();
	titleBgm.Play();
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
				switch (charCode)
				{
				case VK_ESCAPE:
					state = State::Paused;
					wnd.kbd.DisableAutorepeat();
					break;
				case 'Q':
					wnd.kbd.DisableAutorepeat();
					SwapHoldPiece();
					break;
				case 'E':
					pItem->Activate();
					break;
				case VK_SHIFT:
					pItem->EndUse();
					break;
				default:
					piece.ProcessTransformations(wnd.kbd, charCode);
					break;
				}
			}
		}

		piece.UpdateDrop(wnd.kbd, dt);
		pItem->Update(dt);
		brd.ClearRows();

		if (pItem->HasEnded())
		{
			GenerateItem();
		}
		if (GameIsWon())
		{
			boardBgm.StopAll();
			victoryBgm.Play();
			Score::SaveTop();
			Score::LoadTop();
			state = State::Victory;
		}
		if (piece.IsLocked())
		{
			sndLock.Play();
			SpawnPiece(RollPiece());
		}
		if (piece.IsColliding())
		{
			piece.Cut();
			piece.LockToBoard();
			boardBgm.StopAll();
			Score::SaveTop();
			Score::LoadTop();
			state = State::GameOver;
			sndGameOver.Play();
		}
	}
	else if (state == State::Paused)
	{
		while (!wnd.kbd.KeyIsEmpty())
		{
			const Keyboard::Event e = wnd.kbd.ReadKey();
			if (e.IsPress() && e.GetCode() == VK_ESCAPE)
			{
				state = State::Playing;
				wnd.kbd.DisableAutorepeat();
			}
		}
	}
	else if (state == State::Menu)
	{
		menu.Update(wnd.kbd, wnd.mouse);
		if (menu.IsSelecting())
		{
			while (!wnd.kbd.KeyIsEmpty())
			{
				const Keyboard::Event e = wnd.kbd.ReadKey();
				if (e.IsPress() && e.GetCode() == VK_RETURN)
				{
					titleBgm.StopAll();
					ResetGame();
					boardBgm.Play();
					state = State::Playing;
				}
			}
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
					state = State::Menu;
					break;
				case State::Victory:
					victoryBgm.StopAll();
				case State::GameOver:
					sndGameOver.StopAll();
					titleBgm.Play();
					state = State::Title;
					break;
				}
			}
		}
	}

	wnd.kbd.Flush();
	wnd.mouse.Flush();
}

void Game::SpawnPiece(int nShape)
{
	piece = { nShape, Vei2(brd.GetWidth() / 2, 0), brd };
	holdIsLocked = false;
}

void Game::SpawnItem(int nItem)
{
	const Vei2 topLeft = { (Graphics::ScreenWidth + brd.GetRect().right - 64) / 2, brd.GetRect().bottom - 74 };
	switch (nItem)
	{
	case 0:
		pItem = std::make_unique<Star>(topLeft, brd, wnd.mouse, piece, sndUse, sndStar);
		break;
	case 1:
		pItem = std::make_unique<Bomb>(topLeft, brd, wnd.mouse, piece, sndUse, sndBomb);
		break;
	case 2:
		pItem = std::make_unique<Sand>(topLeft, brd, wnd.mouse, piece, sndUse, sndSand);
		break;
	case 3:
		pItem = std::make_unique<Potion>(topLeft, brd, wnd.mouse, piece, sndUse, sndPotion);
		break;
	case 4:
		pItem = std::make_unique<Pickaxe>(topLeft, brd, wnd.mouse, piece, sndUse, sndPickaxe);
		break;
	}
}

void Game::GenerateItem()
{
	const int chance = itemDist(rng);
	for (int i = 0; i < 5; i++)
	{
		if (chance >= rareItemProb + std::max(i - 1, 0) * commonItemProb + std::min(i, 1) &&
			chance <= rareItemProb + i * commonItemProb)
		{
			SpawnItem(i);
		}
	}
}

void Game::SwapHoldPiece()
{
	if (nHoldPiece == -1)
	{
		nHoldPiece = nCurPiece;
		SpawnPiece(RollPiece());
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

void Game::ResetGame()
{
	brd.Reset();
	brd.SetLineGoal(menu.GetGoalEntry().GetSelection());
	nHoldPiece = -1;
	Piece::ResetStaticData(menu.GetSpeedEntry().GetSelection());
	SpawnPiece(RollPiece());
	GenerateItem();
	ShuffleBoardBGM();
	Score::Reset();
}

int Game::RollPiece()
{
	// Prepares next piece in queue, but returns CURRENT piece to be spawned.
	nCurPiece = nNextPiece;
	nNextPiece = shapeDist(rng);
	return nCurPiece;
}

bool Game::GameIsWon()
{
	return brd.GetClearedLineCount() >= brd.GetLineGoal();
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
		gfx.DrawSprite(0, 0, title, SpriteEffect::Copy{});
		TextManager::DrawTitleSubText(consolab, gfx);
		TextManager::DrawTopScore(consola, brd, gfx);
		break;
	case State::Menu:
		if (menu.IsSelecting())
		{
			gfx.DrawSprite(0, 0, background, SpriteEffect::Copy{});
			TextManager::DrawTitleSubText(consolab, gfx);
		}
		menu.Draw(gfx);
		TextManager::DrawTopScore(consola, brd, gfx);
		break;
	case State::Playing:
		gfx.DrawSprite(0, 0, background, SpriteEffect::Copy{});
		brd.Draw(gfx);
		piece.Draw(gfx);
		DrawQueuePreview();
		DrawHoldPreview();
		TextManager::DrawLineCounter(consola, brd, gfx);
		TextManager::DrawGoal(consola, brd, gfx);
		TextManager::DrawScore(consola, brd, gfx);
		TextManager::DrawTopScore(consola, brd, gfx);
		pItem->Draw(consola, gfx);
		break;
	case State::Paused:
		gfx.DrawSprite(0, 0, background, SpriteEffect::Copy{});
		brd.Draw(gfx);
		piece.Draw(gfx);
		DrawQueuePreview();
		DrawHoldPreview();
		TextManager::DrawLineCounter(consola, brd, gfx);
		TextManager::DrawGoal(consola, brd, gfx);
		TextManager::DrawScore(consola, brd, gfx);
		TextManager::DrawTopScore(consola, brd, gfx);
		pItem->Draw(consola, gfx);
		TextManager::DrawPaused(consolab, gfx);
		break;
	case State::GameOver:
		gfx.DrawSprite(0, 0, background, SpriteEffect::Copy{});
		brd.Draw(gfx);
		TextManager::DrawLineCounter(consola, brd, gfx);
		TextManager::DrawGoal(consola, brd, gfx);
		TextManager::DrawScore(consola, brd, gfx);
		TextManager::DrawTopScore(consola, brd, gfx);
		TextManager::DrawGameOver(consolab, gfx);
		TextManager::DrawReturnText(consola, gfx);
		break;
	case State::Victory:
		gfx.DrawSprite(0, 0, background, SpriteEffect::Copy{});
		TextManager::DrawLineCounter(consola, brd, gfx);
		TextManager::DrawGoal(consola, brd, gfx);
		TextManager::DrawScore(consola, brd, gfx);
		TextManager::DrawTopScore(consola, brd, gfx);
		TextManager::DrawVictory(consolab, gfx);
		TextManager::DrawReturnText(consola, gfx);
		break;
	}
}