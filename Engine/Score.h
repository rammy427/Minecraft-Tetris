#pragma once

class Score
{
public:
	static void Add(int n);
	static void LoadTop();
	static void SaveTop();
	static void Reset();
	static int GetScore();
	static int GetTop();
private:
	static int score;
	static int top;
};