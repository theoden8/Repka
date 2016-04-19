#pragma once

#include "glut_config.h"

#include "Position.hpp"

struct Storage;
struct Field;
struct Player;

struct Object {
	Player *owner;

	Field *field;

	Position position;

	bool active,
		 fortify;

	int
		stamina,
		hitpoints,
		cost;

	Object *target;
	Storage *storage;

	int
		idTexture,
		currentFrame;

	Object(Player *owner, Field *field, Storage *storage, Position position, int stamina, int hitpoints, int idTexture, bool active, int cost);
	virtual ~Object();

	GLuint GetFrame();
	virtual void DoStep() = 0;
	void ChangeFrame();
	void GoTo(Object *obj);
	virtual void Respond(char key, Position mouse);
	virtual void ResetStamina() = 0;
};
