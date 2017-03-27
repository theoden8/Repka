#pragma once

#include "Object.hpp"

struct Princess : public Object {
	static const int COST = 4;
	static const int HITPOINTS = 2;
	static const int STAMINA = 2;

	Princess(Player *owner, Field *field, Storage *storage, Position position);

	~Princess();

	void DoStep();
	void Destruction();
	void ResetStamina();
};
