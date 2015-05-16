#include <iostream>

#include "Headquarters.h"
#include "Storage.h"
#include "Field.h"
#include "Player.h"
#include "Dragon.h"
#include "Princess.h"
#include "Knight.h"

Headquarters::Headquarters(Player *owner, Field *field, Storage *storage, Position position):
	Object(owner, field, storage, position, STAMINA, HITPOINTS, Storage::HEADQUARTERS, true, COST)
{
}

Headquarters::~Headquarters() {
}

void Headquarters::DoStep() {
}

void Headquarters::Respond(char key, Position mouse) {
	std::vector <Position> moves = field->GetMoves(this, position);
	if (moves.empty()) {
		return;
	}
	Object *object = NULL;
	if(key == 'd' && owner->gold >= Dragon::COST) {
		object = new Dragon(owner, field, storage, moves.back());
	}
	if(key == 'p' && owner->gold >= Princess::COST) {
		object = new Princess(owner, field, storage, moves.back());
	}
	if(key == 'k' && owner->gold >= Knight::COST) {
		object = new Knight(owner, field, storage, moves.back());
	}
	if(object != NULL) {
		object->target = target;
	}
}

void Headquarters::ResetStamina() {
}
