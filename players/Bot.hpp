#pragma once

#include <vector>

#include "Player.hpp"

struct Bot:public Player {
	Bot(Field *f, Position destination, Storage *storage);
	~Bot();
	void keyboard(unsigned char key, const Position &position);
	void special(int key, int x, int y);
	void mouse(int button, int state, Object *object);
	/* std::vector <std::vector <Object *> > Clusterisation(); */
	/* void ArtificialIntelligence(std::vector <std::vector <Object *> > bunches); */
	void SetTargets();
	void Spawn(char key);
};
