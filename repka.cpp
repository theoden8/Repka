#include <cstdlib>
#include <iostream>
#include <vector>

#include "Storage.hpp"
#include "Field.hpp"
#include "Graphics.hpp"

#include "Position.hpp"
#include "Human.hpp"
#include "Bot.hpp"

int main(int argc, char **argv) {
	int sizex = 60, sizey = 40;
	if(argc == 3) {
		sizex = atoi(argv[1]);
		sizey = atoi(argv[2]);
	}
	Graphics::SetOpenGLContext(double(sizex)/double(sizey), argc, argv);
	Storage *storage = new Storage();
	Field *field = new Field(storage, sizex, sizey);
	Graphics::SetOpenGLFunctions(field, storage);
	field->players.push_back(new Human(field, Position(0, 0), storage));
	field->players.push_back(new Bot(field, Position(sizex - 1, sizey - 1), storage));
	Graphics::StartGraphics();
}
