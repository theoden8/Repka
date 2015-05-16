#include "Sprite.h"

std::string str(int x)
{
	if (x == 0)
		return "0";
	std::string tmp;
	while (x > 0) {
		tmp = char('0' + x % 10) + tmp;
		x /= 10;
	}
	return tmp;
}

Sprite::Sprite (std::string path, int framesCount):
	frames(framesCount)
{
	for(int i = 0; i < framesCount; i++) {
		frames[i].load("textures/" + path + "_" + str(i) + ".tga");
	}
}
