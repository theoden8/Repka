#include "Storage.hpp"

Storage::Storage():
	sprites()
{
	// GRASS
	sprites.push_back(Sprite("grass", 5));
	// HEADQUARTERS
	sprites.push_back(Sprite("headquarters", 4));
	// KNIGHT
	sprites.push_back(Sprite("knight", 4));
	// PRINCESS
	sprites.push_back(Sprite("princess", 4));
	// DRAGON
	sprites.push_back(Sprite("dragon", 4));
	// SELECTION
	sprites.push_back(Sprite("selection", 2));
	// SELECTED_TARGET
	sprites.push_back(Sprite("selected_target", 1));
	// STAMINA BAR
	sprites.push_back(Sprite("staminabar", 1));
	// HEALTHBAR
	sprites.push_back(Sprite("healthbar", 1));
}

Storage::~Storage()
{}

void Storage::Clear() {
	while(!sprites.empty()) {
		sprites.back().Clear();
		sprites.pop_back();
	}
}
