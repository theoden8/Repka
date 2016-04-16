#include <cstdlib>
#include <iostream>
#include <vector>

#include <GLUT/glut.h>

#include "Graphics.hpp"

#include "Position.hpp"
#include "Human.hpp"
#include "Bot.hpp"

int main(int argc, char **argv) {
	InitGraphics(argc, argv);

	g_storage = new Storage();
	g_field = new Field(g_storage, sizex, sizey);

	g_field->players.push_back(new Human(g_field, Position(0, 0), g_storage));
	g_field->players.push_back(new Bot(g_field, Position(sizex - 1, sizey - 1), g_storage));

	glutMainLoop();

	delete g_field;
	delete g_storage;

	return 0;
}
