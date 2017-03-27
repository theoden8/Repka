#pragma once

#include "glut_config.h"

#include <string>

struct Image {
	int width = 0;
	int height = 0;
	GLuint id = 0;
	bool is_loaded = false;

	Image();
	~Image();
	bool load(const std::string &filename);
	void Clear();
};
