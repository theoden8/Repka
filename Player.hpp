#pragma once

#include "Object.hpp"

struct Storage;
struct Field;

struct Player {
	static int g_color;
	int color;
	Field *
		field;
	Object
		*selected,
		*city;
	int
		money,
		income;
	Player(Field *field, Position destination, Storage *storage);
	virtual ~Player();
	virtual void keyboard(unsigned char key, const Position &position) = 0;
	virtual void special(int key, int x, int y) = 0;
	virtual void mouse(int button, int state, Object *object) = 0;
	void Stamina();
	void Death();
	virtual void SetTargets();
};
