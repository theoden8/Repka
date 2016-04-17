#include "Princess.hpp"
#include "Storage.hpp"
#include "Field.hpp"

Princess::Princess(Player *owner, Field *field, Storage *storage, Position position):
	Object(owner, field, storage, position, STAMINA, HITPOINTS, Storage::PRINCESS, true, COST)
{}

Princess::~Princess() {
}

void Princess::DoStep() {
	if (target != NULL)
		field->Move(this);
}

void Princess::Destruction() {
}

void Princess::ResetStamina() {
	stamina = STAMINA;
}
