#pragma once

#include <string>
#include <map>
#include "ChiliWin.h"
#include "Keyboard.h"

class Controller
{
public:
	enum class Key
	{
		MoveLeft,
		MoveRight,
		HardDrop,
		SoftDrop,
		RotateLeft,
		RotateRight,
		SwapPiece,
		UseItem,
		CancelItem,
		Pause,
		Count
	};
public:
	Controller();
	void SetBindings(const std::vector<unsigned char>& keys);
	void SaveBindings();
	// Returns true if file loaded successfully.
	bool LoadBindings();
	unsigned char GetBinding(Key key) const;
private:
	const std::vector<unsigned char> defaults =
	{
		VK_LEFT,
		VK_RIGHT,
		VK_UP,
		VK_DOWN,
		'A',
		'D',
		'Q',
		'E',
		VK_SHIFT,
		VK_ESCAPE
	};
	std::map<Key, unsigned char> bindings;
};