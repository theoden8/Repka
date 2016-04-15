#include <cstdlib>
#include <sys/time.h>
#include <iostream>
#include <vector>

#include <GLUT/glut.h>

#include "Storage.hpp"
#include "Object.hpp"
#include "Field.hpp"
#include "Human.hpp"
#include "Bot.hpp"
#include "Headquarters.hpp"
#include "Knight.hpp"
#include "Princess.hpp"
#include "Dragon.hpp"

using std::vector;

double g_width = 600, g_height = 600;
const double g_frequency = 20;

const int g_MSPERS = 1e6;
timeval g_change_frame;

Field *g_field = NULL;
Storage *g_storage = NULL;

int sizex = 15, sizey = 15;

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
	glOrtho(0, g_field->width, 0, g_field->height, -1, 1);

	Object *object;
	for (int x = 0; x < g_field->width; ++x) {
		for (int y = 0; y < g_field->height; ++y) {
			Position position(x, y);
			object = g_field->GetPassiveObject(position);
			if (object != NULL)
				draw(object->GetFrame(), object->position);
			object = g_field->GetActiveObject(position);
			if (object != NULL) {
				draw(object->GetFrame(), object->position);
				if(
					object->stamina && (
						object->target == NULL
						|| object->position == object->target->position
					)
				) {
					draw(g_storage->sprites[Storage::STAMINABAR].frames[0].id, object->position);
				}
			}
		}
	}

	Object *selected = g_field->GetActivePlayer()->selected;
	if (selected != NULL) {
		draw(g_storage->sprites[Storage::SELECTION].frames[0].id, selected->position);
		if (selected->target != NULL)
			draw(g_storage->sprites[Storage::SELECTED_TARGET].frames[0].id, selected->target->position);
	}

	glutSwapBuffers();
}

void timer(int) {
}

Position Position2Click(double x, double y) {
	return Position(
		x / (g_width / g_field->width),
		(g_height - y) / (g_height / g_field->height)
	);
}

void keyboard(unsigned char key, int x, int y) {
	switch(key) {
		case 27:
			exit(0);
		break;
		case 32:
			g_field->NextPlayer();
		break;
	}
	if(('a' <= key && key <= 'z') || key == 13) {
		g_field->GetActivePlayer()->keyboard(key, Position2Click(x, y));
	}
}

void special(int key, int x, int y) {
	g_field->GetActivePlayer()->special(key, x, y);
}


void mouse(int button, int state, int x, int y) {
	Object *object = g_field->GetObject(Position2Click(x, y));
	if (object == NULL) {
		return;
	}
	g_field->GetActivePlayer()->mouse(button, state, object);
}

void reshape(int new_width, int new_height) {
	g_height = new_height;
	g_width = new_width;
	glViewport(0, 0, g_width, g_height);
	glutPostRedisplay();
}

void idle() {
	timeval current_time;
	gettimeofday(&current_time, NULL);
	if ((current_time.tv_usec - g_change_frame.tv_usec + g_MSPERS) % g_MSPERS < g_MSPERS / g_frequency)
		return;

	Object *object;
	for (int x = 0; x < g_field->width; ++x) {
		for (int y = 0; y < g_field->height; ++y) {
			Position position(x, y);
			object = g_field->GetActiveObject(position);
			if (object != NULL && rand() % 10 == 0)
				object->ChangeFrame();
			object = g_field->GetPassiveObject(position);
			if (object != NULL && rand() % 10 == 0)
				object->ChangeFrame();
		}
	}

	g_change_frame = current_time;
	glutPostRedisplay();
}

int main(int argc, char **argv) {
	if(argc == 3) {
		sizex = atoi(argv[1]);
		sizey = atoi(argv[2]);
	}
	gettimeofday(&g_change_frame, NULL);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(g_width, g_height);
	glutCreateWindow("Repka");

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glutDisplayFunc(display);
	glutTimerFunc(g_frequency, timer, 0);
	glutMouseFunc(mouse);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
	glutSpecialFunc(special);

	g_storage = new Storage();
	g_field = new Field(g_storage, sizex, sizey);

	g_field->players.push_back(new Human(g_field, Position(0, 0), g_storage));
	g_field->players.push_back(new Bot(g_field, Position(sizex - 1, sizey - 1), g_storage));

	glutMainLoop();

	delete g_field;
	delete g_storage;

	return 0;
}
