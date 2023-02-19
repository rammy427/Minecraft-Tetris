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
		Quit,
		Count
	};
public:
	Controller();
	void SaveBindings();
	// Returns true if file loaded successfully.
	bool LoadBindings();
	unsigned char GetBinding(Key key) const;
private:
	std::map<Key, unsigned char> bindings;
};