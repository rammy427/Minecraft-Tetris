#include "Controller.h"
#include <fstream>

Controller::Controller()
{
	if (!LoadBindings())
	{
		SetBindings(defaults);
		SaveBindings();
	}
}

void Controller::SetBindings(const std::vector<unsigned char>& keys)
{
	for (int i = 0; i < int(Key::Count); i++)
	{
		bindings[Key(i)] = keys[i];
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
	std::vector<unsigned char> keys;
	for (int i = 0; i < int(Key::Count); i++)
	{
		unsigned char binding;
		in.seekg(sizeof(i), std::ios::cur);
		in.read(reinterpret_cast<char*>(&binding), sizeof(binding));
		keys.push_back(binding);

		// Skip new lines (carriage return + line feed).
		in.seekg(2, std::ios::cur);
	}
	SetBindings(keys);
	return true;
}

unsigned char Controller::GetBinding(Key key) const
{
	return bindings.find(key)->second;
}