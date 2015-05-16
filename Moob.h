#ifndef __MOOB__
#define __MOOB__

#include <vector>

#include "Player.h"

struct Moob:public Player {
	Moob(Field *f, Position destination, Storage *storage);
	~Moob();
	void keyboard(unsigned char key, Position position);
	void special(int key, int x, int y);
	void mouse(int button, int state, Object *object);
	std::vector <std::vector <Object *> > Clusterisation();
	void ArtificialIntelligence(std::vector <std::vector <Object *> > bunches);
	void SetTargets();
	void Spawn(char key);
};
#endif
