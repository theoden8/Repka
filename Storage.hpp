#pragma once

#include <vector>

#include "Sprite.hpp"

struct Storage {
	static const int GRASS = 0;
	static const int HEADQUARTERS = 1;
	static const int KNIGHT = 2;
	static const int PRINCESS = 3;
	static const int DRAGON = 4;
	static const int SELECTION = 5;
	static const int SELECTED_TARGET = 6;
	static const int STAMINABAR = 7;
	static const int HEALTHBAR = 8;

	std::vector <Sprite> sprites;

	Storage();
	~Storage();
	void Clear();
};
