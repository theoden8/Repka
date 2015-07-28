#ifndef __ANORAK__
#define __ANORAK__

#include "Player.hpp"

struct Anorak:public Player {
	Anorak(Field *field, Position destination, Storage *storage);
	~Anorak();
	void keyboard(unsigned char key, Position position);
	void special(int key, int x, int y);
	void mouse(int button, int state, Object *object);
};

#endif
