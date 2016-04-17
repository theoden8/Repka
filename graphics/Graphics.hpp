#pragma once

#include <sys/time.h>

#include "Storage.hpp"
#include "Field.hpp"
#include "Position.hpp"

#define MSPERS ((int)1e6)
#define FREQUENCY 20.

class Graphics {
	static double
		window_width,
		window_height;
	static timeval
		change_frame;

	static Field *field;
	static Storage *storage;

public:
	static void InitGraphics(Field *, Storage *, int argc, char **argv);
	static void StartGraphics();
	static void CleanUp();

private:
	static void Draw(GLuint frame, Position position);
	static void Display();
	static void Timer(int);
	static Position pos2click(double x, double y);
	static void Keyboard(unsigned char key, int x, int y);
	static void Special(int key, int x, int y);
	static void Mouse(int button, int state, int x, int y);
	static void Reshape(int new_width, int new_height);
	static void Idle();
};
