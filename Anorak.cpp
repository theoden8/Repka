#include "Anorak.hpp"
#include "Field.hpp"

Anorak::Anorak(Field *field, Position destination, Storage *storage) :
	Player(field, destination, storage)
{
}

Anorak::~Anorak() { }

void Anorak::keyboard(unsigned char key, Position position) {
	if (selected == NULL || selected->owner != this) {
		return;
	}
	if (key == 13) {
		selected->target = field->GetObject(position);
	} else {
		selected->Respond(key, position);
	}
}

void Anorak::special(int key, int x, int y) {
	Position selection = selected->position;
	if (selected == NULL) {
		selected = city;
		return;
	}
	switch(key) {
		case 100 :
			selection.x += -1;
		break;
		case 101 :
			selection.y += 1;
		break;
		case 102 :
			selection.x += 1;
		break;
		case 103 :
			selection.y += -1;
		break;
	}
	if (field->Valid(selection)) {
		selected = field->GetObject(selection);
	}
}

void Anorak::mouse(int button, int state, Object *object) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		selected = object;
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && selected != NULL && object->owner == this) {
		selected->target = object;
	}
}
