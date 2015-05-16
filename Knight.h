#ifndef __KNIGHT__
#define __KNIGHT__

#include "Object.h"

struct Knight : public Object {
	static const int COST = 1;
	static const int HITPOINTS = 3;
	static const int STAMINA = 2;

	Knight(Player *owner, Field *field, Storage *storage, Position position);

	~Knight();

	void DoStep();
	void Destruction();
	void ResetStamina();
};

#endif
