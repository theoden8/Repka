#ifndef __HUMAN__
#define __HUMAN__

#include "Player.hpp"

struct Human:public Player {
	Human(Field *field, Position destination, Storage *storage);
	~Human();
	void keyboard(unsigned char key, Position position);
	void special(int key, int x, int y);
	void mouse(int button, int state, Object *object);
};

#endif
