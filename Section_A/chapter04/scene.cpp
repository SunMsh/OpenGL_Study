#include "scene.h"
#include "utils.h"
#include "skybox.h"

GLuint Texture;
SkyBox skybox;

void Init()
{
	glMatrixMode(GL_PROJECTION);
	gluPerspective(50.0f, 800.0f/600.0f, 0.1f, 1000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
//	gluLookAt(0.0f, 2.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, -0.5f);
	skybox.Init("Res/");
}

void Draw()
{
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	skybox.Draw();

	glEnable(GL_DEPTH_TEST);

	//glBegin(GL_QUADS);
	//glColor4ub(0, 250, 0, 255);
	//glVertex3f(-0.1f, -0.1f, -0.4f);
	//glVertex3f(0.1f, -0.1f, -0.4f);
	//glVertex3f(0.1f, 0.1f, -0.4f);
	//glVertex3f(-0.1f, 0.1f, -0.4f);
	//glEnd();

	glBegin(GL_QUADS);
	glColor4ub(0, 250, 0, 255);
	glVertex3f(-0.1f, -0.1f, -0.6f);
	glVertex3f(0.1f, -0.1f, -0.6f);
	glVertex3f(0.1f, 0.1f, -0.6f);
	glVertex3f(-0.1f, 0.1f, -0.6f);
	glEnd();

}
