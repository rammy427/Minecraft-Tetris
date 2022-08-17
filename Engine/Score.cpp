#include "Score.h"
#include <fstream>

void Score::Add(int n)
{
	score += n;
}

void Score::LoadTop()
{
	std::ifstream curTop("score.dat", std::ios::binary);
	if (curTop)
	{
		curTop.read(reinterpret_cast<char*>(&top), sizeof(top));
	}
}

void Score::SaveTop()
{
	if (score > top)
	{
		std::ofstream newTop("score.dat", std::ios::binary);
		newTop.write(reinterpret_cast<char*>(&score), sizeof(score));
	}
}

void Score::Reset()
{
	score = 0;
}

int Score::GetScore()
{
	return score;
}

int Score::GetTop()
{
	return top;
}

int Score::score = 0;
int Score::top = 0;