#ifndef __SPRITE__
#define __SPRITE__

#include <vector>
#include <string>

#include "Image.h"

struct Sprite {
	std::vector <Image> frames;
	int frequency;

	Sprite(std::string path, int framesCount);
};

#endif
