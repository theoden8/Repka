#ifndef __PRINCESS__
#define __PRINCESS__

#include "Object.hpp"

struct Princess : public Object {
	static const int COST = 2;
	static const int HITPOINTS = 3;
	static const int STAMINA = 2;

	Princess(Player *owner, Field *field, Storage *storage, Position position);

	~Princess();

	void DoStep();
	void Destruction();
	void ResetStamina();
};

#endif
