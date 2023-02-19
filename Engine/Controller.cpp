#include "Controller.h"
#include <fstream>

Controller::Controller()
{
	if (!LoadBindings())
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
		SaveBindings();
	}
}

void Controller::SaveBindings()
{
	std::ofstream out("bindings.txt");
	for (int i = 0; i < int(Key::Count); i++)
	{
		out.write(reinterpret_cast<char*>(&i), sizeof(i));
		out.put(bindings[Key(i)]);

		// Add new line to separate entries. These will be skipped when reading.
		out.put('\n');
	}
}

bool Controller::LoadBindings()
{
	std::ifstream in("bindings.txt");
	if (!in) return false;
	for (int i = 0; i < int(Key::Count); i++)
	{
		unsigned char binding;
		in.seekg(sizeof(i), std::ios::cur);
		in.read(reinterpret_cast<char*>(&binding), sizeof(binding));
		bindings[Key(i)] = binding;

		// Skip new lines (carriage return + line feed).
		in.seekg(2, std::ios::cur);
	}
	return true;
}

unsigned char Controller::GetBinding(Key key) const
{
	return bindings.find(key)->second;
}