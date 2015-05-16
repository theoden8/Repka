#ifndef __STORAGE__
#define __STORAGE__

#include <vector>

#include "Sprite.h"

struct Storage {
	static const int GRASS = 0;
	static const int HEADQUARTERS = 1;
	static const int KNIGHT = 2;
	static const int PRINCESS = 3;
	static const int DRAGON = 4;
	static const int SELECTION = 5;
	static const int SELECTED_TARGET = 6;
	static const int STAMINABAR = 7;

	std::vector <Sprite> sprites;

	Storage();
};

#endif
