#include <iostream>

#include "Storage.hpp"
#include "Object.hpp"
#include "Field.hpp"
#include "Player.hpp"

Object::Object(Player *owner, Field *field, Storage *storage, Position position, int stamina, int hitpoints, int idTexture, bool active, int cost):
	owner(owner),
	field(field),
	storage(storage),
	position(position),
	stamina(stamina),
	hitpoints(hitpoints),
	idTexture(idTexture),
	currentFrame(0),
	target(NULL),
	active(active),
	cost(cost)
{
	field->SetObject(this);
	if(owner != NULL)
		owner->gold -= cost;
}

Object::~Object() {
	field->RemoveObject(this);
	for(const auto &it : field->active_objects) {
		if(it != NULL && it->target == this)
			it->target = NULL;
	}
}

GLuint Object::GetFrame() {
	return storage->sprites[idTexture].frames[currentFrame].id;
}

void Object::ChangeFrame() {
	currentFrame = (currentFrame + 1) % storage->sprites[idTexture].frames.size();
}

void Object::GoTo(Object *obj) {
	target = obj;
}

void Object::Respond(char key, Position mouse) {
	if (key == 'h')
		target = NULL;
}
