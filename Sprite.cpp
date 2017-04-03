#include "Sprite.hpp"

#include <iostream>
Sprite::Sprite (std::string path, int framesCount):
	frames(framesCount)
{
	for(int i = 0; i < framesCount; i++) {
		frames[i].load("textures/" + path + "_" + std::to_string(i) + ".tga");
	}
}

Sprite::~Sprite()
{}

void Sprite::Clear() {
	while(!frames.empty()) {
		frames.back().Clear();
		frames.pop_back();
	}
}
