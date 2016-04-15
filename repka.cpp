#include <GLUT/glut.h>
#include <cstdlib>
#include <sys/time.h>
#include <iostream>
#include <vector>

#include "Units/include.hpp"
#include "Field.hpp"
#include "Human.hpp"
#include "Bot.hpp"
#include "Storage.hpp"

using std::vector;

typedef std::map <Position, std::vector <Object *> > p2vpobj;
typedef std::map <Position, std::vector <Object *> > :: iterator p2vpobjit;
typedef std::vector <Object *> vpobj;
typedef std::vector <Object *> :: iterator vpobjit;

double width = 600;
double height = 600;
const double freqy = 20;

const int MSPERS = 1e6;
timeval change_frame;

Field *field = NULL;
Storage *storage = NULL;

int sizex = 15;
int sizey = 15;

void draw(GLuint frame, Position position) {
	glPushMatrix();
	glTranslatef(position.x, position.y, 0);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, frame);

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(0, 0, 0.0);
	glTexCoord2f(1, 0); glVertex3f(1, 0, 0.0);
	glTexCoord2f(1, 1); glVertex3f(1, 1, 0.0);
	glTexCoord2f(0, 1); glVertex3f(0, 1, 0.0);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

void display () {
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glOrtho(0, field->width, 0, field->height, -1, 1);

	Object *object;
	for (int x = 0; x < field->width; ++x) {
		for (int y = 0; y < field->height; ++y) {
			Position position(x, y);
			object = field->GetPassiveObject(position);
			if (object != NULL) {
				draw(object->GetFrame(), object->position);
			}
			object = field->GetActiveObject(position);
			if (object != NULL) {
				draw(object->GetFrame(), object->position);
				if(
					object->stamina
					&& (
						object->target == NULL
						|| object->position == object->target->position
					)
				) {
					draw(storage->sprites[Storage::STAMINABAR].frames[0].id, object->position);
				}
			}
		}
	}

	Object *selected = field->GetActivePlayer()->selected;
	if (selected != NULL) {
		draw(storage->sprites[Storage::SELECTION].frames[0].id, selected->position);
		if (selected->target != NULL) {
			draw(storage->sprites[Storage::SELECTED_TARGET].frames[0].id, selected->target->position);
		}
	}

	glutSwapBuffers();
}

void timer(int) {
}

Position Position2Click(double x, double y) {
	return Position(x / (width / field->width), (height - y) / (height / field->height));
}

void keyboard(unsigned char key, int x, int y) {
	switch(key) {
		case 27:
			exit(0);
		break;
		case 32:
			field->NextPlayer();
		break;
	}
	if(('a' <= key && key <= 'z') || key == 13) {
		field->GetActivePlayer()->keyboard(key, Position2Click(x, y));
	}
}

void special(int key, int x, int y) {
	field->GetActivePlayer()->special(key, x, y);
}


void mouse(int button, int state, int x, int y) {
	Object *object = field->GetObject(Position2Click(x, y));
	if (object == NULL) {
		return;
	}
	field->GetActivePlayer()->mouse(button, state, object);
}

void reshape(int new_width, int new_height) {
	height = new_height;
	width = new_width;
	glViewport(0, 0, width, height);
	glutPostRedisplay();
}

void idle() {
	timeval current_time;
	gettimeofday(&current_time, NULL);
	if ((current_time.tv_usec - change_frame.tv_usec + MSPERS) % MSPERS < MSPERS / freqy)
		return;

	Object *object;
	for (int x = 0; x < field->width; ++x) {
		for (int y = 0; y < field->height; ++y) {
			Position position(x, y);
			object = field->GetActiveObject(position);
			if (object != NULL && rand() % 10 == 0) {
				object->ChangeFrame();
			}
			object = field->GetPassiveObject(position);
			if (object != NULL && rand() % 10 == 0) {
				object->ChangeFrame();
			}
		}
	}

	change_frame = current_time;
	glutPostRedisplay();
}

int main(int argc, char **argv) {
	if(argc == 3) {
		sizex = atoi(argv[1]);
		sizey = atoi(argv[2]);
	}
	gettimeofday(&change_frame, NULL);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutCreateWindow("Repka");

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glutDisplayFunc(display);
	glutTimerFunc(freqy, timer, 0);
	glutMouseFunc(mouse);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
	glutSpecialFunc(special);

	storage = new Storage();
	field = new Field(storage, sizex, sizey);

	field->players.push_back(new Human(field, Position(0, 0), storage));
	field->players.push_back(new Bot(field, Position(sizex - 1, sizey - 1), storage));

	glutMainLoop();


	delete field;
	delete storage;

	return 0;
}
