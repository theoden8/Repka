#pragma once

#include "Object.hpp"

struct Storage;
struct Field;

struct Player {
	Field *
		field;
	Object
		*selected,
		*city;
	int
		gold,
		income;
	Player(Field *field, Position destination, Storage *storage);
	virtual ~Player();
	virtual void keyboard(unsigned char key, const Position &position) = 0;
	virtual void special(int key, int x, int y) = 0;
	virtual void mouse(int button, int state, Object *object) = 0;
	void stamina();
	void death();
	virtual void SetTargets();
};
