#pragma once

#include <sys/time.h>

#include "Position.hpp"

double
	g_width = 600,
	g_height = 600;
const double
	g_frequency = 20;
const int
	g_MSPERS = 1e6;
timeval
	g_change_frame;
int
	sizex = 15,
	sizey = 15;

void Draw(GLuint frame, Position position);
void Display();
void Timer(int);
Position pos2click(double x, double y);
void Keyboard(unsigned char key, int x, int y);
void Special(int key, int x, int y);
void Mouse(int button, int state, int x, int y);
void Reshape(int new_width, int new_height);
void Idle();

void InitGraphics(int argc, char **argv);
