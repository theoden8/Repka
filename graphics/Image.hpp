#pragma once

#include "glut_config.h"

#include <string>

struct Image {
	int width;
	int height;
	GLuint id;

	Image();
	bool load(const std::string &filename);
};
