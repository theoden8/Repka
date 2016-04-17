#pragma once

#include "Dragon.hpp"
#include "Princess.hpp"
#include "Knight.hpp"

struct Headquarters : public Object {
	static const int COST = 1000;
	static const int STAMINA = 0;
	static const int HITPOINTS = 10;

	Headquarters(Player *owner, Field *field, Storage *storage, Position position);

	~Headquarters();

	void DoStep();
	void Respond(char key, Position mouse);
	void ResetStamina();
};
