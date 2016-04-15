#include <iostream>

#include "Dragon.hpp"
#include "../Storage.hpp"
#include "../Field.hpp"

Dragon::Dragon(Player *owner, Field *field, Storage *storage, Position position):
	Object(owner, field, storage, position, STAMINA, HITPOINTS, Storage::DRAGON, true, COST)
{
}

Dragon::~Dragon() {
}

void Dragon::DoStep() {
	if (target != NULL) {
		field->Move(this);
	}
}

void Dragon::Destruction()
{
}

void Dragon::ResetStamina() {
	stamina = STAMINA;
}
