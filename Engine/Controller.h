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
		Transition,
		Pause,
		Quit
	};
public:
	Controller();
	unsigned char GetBinding(Key key) const;
private:
	std::map<Key, unsigned char> bindings;
};