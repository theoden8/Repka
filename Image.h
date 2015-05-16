#ifndef __IMAGE__
#define __IMAGE__

#include <GLUT/glut.h>
#include <string>

struct Image {
	int width;
	int height;
	GLuint id;

	Image();
	bool load(const std::string &filename);
};

#endif
