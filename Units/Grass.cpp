#include "Grass.hpp"
#include "../Storage.hpp"

Grass::Grass(Field *field, Storage *storage, Position position):
	Object(NULL, field, storage, position, 0, 0, Storage::GRASS, false, 0)
{
}

Grass::~Grass() {
}

void Grass::DoStep() {
}

void Grass::ResetStamina() {
}
