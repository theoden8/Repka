#include "Knight.hpp"
#include "Storage.hpp"
#include "Field.hpp"

Knight::Knight(Player *owner, Field *field, Storage *storage, Position position):
	Object(owner, field, storage, position, STAMINA, HITPOINTS, Storage::KNIGHT, true, COST)
{}

Knight::~Knight() {
}

void Knight::DoStep() {
	if(target != NULL)
		field->Move(this);
}

void Knight::Destruction() {
}

void Knight::ResetStamina() {
	stamina = STAMINA;
}
