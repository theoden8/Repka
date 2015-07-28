#ifndef __GRASS__
#define __GRASS__

#include "Object.hpp"

struct Grass : public Object {
	static const int COST = 0;
	static const int STAMINA = 0;
	static const int HITPOINTS = 1000;
	Grass(Field *field, Storage *storage, Position position);

	~Grass();

	void DoStep();
	void Destruction();
	void ResetStamina();
};

#endif
