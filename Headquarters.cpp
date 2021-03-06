#include <iostream>

#include "Headquarters.hpp"
#include "Storage.hpp"
#include "Field.hpp"
#include "Player.hpp"

Headquarters::Headquarters(Player *owner, Field *field, Storage *storage, Position position):
	Object(owner, field, storage, position, STAMINA, HITPOINTS, Storage::HEADQUARTERS, true, COST)
{}

Headquarters::~Headquarters() {
}

void Headquarters::DoStep() {
}

void Headquarters::Respond(char key, Position mouse) {
	std::vector <Position> moves = field->GetMoves(this, position);
	if(moves.empty())
		return;

	Object *object = NULL;

	if(key == 'd' && owner->money >= Dragon::COST) {
		object = new Dragon(owner, field, storage, moves.back());
	} else if(key == 'p' && owner->money >= Princess::COST) {
		object = new Princess(owner, field, storage, moves.back());
	} else if(key == 'k' && owner->money >= Knight::COST) {
		object = new Knight(owner, field, storage, moves.back());
	}

	if(object != NULL)
		object->target = target;
}

void Headquarters::ResetStamina() {
}
