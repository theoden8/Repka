#ifndef __OBJECT__
#define __OBJECT__

#include <GLUT/glut.h>

#include "../Position.hpp"

struct Storage;
struct Field;
struct Player;

struct Object {
	Player *owner;
	Position position;
	int stamina;
	int hitpoints;
	Object *target;
	bool active;
	int cost;
	bool fortify;

	Storage *storage;
	int idTexture;
	int currentFrame;

	Field *field;

	Object(Player *owner, Field *field, Storage *storage, Position position, int stamina, int hitpoints, int idTexture, bool active, int cost);
	virtual ~Object();

	GLuint GetFrame();
	virtual void DoStep() = 0;
	void ChangeFrame();
	void GoTo(Object *obj);
	virtual void Respond(char key, Position mouse);
	virtual void ResetStamina() = 0;
};

#endif
