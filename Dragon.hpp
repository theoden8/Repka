#pragma once

#include "Object.hpp"

struct Dragon : public Object {
	static const int COST = 2;
	static const int HITPOINTS = 2;
	static const int STAMINA = 2;

	Dragon(Player *owner, Field *field, Storage *storage, Position position);

	~Dragon();

	void DoStep();
	void Destruction();
	void ResetStamina();
};
