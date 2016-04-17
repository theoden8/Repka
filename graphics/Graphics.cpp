#include <GLUT/glut.h>

#include "Graphics.hpp"

#include "Object.hpp"

#include "Player.hpp"

#include "Headquarters.hpp"
#include "Knight.hpp"
#include "Princess.hpp"
#include "Dragon.hpp"

double
	Graphics::window_width = 600,
	Graphics::window_height = 600;
timeval
	Graphics::change_frame;
Field *
	Graphics::field = NULL;
Storage *
	Graphics::storage = NULL;

void Graphics::SetOpenGLContext(int argc, char **argv) {
	gettimeofday(&change_frame, NULL);

	window_width = 600,
	window_height = 600;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(window_width, window_height);
	glutCreateWindow("Repka");

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

void Graphics::CleanUp() {
	delete field;
	delete storage;
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

void Graphics::Display () {
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glOrtho(0, field->width, 0, field->height, -1, 1);

	Object *object;
	for(int x = 0; x < field->width; ++x) {
		for(int y = 0; y < field->height; ++y) {
			Position position(x, y);
			object = field->GetPassiveObject(position);
			if(object != NULL)
				Draw(object->GetFrame(), object->position);
			object = field->GetActiveObject(position);
			if(object != NULL) {
				Draw(object->GetFrame(), object->position);
				if(
					object->stamina && (
						object->target == NULL
						|| object->position == object->target->position
					)
				) {
					Draw(storage->sprites[Storage::STAMINABAR].frames[0].id, object->position);
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
}

void Graphics::Timer(int) {
}

Position Graphics::pos2click(double x, double y) {
	return Position(
		x / (window_width / field->width),
		(window_height - y) / (window_height / field->height)
	);
}

void Graphics::Keyboard(unsigned char key, int x, int y) {
	switch(key) {
		case 27:
			exit(0);
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
	if(object == NULL) {
		return;
	}
	field->GetActivePlayer()->mouse(button, state, object);
}

void Graphics::Reshape(int new_width, int new_height) {
	window_height = new_height;
	window_width = new_width;
	glViewport(0, 0, window_width, window_height);
	glutPostRedisplay();
}

void Graphics::Idle() {
	timeval current_time;
	gettimeofday(&current_time, NULL);
	if((current_time.tv_usec - Graphics::change_frame.tv_usec + MSPERS) % MSPERS < MSPERS / FREQUENCY)
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

	Graphics::change_frame = current_time;
	glutPostRedisplay();
}
