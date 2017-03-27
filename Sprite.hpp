#pragma once

#include <vector>
#include <string>

#include "Image.hpp"

struct Sprite {
	std::vector <Image> frames;
	int frequency;

	Sprite(std::string path, int framesCount);
	~Sprite();
	void Clear();
};
