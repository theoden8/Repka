#pragma once

#include <sys/time.h>

#include "Storage.hpp"
#include "Field.hpp"
#include "Position.hpp"

#define MSPERS ((int)1e6)
#define FREQUENCY 20.

class Graphics {
	static double
		windowWidth,
		windowHeight;
	static timeval
		changeFrame;
	static Field *field;
	static Storage *storage;
public:
	static void SetOpenGLContext(double proportion, int argc, char **argv);
	static void SetOpenGLFunctions(Field *, Storage *);
	static void StartGraphics();
private:
	static void Draw(GLuint frame, Position position);
	static void ResetColor();
	static void SetPlayerColor(Player *p);
	static void SetVictoryColor(Player *p);
	static void Display();
	static void Timer(int);
	static Position pos2click(double x, double y);
	static void Keyboard(unsigned char key, int x, int y);
	static void Special(int key, int x, int y);
	static void Mouse(int button, int state, int x, int y);
	static void Reshape(int new_width, int new_height);
	static void Idle();
	static void Quit();
};
