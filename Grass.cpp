#include "Grass.h"
#include "Storage.h"

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
