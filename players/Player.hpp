#pragma once

#include "Object.hpp"

struct Storage;
struct Field;

struct Player {
	Field *field;
	Object *selected;
	Object *city;
	int gold;
	int income;
	Player(Field *field, Position destination, Storage *storage);
	virtual ~Player();
	virtual void keyboard(unsigned char key, Position position) = 0;
	virtual void special(int key, int x, int y);
	virtual void mouse(int button, int state, Object *object) = 0;
	void stamina();
	void death();
	virtual void SetTargets();
};
