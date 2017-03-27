#include <iostream>

#include "Storage.hpp"
#include "Object.hpp"
#include "Field.hpp"
#include "Player.hpp"

Object::Object(
	Player *owner,
	Field *field,
	Storage *storage,
	Position position,
	int stamina, int hitpoints,
	int idTexture,
	bool active,
	int cost
):
	owner(owner),
	field(field),
	storage(storage),
	position(position),
	stamina(stamina),
	maxhitpoints(hitpoints),
	hitpoints(hitpoints),
	idTexture(idTexture),
	currentFrame(0),
	target(NULL),
	active(active),
	cost(cost)
{
	field->SetObject(this);
	if(owner != NULL)
		owner->money -= cost;
}

Object::~Object() {
	field->RemoveObject(this);
	for(const auto &it : field->activeObjects) {
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

void Object::SetTarget(Object *new_target) {
	target = new_target;
}

void Object::Respond(char key, Position mouse) {
	switch(key) {
		case 'h':
			target = NULL;
		break;
		case 'g':
			target = field->GetObject(mouse);
		break;
	}
}
