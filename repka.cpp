#include <cstdlib>
#include <iostream>
#include <vector>

#include "Storage.hpp"
#include "Field.hpp"
#include "Graphics.hpp"

#include "Position.hpp"
#include "Human.hpp"
#include "Bot.hpp"

#define LOG {std::cerr << "------------------------------------------" << std::endl;}

int main(int argc, char **argv) {
	int
		sizex = 15,
		sizey = 15;
	if(argc == 3) {
		sizex = atoi(argv[1]);
		sizey = atoi(argv[2]);
	}

	Storage *storage = new Storage();

	LOG

	Field *field = new Field(storage, sizex, sizey);

	LOG

	Graphics::InitGraphics(field, storage, argc, argv);

	field->players.push_back(new Human(field, Position(0, 0), storage));
	field->players.push_back(new Bot(field, Position(sizex - 1, sizey - 1), storage));

	Graphics::StartGraphics();
	Graphics::CleanUp();

	return 0;
}
