#include "Sprite.hpp"

#include <iostream>
Sprite::Sprite (std::string path, int framesCount):
	frames(framesCount)
{
	for(int i = 0; i < framesCount; i++) {
		std::cerr << "\033[1;92mtextures/" + path + "_" + std::to_string(i) + ".tga\033[0m" << std::endl;
		frames[i].load("textures/" + path + "_" + std::to_string(i) + ".tga");
	}
}
