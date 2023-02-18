#include "Controller.h"

Controller::Controller()
{
	bindings.emplace(Key::MoveLeft, VK_LEFT);
	bindings.emplace(Key::MoveRight, VK_RIGHT);
	bindings.emplace(Key::HardDrop, VK_UP);
	bindings.emplace(Key::SoftDrop, VK_DOWN);
	bindings.emplace(Key::RotateLeft, 'A');
	bindings.emplace(Key::RotateRight, 'D');
	bindings.emplace(Key::SwapPiece, 'Q');
	bindings.emplace(Key::UseItem, 'E');
	bindings.emplace(Key::CancelItem, VK_SHIFT);
	bindings.emplace(Key::Transition, VK_RETURN);
	bindings.emplace(Key::Pause, VK_ESCAPE);
	bindings.emplace(Key::Quit, 'Q');
}

unsigned char Controller::GetBinding(Key key) const
{
	return bindings.find(key)->second;
}