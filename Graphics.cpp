#include <iostream>
#include <unistd.h>

#include "glut_config.h"

#include "Graphics.hpp"
#include "Field.hpp"
#include "Object.hpp"
#include "Player.hpp"
#include "Storage.hpp"

double Graphics::windowWidth = 0.0;
double Graphics::windowHeight = 0.0;
timeval Graphics::changeFrame;
Field *Graphics::field = NULL;
Storage *Graphics::storage = NULL;

void Graphics::SetOpenGLContext(double proportion, int argc, char **argv) {
	gettimeofday(&changeFrame, NULL);

	glutInit(&argc, argv);
	int maxwidth = glutGet(GLUT_SCREEN_WIDTH);
	int maxheight = glutGet(GLUT_SCREEN_HEIGHT);
	windowHeight = maxheight - 100;
	windowWidth = windowHeight * proportion;
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition((maxwidth - windowWidth) / 2, 0);
	glutCreateWindow("Repka");
	glutShowWindow();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Graphics::SetOpenGLFunctions(Field *f, Storage *s) {
	field = f;
	storage = s;

	glutDisplayFunc(Display);
	glutTimerFunc(FREQUENCY, Timer, 0);
	glutMouseFunc(Mouse);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutIdleFunc(Idle);
	glutSpecialFunc(Special);
}

void Graphics::StartGraphics() {
	glutMainLoop();
}

void Graphics::Draw(GLuint frame, Position position) {
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

void Graphics::SetPlayerColor(Player *p) {
	switch(p->color) {
		case 0: glColor3f(1.0f, 0.9f, 0.9f); break;
		case 1: glColor3f(0.9f, 0.9f, 1.0f); break;
		case 2: glColor3f(0.9f, 1.0f, 0.9f); break;
		default: glColor3f(1.0f, 1.0f, 1.0f); break;
	}
}

void Graphics::SetVictoryColor(Player *p) {
	switch(p->color) {
		case 0: glColor3f(1.0f, 0.0f, 0.0f); break;
		case 1: glColor3f(0.0f, 0.0f, 1.0f); break;
		case 2: glColor3f(0.0f, 1.0f, 0.0f); break;
		default: glColor3f(0.5f, 0.5f, 0.5f); break;
	}
}

void Graphics::ResetColor() {
	glColor3f(1.0f, 1.0f, 1.0f);
}

void Graphics::Display() {
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glOrtho(0, field->width, 0, field->height, -1, 1);

	bool victory = field->winner != NULL;

	if(victory) {
		SetVictoryColor(field->winner);
	}
	Object *object;
	for(int x = 0; x < field->width; ++x) {
		for(int y = 0; y < field->height; ++y) {
			Position position(x, y);
			object = field->GetPassiveObject(position);
			if(object != NULL) {
				Draw(object->GetFrame(), object->position);
			}
			object = field->GetActiveObject(position);
			if(object != NULL) {
				if(!victory) {
					SetPlayerColor(object->owner);
					Draw(object->GetFrame(), object->position);
					ResetColor();
				}
				// staminabar
				if(
					object->stamina && (
						object->target == NULL
						|| object->position == object->target->position
					)
				)
                {
					Draw(storage->sprites[Storage::STAMINABAR].frames[0].id, object->position);
				}
				// healthbar
				if(!victory) {
					glColor3f(
						float(object->maxhitpoints - object->hitpoints) / object->maxhitpoints,
						float(object->hitpoints) / object->maxhitpoints,
						0.0f
					);
					Draw(storage->sprites[Storage::HEALTHBAR].frames[0].id, object->position);
					ResetColor();
				}
			}
		}
	}

	Object *selected = field->GetActivePlayer()->selected;
	if(selected != NULL) {
		Draw(storage->sprites[Storage::SELECTION].frames[0].id, selected->position);
		if(selected->target != NULL)
			Draw(storage->sprites[Storage::SELECTED_TARGET].frames[0].id, selected->target->position);
	}

	glutSwapBuffers();

	if(victory) {
		sleep(3);
		Quit();
		storage->Clear();
		delete storage;
		delete field->winner;
		delete field;
	}
}

void Graphics::Timer(int) {
}

Position Graphics::pos2click(double x, double y) {
	return Position(
		x / (windowWidth / field->width),
		(windowHeight - y) / (windowHeight / field->height)
	);
}

void Graphics::Keyboard(unsigned char key, int x, int y) {
	switch(key) {
		case 27:
			Quit();
			break;
		case 32:
			field->NextPlayer();
		break;
	}
	if(('a' <= key && key <= 'z') || key == 13)
		field->GetActivePlayer()->keyboard(key, pos2click(x, y));
}

void Graphics::Special(int key, int x, int y) {
	field->GetActivePlayer()->special(key, x, y);
}

void Graphics::Mouse(int button, int state, int x, int y) {
	Object *object = field->GetObject(pos2click(x, y));
	if(object == NULL)
		return;
	field->GetActivePlayer()->mouse(button, state, object);
}


void Graphics::Reshape(int new_width, int new_height) {
	windowHeight = new_height;
	windowWidth = new_width;
	glViewport(0, 0, windowWidth, windowHeight);
	glutPostRedisplay();
}

void Graphics::Idle() {
	timeval current_time;
	gettimeofday(&current_time, NULL);
	if((current_time.tv_usec - Graphics::changeFrame.tv_usec + MSPERS) % MSPERS < MSPERS / FREQUENCY)
		return;

	Object *object;
	for(int x = 0; x < field->width; ++x) {
		for(int y = 0; y < field->height; ++y) {
			Position position(x, y);
			object = field->GetActiveObject(position);
			if(object != NULL && rand() % 10 == 0)
				object->ChangeFrame();
			object = field->GetPassiveObject(position);
			if(object != NULL && rand() % 10 == 0)
				object->ChangeFrame();
		}
	}

	Graphics::changeFrame = current_time;
	glutPostRedisplay();
}

void Graphics::Quit() {
	field->Clear();
	delete field;
	storage->Clear();
	delete storage;
	exit(0);
}
