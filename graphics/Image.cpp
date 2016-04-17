#include <iostream>
#include <fstream>
#include <sstream>

#include "Image.hpp"

Image::Image()
{
	width = 0;
	height = 0;
	id = 0;
}

bool Image::load(const std::string &filename) {
	std::ifstream File(filename.c_str(), std::ios::in | std::ios::binary);
	unsigned char header[20];
	/* std::cerr << "TGA loading: " << filename << std::endl; */
	if(!File.is_open()) {
		id = 0;
		std::cerr << "TGA loading: Wasn't able to find specified Image" << std::endl;
		return false;
	}

	File.read(reinterpret_cast <char *> (header), sizeof(char) * 18);

	if(header[2] != 2) {
		File.close();
		id = 0;
		std::cerr << "TGA loading: wrong file header" << std::endl;
		return false;
	}

	if(header[0])
		File.seekg(header[0], std::ios_base::cur);

	width = header[13] * 256 + header[12];
	height = header[15] * 256 + header[14];
	int bpp = header[16] / 8;

	if(bpp != 4) {
		File.close();
		id = 0;
		std::cerr << "TGA loading: wrong bit depth" << std::endl;
		return false;
	}

	long ImageSize = width * height * bpp;
	unsigned char *data = new unsigned char[ImageSize];

	File.read(reinterpret_cast <char *> (data), sizeof(char) * ImageSize);

	for(GLuint cswap = 0; cswap < (unsigned int) ImageSize; cswap += bpp)
		std::swap(data[cswap], data[cswap + 2]);
	File.close();

	unsigned int color_mode = GL_RGBA;
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, color_mode, width, height, 0, color_mode, GL_UNSIGNED_BYTE, data);

	delete [] data;
	data = NULL;

	/* std::cerr << "TGA loading: finished id = " << id << std::endl; */

	return true;
}
